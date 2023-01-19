//주변환경의 온도와 습도를 측정하여 LCD에 출력하기

#include 

#include 

#include 

#include 

#include 

​

#define DHTPIN 7

#define DHTTYPE DHT11

​

hd44780_I2Cexp lcd; //LCD 객체

DHT dht(DHTPIN, DHTTYPE);

​

void setup() {

Serial.begin(9600);

lcd.begin(16, 2); //LCD 통신 사용

dht.begin();

pinMode(5, OUTPUT);

}

​

void loop() {

//온도와 습도 값을 측정하고 변수에 저장하기

float humi, temp;

temp = dht.readTemperature();

humi = dht.readHumidity();

//센서가 측정하지 못 할 경우 측정 종료

if(isnan(humi) || isnan(temp)){

Serial.println("Failed to read from DHT sensor!!");

return;

}

//측정된 온도와 습도 출력하기

lcd.clear (); //LCD 출력내용 지우기

lcd.setCursor (0, 0);

lcd.print("Temp: ");

lcd.print (temp);

lcd.setCursor (0, 1);

lcd.print("Humi: ");

lcd.print (humi);

delay(300);

​

if (temp>21) {

digitalWrite(5,HIGH);

}

else {

digitalWrite(5,LOW);

}

delay(2000);

}
