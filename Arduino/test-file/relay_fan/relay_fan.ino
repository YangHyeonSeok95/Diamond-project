
int Relay = 9;


void setup() {
  {
    pinMode(Relay, OUTPUT);  //릴레에를 출력으로 설정
  }

}

void loop() {
  digitalWrite(Relay, HIGH);
  delay(50000);

  digitalWrite(Relay, LOW);
  delay(3000);
}
