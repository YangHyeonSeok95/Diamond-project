#include <LiquidCrystal.h>

 // (RS, E, DB4,DB5,DB6,DB7)
LiquidCrystal lcd(4, 5, 8, 9, 10, 11);
 
void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Hello!");
  delay(1000);
  lcd.clear();
}
 
void loop() {  
  lcd.setCursor(0,0);
  lcd.print("C_T: ");
  lcd.print("34");              //DB에 있는 온습도 센서의 온도 값 읽어오기
  lcd.setCursor(0,1);  
  lcd.print("C_H: ");
  lcd.print("35");              //DB에 있는 온습도 센서의 습도 값 읽어오기
  lcd.setCursor(8,0);
  lcd.print("H_T: ");
  lcd.print("35");              //DB에 있는 HOT_ZONE의 열센서 온도 값 읽어오기
  lcd.setCursor(8,1);
  lcd.print("P_T: "); 
  lcd.print("36");              //DB에 있는 열패드의 열센서 온도 값 읽어오기           
}

//통신해서 받아오는 데이터값 연동하기!
