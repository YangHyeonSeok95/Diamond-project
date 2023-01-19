// 사육장 내부 코드 - 1.온습도센서 2.가습기센서
//대상 : 크레스티그게코(온도 핫스팟:32~35, 쿨스팟:24~28, 습도:50~80)

//h_sensor 라이브러리
#include <DHT11.h>
int h_sensor = 1;      // 온습도 센서 핀 번호
int humidifier = 2;    // 가습기 센서 핀 번호
int t = 0;             // 센서 작동 조절 시 임의의 변수
 
DHT11 dht11(h_sensor);

void setup() {
 pinMode(h_sensor, INPUT);
 pinMode(humidifier, OUTPUT);
 Serial.begin(115200);
}

void loop() {
 //온습도 센서 코드
 int err;
  float temp, humi;
  if((err=dht11.read(humi, temp))==0)
  {
    Serial.print("temperature:");
    Serial.print(temp);
    Serial.print(" humidity:");
    Serial.print(humi);
    Serial.println();
  }
  else
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();

  }
  delay(DHT11_RETRY_DELAY); //delay for reread

  //가습기 센서 코드 - 특정온도 범위 내에서 조절 코드작성
  //일정온도 이상, 일정습도 이하
  if(temp < 32){
    digitalWrite(2,0);        //32도 이하에서 가습기 꺼짐
  } else {
    digitalWrite(2,1);        //32도 이상에서 가습기 켜짐
    if(temp == 35){           //35도 에서 다른 코드 동작
      t == 0;
      if(t == 0){
        digitalWrite(2,0);
      }
    } else if(temp == 32){
      t == 1;
      if(t == 1){
        digitalWrite(2,1);
      }
    }
  }
 }
