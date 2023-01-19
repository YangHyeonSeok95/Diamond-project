 #include <AFMotor.h> // 라이브러리는 첨부하였습니다.
AF_DCMotor motor(1);

void setup() {
 Serial.begin(9600);    
 Serial.println("Motor party!");
 motor.setSpeed(200);
 motor.run(RELEASE);
}

int i;
void loop() {
 motor.run(FORWARD);
 for (i=0; i<255; i++) {
   motor.setSpeed(i);  
   delay(3);
}
 for (i=255; i!=0; i--) {

   motor.setSpeed(i);  
   delay(3);
}

 motor.run(BACKWARD);
 for (i=0; i<255; i++) {
  
   motor.setSpeed(i);  
   delay(3);
}

 for (i=255; i!=0; i--) {
  
   motor.setSpeed(i);  
   delay(3);
}
} 
