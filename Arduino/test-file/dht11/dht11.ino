#include <DHT11.h>
int pin=A3;    // 연결한 아두이노 디지털 핀 번호
int led=18;
DHT11 dht11(pin);
void setup()
{
  pinMode(led, OUTPUT);
   Serial.begin(115200);
}
void loop()
{

  // led 켜지는 코드 - 오류시 다른 신호 들어오게 하는 코드 필요
  digitalWrite(led, 1);
  delay(1000);
  digitalWrite(led, 0);
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
