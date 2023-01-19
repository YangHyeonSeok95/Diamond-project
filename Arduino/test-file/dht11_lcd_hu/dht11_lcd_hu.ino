/* 본 스케치는 여러 커뮤니티를 참고하여 
 kocoafab에서 작성하였습니다.
 누구나 무료로 사용하실 수 있습니다.*/

#include <LiquidCrystal.h> 
#include <DHT11.h> 
#define relay 9             //relay와 연결된 9번 핀
#define dht11Pin 6          //dht11과 연결된 6번 핀

LiquidCrystal lcd(12,11,5,4,3,2);   //RS 핀, E핀, 데이터 핀 4개
String lcdString = "";

DHT11 dht11(dht11Pin);      //dht11 라이브러리 사용을 위한 객체 선언
 
void setup()
{
  pinMode(relay, OUTPUT);
  
  lcd.begin(16,2);           //LCD 크기 지정, 2줄 16칸
  lcd.clear();               //화면 지우기  
  
  Serial.begin(9600);
}

void loop()
{
  int err;     //에러구분 변수
  float humi;  //습도 저장 변수
  float tem;   //온도 저장 변수, 필요한 분은 사용하세요.

  if((err=dht11.read(humi, tem))==0)   //습도값을 에러없이 읽어 왔다면
  {
    onOff(humi);           //가습기 on/off 함수 호출
    lcdHumidity(humi);     //현재 습도 lcd 출력 함수 호출
  }
  else
  {
    //읽어오는 도중 문제가 발생할 경우 에러번호와 에러 시리얼 모니터에 출력
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();    
  }
  delay(DHT11_RETRY_DELAY); //다시 읽어올때 까지 멈춤
}

//가습기 on/off 함수 호출
void onOff(float h) {

 if (h < 50 ) { //습도가 50%보다 작으면 
   digitalWrite(relay, HIGH); //가습기 ON 
 }else { 
   digitalWrite(relay,LOW); 
 }
} 

//현재 습도 LCD 출력 함수 
void lcdHumidity(float hu) { 
 lcd.setCursor(0,0); //커서 0,0에 배치 
 lcd.print("current humidity"); //""안에 글자 출력 
 lcd.setCursor(1,3); //커서 위치 1,3으로 변경 후 
 char buffer[10]; //float를 string으로 변환하기 위한 임시 char 배열 선언 
 dtostrf(hu, 4, 1, buffer); //float -> char로 변환 
 String humidity = " : "; //두번째 줄에 출력할 구문 만들기 ( : 습도 %) 
 humidity += (String)buffer; //char -> string 
 humidity += "%"; 
 Serial.print(humidity); 
 lcd.print(humidity); //현재 습도 출력
}
