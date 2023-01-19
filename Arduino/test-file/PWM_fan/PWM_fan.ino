#define fadePin 9 // 모스펫 컨트롤 팬
//#define fadePin 19 // 모스펫 컨트롤 팬
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.flush();

  pinMode(fadePin, OUTPUT); //핀 설정.
}

void loop() {
  FuncManualAction();
}
/********************************
  * 시리얼 모니터의 값을 읽어서 속도 조절
********************************/
  void FuncManualAction(){
    String strlnput = "";
                        
    // 시리얼 통신으로 문자를 입력하기 위한 준비를 한다.
    while(Serial.available() > 0){ //시리얼 입력 값이 있을 때,
      strlnput += (char) Serial.read(); //한번에 한문자를 읽으면
      delay(5); //5밀리초 동안 대기하고 다음 문자를 읽을 준비를 합니다.
    }
  // 입력값이 있으면 적용
  if(strlnput != "") {
    int intVal = strlnput.toInt();
    analogWrite(fadePin, intVal);
    Serial.println(strlnput);
  }

    
}
