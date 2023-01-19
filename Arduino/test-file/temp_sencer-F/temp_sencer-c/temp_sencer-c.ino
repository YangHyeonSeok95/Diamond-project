int tmp = A2;
void setup() {
Serial.begin(9600);
pinMode(tmp, INPUT);
}

void loop() {
 int value = analogRead(tmp);
 float voltage = value * 5.0/1024;     // 온도센서의 값을 전압으로 변환
 float temperature = (voltage - 0.5) * 100; //섭씨온도로 변환
 Serial.print(temperature);
 Serial.println(" C");
 delay(300);
}
