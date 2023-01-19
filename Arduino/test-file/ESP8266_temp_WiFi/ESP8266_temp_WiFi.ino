#include <Arduino.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID "gjaischool 3F"
#define WIFI_PASS "gjaischool"
#define WIFI_CONN_BACKOFF_MS 1000

#define MQTT_SERVER_IP "XXX.XXX.XXX.XXX"
#define MQTT_SERVER_PORT XXXXX

#define STATUS_LED_PIN 2

float tempCelcius = 0.0f;
float tempFaren = 0.0f;
String deviceId;

WiFiClient wifiClient;

// Forward decls
void connectWifi(const char* ssid, const char* password);
void adcValToTemperatures(float adcVal, float *celcius, float *farenheit);
void printTempToSerial(float adcVal, float tempCelcius, float tempFaren);
void sendTemperature(float tempCelcius);
String getDeviceId();

void setup() {
  Serial.begin(115200);

  // Turn off WiFi to resolve an issue with unstable readings
  // See this: https://github.com/esp8266/Arduino/issues/2070
  WiFi.disconnect(true);
  pinMode(STATUS_LED_PIN, OUTPUT);

  deviceId = getDeviceId();
}

void loop() {
  float adcVal = analogRead(A0);
  delay(1000);

  adcValToTemperatures(adcVal, &tempCelcius, &tempFaren);
  printTempToSerial(adcVal, tempCelcius, tempFaren);

  sendTemperature(tempCelcius);
  delay(1000);
}

void connectWifi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  while (WiFi.isConnected() != true) {
    Serial.print(".");
    delay(WIFI_CONN_BACKOFF_MS);
  }

  Serial.print("IP=");
  Serial.println(WiFi.localIP());
}

void adcValToTemperatures(float adcVal, float *celcius, float *farenheit) {
  *celcius = ((adcVal * (3300.0 / 1024)) - 500) / 10;
  *farenheit = (*celcius * 1.8) + 32;
}

void printTempToSerial(float adcVal, float tempCelcius, float tempFaren) {
  Serial.print("adc=");
  Serial.print(adcVal);
  Serial.print(" celcius=");
  Serial.print(tempCelcius);
  Serial.print(" farenheit=");
  Serial.println(tempFaren);
}

void sendTemperature(float tempCelcius) {
  digitalWrite(STATUS_LED_PIN, LOW);
  connectWifi(WIFI_SSID, WIFI_PASS);
  WiFi.disconnect(true);
  digitalWrite(STATUS_LED_PIN, HIGH);
}

String getDeviceId() {
  return ("iot_" + WiFi.macAddress());
}
