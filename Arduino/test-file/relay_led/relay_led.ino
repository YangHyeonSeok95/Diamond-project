int ctrl_pin1 = 18;      // 릴레이모듈 IN(제어핀)을 18번에 연결
int ctrl_pin2 = 19;      // 릴레이모듈 IN(제어핀)을 19번에 연결
void setup() {
  pinMode(ctrl_pin1, OUTPUT);  // 제어 핀을 출력으로 사용
  pinMode(ctrl_pin2, OUTPUT);  // 제어 핀을 출력으로 사용
}

void loop() {
  digitalWrite(ctrl_pin1, 1);   // 제어핀18을 HIGH로(LED 켬)
  digitalWrite(ctrl_pin2, 1);   // 제어핀을 19HIGH로(LED 켬)
  delay(30000);      // 1초간 기다림
  
  digitalWrite(ctrl_pin1, 0);    // 제어핀을18LOW로(LED 끔)
  digitalWrite(ctrl_pin2, 0);    // 제어핀을 19LOW로(LED 끔)
  delay(5000);      // 1초간 기다림
}
