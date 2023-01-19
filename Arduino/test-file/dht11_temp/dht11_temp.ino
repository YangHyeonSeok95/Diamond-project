#include <DHT11.h>
float temperature;  
int reading;  
int lm35Pin = A2; //Analog 0 번에 센서핀 연결
int pin=A3;    // 연결한 아두이노 디지털 핀 번호

DHT11 dht11(pin);

void setup()
{

  analogReference(INTERNAL);
   Serial.begin(115200);
   delay(3000);
}
void loop()
{
  
  //전압의 변화값을 센서핀으로 부터 읽음
    reading = analogRead(lm35Pin);
    //전압값을 읽음, 센서에 공급되는 전압이 5V면 읽은값x5.0 이고 3.3V 이면 3.3을 곱해준다
    float voltage = reading*5.0;
    voltage /= 1024.0;
    //시리얼 모니터에 전압값 출력, 전압값(mV)으로 온도 구함 (섭씨), 시리얼 모니터 출력
    temperature = reading / 9.31;
    Serial.print(voltage); Serial.println(" volts");
    Serial.print(temperature); Serial.println(" degrees C");
    delay(1000);
    
  // 온습도 센서 코드
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

  //
}
