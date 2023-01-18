/* ESP32 시리얼 사용 라이브러리
  포트 : COM10 //외부 엑츄에이터(Serial_1)=센서값 받는부분 [DC전원연결 여기로]
  팬6, 열패드1, 가습기1, ESP32-CAM, LCD 16*2(1)
  에 다른ESP32 D1 R32보드에서 받아온 센서값으로 작동 범위를 설정하고
  on, off를 릴레이모듈로 제어
  열패드 온도 30이상 35이하 유지
  온습도 50~80 유지
  LCD빼본파일
  COM6
*/

#include <HardwareSerial.h>
#include <ArduinoJson.h>
HardwareSerial mySerial(1); //3개의 시리얼 중 2번 채널을 사용
//팬 핀번호
int Relay1 = 02;  //pan1(좌우2개)
int Relay2 = 04;  //pan2(좌우2개)
int Relay3 = 18;  //pan3(좌우2개)
int Relay4 = 19;  // 열패드(hot_pad)릴레이모듈 IN(제어핀)을 19번에 연결
int Relay5 = 5;  // 가습기모듈의 (릴레이모듈) IN(제어핀)을 23번에 연결
int high_point1 = 35; // 열패드 온도 컨트롤을 위한 임의 변수(서식하는 온도 최고값 입력)
int high_point2 = 80; // 가습기 온도 컨트롤을 위한 임의 변수(서식하는 습도 최고값 입력)
/*값을 받아서 LCD에 온도센서2개, 온습도센서1개 값 불러오기*/

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200, SERIAL_8N1, 16, 17);//추가로 사용할 시리얼. RX:16 / TX:17번 핀 사용(16<->17, 17<->16)


  // 팬 작동 릴레이모듈로 신호보내기
  pinMode(Relay1, OUTPUT);  // 제어 핀을 출력으로 설정
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  // 열패드(hot_pad) 작동 릴레이모듈로 신호보내기
  pinMode(Relay4, OUTPUT);  // 제어 핀을 출력으로 설정
}

void loop() {
  // put your main code here, to run repeatedly:
  // 데이터통신코드 여기
  /*
    //tx  통신 보내는걸 확인하는 코드(tx)
    //  mySerial.println("check_tx");
  */
  //rx  통신 받는걸 확인하는 코드
  String command = mySerial.readStringUntil('\n');  // \n을 기준으로 끊어서 하나의 변수화 시켜서 읽어온다.
  Serial.println(command);  // 읽어오는 변수명(command)

  DynamicJsonBuffer jsonBuffer; // 읽어오는 데이터 저장공간 만들어주는 함수
  JsonObject& result = jsonBuffer.parseObject(command);
  // commend라는 변수를 Json화 시켜서 result 라는 변수에 담는다

  // 받아온 시리얼 데이터를 변수명으로 저장
  int T1 = result["T1"];   // 열패드온도(P_T)
  //  int T2 = result["T2"];   // 핫존 온도(H_T)
  int D_H = result["D_H"]; // 온습도센서 습도(C_H)
  int D_T = result["D_T"]; // 온습도센서 온도(C_T)
  delay(1500);


  // 6Fan 릴레이모듈로 팬2개씩 묶어서 3단계 조절하는방법 //HIGH=켜짐, LOW=꺼짐
  if (T1 >= 30 ) {      // 열패드 온도 조절코드 (NO모드) 평상시 팬이 꺼저있다가 신호가오면 켜지는코드
    digitalWrite(Relay1, HIGH); //30이상이면 팬 1,2,3작동
    digitalWrite(Relay2, HIGH);
    digitalWrite(Relay3, HIGH);
  } else if (T1 >= 27) {        // 27이상이면 팬 1,2작동
    digitalWrite(Relay1, HIGH);
    digitalWrite(Relay2, HIGH);

  } else if (T1 >= 25) {        //25이상이면 팬1작동
    digitalWrite(Relay1, HIGH);
  } else {                      //25미만이면 팬 123끔
    digitalWrite(Relay1, LOW);
    digitalWrite(Relay2, LOW);
    digitalWrite(Relay3, LOW);
  }
  // 열패드 온도 조절코드
  if (T1 <= high_point1) {   // 35이하면 킨다 (그려면 30이상 35도이하에서는 키는 상황)
    digitalWrite(Relay4, HIGH);   // 제어핀을 HIGH로( 켬)
    high_point1 = 35;          // 여기를 지나가면 high_point 값이 35로 변함
  } else {    // 35초과면 끈다
    digitalWrite(Relay4, LOW);    // 제어핀을 LOW로(LED 끔)
    high_point1 = 30;          // 여기를 지나가면 high_point 값이 30로 변함
  }

  //가습기 모듈 코드
  if (D_H <= high_point2) {        // 80이하면 킨다 (그려면 50이상 80이하에서는 키는 상황)
    digitalWrite(Relay5 , HIGH);  // 제어핀을 HIGH로( 켬)
    high_point2 = 80;             // 여기를 지나가면 high_point 값이 80로 변함
  } else {                       // 80초과면 끈다
    digitalWrite(Relay5, LOW);    // 제어핀을 LOW로(LED 끔)
    high_point2 = 50;             // 여기를 지나가면 high_point 값이 50로 변함
  }


}
