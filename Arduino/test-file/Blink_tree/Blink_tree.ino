void setup() {

  for (int i = 10; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  int num = 100;

  digitalWrite(13, HIGH); //13번핀에 +를 출력하자
  digitalWrite(12, LOW);  //13번핀에 -를 출력하자
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  delay(num);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  delay(num);
}
