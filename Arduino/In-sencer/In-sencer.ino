/* ESP32 시리얼 사용 라이브러리
  세서부에 LCD 부착파일
  포트 : COM3 //내부센서(Serial-2)=센서값 보내는부분
  TMP36(2), DTH11(1) 센서 3개의 센서값을 받아서
  시리얼 통신으로 다른 ESP32 D1 R32 보드의 팬, 열패드, 가습기를 작동시키기 위해
  센서값 전송
  COM5
*/
#include <ArduinoJson.h>      // Json형태의 데이터를 처리할수 있게해주는 라이브러리
#include <HardwareSerial.h>   // 시리얼 데이터 통신 라이브러리
#include <DHT11.h>        // 온습도센서 라이브러리
#include <Wire.h>         // 적외선 열감지센서 라이브러리 
#include <Adafruit_MLX90614.h>    // 적외선 열감지센서 라이브러리 
#include <LiquidCrystal.h>      //LCD 라이브러리 불러오기
LiquidCrystal My_LCD(13, 12, 14, 27, 25, 26); //(RS, E, DB4,DB5,DB6,DB7)

Adafruit_MLX90614 mlx = Adafruit_MLX90614();    // 라이브러리 생성
HardwareSerial mySerial(1); //3개의 시리얼 중 2번 채널을 사용
//  열감지 센서를 T1으로
int pin = 18;               //DTH11 읽는핀
DHT11 dht11(pin);

void setup() {
  Serial.begin(115200);
  mlx.begin();                                  // 온도센서 시작
  mySerial.begin(115200, SERIAL_8N1, 16, 17);//추가로 사용할 시리얼. RX:16 / TX:17번 핀 사용(16<->17, 17<->16)
  // put your setup code here, to run once:

  // LCD 잘나오는지 처음 화면 Test
  My_LCD.begin(16, 2);    // LCD 가로16 세로2칸(col,row)
  My_LCD.setCursor(6, 0);
  My_LCD.print("Hello!");
  My_LCD.setCursor(2, 1);
  My_LCD.print("Well come to");
  delay(5000);
  My_LCD.clear();

}
void loop() {
  // MLX90614 적외선 온도감지센서                T1으로 설정
  Serial.print("T1 : ") ;                 // 시리얼모니터에 출력
  float T0 = mlx.readObjectTempC();
  const double T1 = round(T0 * 100) / 100; // 소수점 자리 2자리수 이하 날려버리기(데이터 전송할떄 5자리까지나와서)
  Serial.println(T1);

  // 온습도센서
  int err;
  float D_H, D_T;
  if ((err = dht11.read(D_H, D_T)) == 0) // (습도, 온도)
  {
    Serial.print("D_T:");
    Serial.print(D_T);         //온도는 D_T , 습도는 D_H
    Serial.print("D_H:");
    Serial.print(D_H);
    Serial.println();
  }
  else
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();
  }

  /*LCD 시작*/
  //  // hot_temple"H_T" // 변수명(코드명) T2(temp2)
  //  My_LCD.setCursor(0, 0);
  //  My_LCD.print("H_T :");
  //  if (T2 > 0 && T2 < 100) { //값이 0보다 크고 100보다 작으면 T2(온도값)출력
  //    My_LCD.setCursor(5, 0);
  //    My_LCD.print(T2);
  //  } else {                 //값이 위조건이 아니면 err
  //    My_LCD.setCursor(5, 0);
  //    My_LCD.print("err");
  //  }
  // 열패드온도화면(적외선 비접촉센서 사용) pad_temp"P_T"  // 변수명(코드명) T1(temp1)
  My_LCD.setCursor(0, 1);
  My_LCD.print("P_T :");
  if (T1 > 0 && T1 < 100) { //값이 0보다 크고 100보다 작으면 T1(온도값)출력
    My_LCD.setCursor(5, 1);
    My_LCD.print(T1);
  } else {                 //값이 위조건이 아니면 err
    My_LCD.setCursor(5, 1);
    My_LCD.print("err");
  }
  // 온습도센서 습도화면 cool_humid"C_H" //변수명(코드명) D_H(DTH11_humid)
  My_LCD.setCursor(8, 0);
  My_LCD.print("C_H :");
  if (D_H >= 20 && D_H <= 95) {   //만약 온습도 센서 습도값이 20이상 95이하일경우 정상
    My_LCD.setCursor(13, 0);
    My_LCD.print(D_H);
  } else {                         //값이 위조건이 아니면 err
    My_LCD.setCursor(13, 0);
    My_LCD.print("err");
  }
  // 온습도센서 온도화면 cool_temp"C_T" //변수명(코드명)D_T(DTH11_temp)
  My_LCD.setCursor(8, 1);
  My_LCD.print("C_T :");
  if (D_T > 0 && D_T <= 50) {   //만약 온습도 센서 온도값이 0보다크고 50이하일경우 정상
    My_LCD.setCursor(13, 1);
    My_LCD.print(D_T);
    My_LCD.setCursor(15, 1);    //err 끝에 r이 남아서 한칸 공백으로 입력하여 지워주기
    My_LCD.print(" ");
  } else {
    My_LCD.setCursor(13, 1);    //값이 위조건이 아니면 err
    My_LCD.print("err");
  }
  delay(1000);
  My_LCD.clear();
  //  delay(1000); //delay for reread

  // 시리얼데이터 전송코드
  // put your main code here, to run repeatedly:
  //tx
  Serial.println("check2");

  String abc = "{\"T1\":\"0\",\"D_T\":\"0\", \"D_H\":\"0\"}";
  String nnn = "";
  DynamicJsonBuffer jsonBuffer;
  JsonObject& result = jsonBuffer.parseObject(abc);
  result["T1"] = T1;
  //  result["T2"] = T2;
  result["D_H"] = D_H;
  result["D_T"] = D_T;
  result.printTo(nnn);
  mySerial.println(nnn);



  //rx 신호를 읽어오는지 확인하는 코드
  //  String command2 = mySerial.readStringUntil('\n');
  //  Serial.println(command2);
  Serial.println("==========");
  delay(1000);
}
