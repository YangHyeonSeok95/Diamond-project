int btn = 2;
int fan = 9;

void setup()
{
  pinMode(btn, INPUT);
  pinMode(fan, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int ipush = digitalRead(btn);

  Serial.println(ipush);

  if (digitalRead(btn) == HIGH) {
    for (int x = 0; x < 255; x++) { //모터속도 제어변수
      analogWrite(fan, x);
      delay(5);
    }
  } else {
    analogWrite(fan, 0); //모터 정지
  }
  delay(1000); //1초지연
}
