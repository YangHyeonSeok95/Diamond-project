#include <DHT.h>

#define PIN_DHT 2  // D4 = 2번핀 (https://www.make-it.ca/nodemcu-details-specifications/)

DHT DHTsensor(PIN_DHT, DHT11);

void setup() {
  DHTsensor.begin();
  pinMode(PIN_DHT, INPUT);

  Serial.begin(115200);

}

void loop() {

  float humidity = DHTsensor.readHumidity();
  float temp = DHTsensor.readTemperature();
  Serial.print("Humidity : ");
  Serial.print(humidity);
  Serial.print(" Temperature : ");
  Serial.print(temp);
  Serial.println(" ºC");
  delay(100);

}
