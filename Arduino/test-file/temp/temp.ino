float temperature;
int reading;
int pin = 2;  // 연결한 아두이노 디지털 핀 번호 -  온습도센서

void setup() {
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(19);           // 온도센서(TMP36) 값 측정
  //전압값을 읽음, 센서에 공급되는 전압이 5V면 읽은값x5.0 이고 3.3V 이면 3.3을 곱해준다
  float voltage = reading * 5.0;
  voltage /= 1024.0;
  //시리얼 모니터에 전압값 출력, 전압값(mV)으로 온도 구함 (섭씨), 시리얼 모니터 출력
  temperature = reading / 9.31;
  Serial.print(voltage); Serial.println(" volts");
  Serial.print(temperature); Serial.println(" degrees C");
  delay(1000);
}
