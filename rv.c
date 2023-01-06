int analogInputPin = 0; // pin connected to the voltage source

void setup() {
  Serial.begin(9600); // initialize serial communication
}

void loop() {
  int adcValue = analogRead(analogInputPin); // read the analog input
  float voltage = (adcValue * 5.0) / 1023; // convert ADC value to voltage
  Serial.println(voltage); // print the voltage to the serial monitor
  delay(1000); // wait for 1 second before taking another reading
}
