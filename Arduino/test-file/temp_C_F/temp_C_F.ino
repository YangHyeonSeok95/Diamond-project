int outputpin= A2; // 센서와 연결된 아날로그 핀 설정

void setup()
{
  Serial.begin(9600); // 시리얼 통신을 열고 속도를 9600bps 로 사용한다.
}

void loop()
{
  int reading = analogRead(outputpin);  // //전압값을 읽음, 
  //센서에 공급되는 전압이 5V면 읽은값x5.0 이고 3.3V 이면 3.3을 곱해준다
  float voltage = reading * 5.0 / 1024.0;
  //시리얼 모니터에 전압값 출력, 전압값(mV)으로 온도 구함 (섭씨), 시리얼 모니터 출력
  float celsiustemp = (voltage - 0.5) * 100 ;  

  // 입력받은 자료값을 수정하여 필요한 자료값으로 바꾼다.

  Serial.print(celsiustemp);
  Serial.println(" Celsius");
  Serial.println("----------------------");
//  Serial.print(fahrenheittemp);
//  Serial.println(" Fahrenheit");
  // 수정하여 나온 자료값을 출력한다.(섭씨, 화씨 둘다 출력)
  delay(2000);
} 
