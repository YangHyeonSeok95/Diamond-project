#define PIN_DHT 2    //analog input pin constant<br>
int tempVal;    // temperature sensor raw readings
float volts;    // variable for storing voltage
float temp;     // actual temperature variable
void setup()
{
  // start the serial port at 9600 baud
  Serial.begin(9600);
}
void loop()
{
  //read the temp sensor and store it in tempVal
  tempVal = analogRead(PIN_DHT);
  volts = tempVal / 1023.0;           // normalize by the maximum temperature raw reading range
  temp = (volts - 0.5) * 100 ;         //calculate temperature celsius from voltage as per the equation found on the sensor spec sheet.
  Serial.print(" Temperature is:   "); // print out the following string to the serial monitor
  Serial.print(temp);                  // in the same line print the temperature
  Serial.println (" degrees C");       // still in the same line print degrees C, then go to next line.
  delay(2000);                         // wait for 1 second or 1000 milliseconds before taking the next reading.
}
