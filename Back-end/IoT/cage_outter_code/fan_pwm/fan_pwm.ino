// 사육장 외부(Arduino) 코드 - 1.팬 2.LCD 3.열패드 
//대상 : 크레스티그게코(온도 핫스팟:32~35, 쿨스팟:24~28, 습도:50~80)

int fan_pin = A1;

void setup() {
 pinMode(fan_pin, OUTPUT);
 Serial.begin(9600);
}

void loop() {
 // 팬 조절 코드 - DB에서 temp와 humi값을 읽어오기(humi는 80이하일 때 
 if(temp < 32 || humi < 80){
   digitalWrite(fan_pin,0);
 }
 else if(temp > 35 || humi > 80){
  digitalWrite(fan_pin,1);
 }
 else{
  int ch1 = map(temp, 31, 36, 255, 0); // DB에서 온습도센서의 온도 값 읽어오기
                                       // 32~35도 이지만 오차 및 기타를 고려하여 끝 값이 아닌 31~36으로 설정
  analogWrite(fan_pin, ch1);
 }
}

// ch1 상태일 때 temp와 humi가 계속 그 상태로 유지될 것인가? 그렇다면 가습기나 팬은 계속 작동할 것이다. 실험 확인필요
