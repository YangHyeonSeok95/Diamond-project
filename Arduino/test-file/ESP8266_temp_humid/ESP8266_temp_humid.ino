#include <DHT.h>
#define PIN_DHT 4

DHT DHTsensor(PIN_DHT, DHT11);

void setup() {
 DHTsensor.begin();
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
  delay(1000);
}
