#include <ESP32_Servo.h>

int fan = 18;
void setup() {
pinMode(fan, OUTPUT);
}
void loop() {
digitalWrite(fan, HIGH);
delay(90000);
digitalWrite(fan,LOW);
delay(3000);
}
