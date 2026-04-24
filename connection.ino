void setup() {
  Serial.begin(115200);   // start communication
}

void loop() {
  int sensorValue = analogRead(A0);   // read from sensor
  
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);        // print value
  
  delay(200);   // small delay
}