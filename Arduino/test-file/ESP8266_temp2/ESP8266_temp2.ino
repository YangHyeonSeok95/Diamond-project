#define PIN_DHT 2
#define COUNT   64


void setup() {
  Serial.begin(115200); // 시리얼 통신을 열고 속도를 9600bps 로 사용한다.
}

void loop() {
  int value;
  unsigned int total;
  float voltage, temp;
  total = 0;
  for (int i = 0; i < COUNT; i++) {
    total += analogRead(PIN_DHT);
    delay(1);
  }

  total = total/COUNT;
  voltage = total / 1024.0;
  temp = (voltage - 0.5) * 100;
  Serial.print("value: ");
  Serial.print(total);
  Serial.print(" voltage: ");
  Serial.print(voltage);
  Serial.print(" temp: ");
  Serial.println(temp);
  delay(1000);
  // 전압값으로 변환
}
