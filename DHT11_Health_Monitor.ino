// ============================================
// Health Monitoring System
// Bio-Signal Acquisition using DHT11 + NodeMCU
// DSP Lab Project - Signal Acquisition Part
// ============================================

#include <DHT.h>

#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  Serial.println("=====================================");
  Serial.println("  Health Monitoring System - DSP Lab ");
  Serial.println("  Signal Acquisition using DHT11     ");
  Serial.println("=====================================");
  Serial.println("Sensor is starting up... Please wait.");
  delay(2000);
}

void loop() {
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("ERROR: Failed to read from DHT11!");
    Serial.println("Check your wiring and try again.");
    delay(2000);
    return;
  }

  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);

  Serial.println("-------------------------------------");

  Serial.print("Reading taken at: ");
  Serial.print(millis() / 1000);
  Serial.println(" seconds");

  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity    : ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Heat Index  : ");
  Serial.print(heatIndex);
  Serial.println(" C");

  Serial.print("Status      : ");
  if (temperature < 35.0) {
    Serial.println("Below Normal");
  } else if (temperature >= 35.0 && temperature <= 37.5) {
    Serial.println("NORMAL");
  } else if (temperature > 37.5 && temperature <= 38.5) {
    Serial.println("Mild Fever");
  } else {
    Serial.println("HIGH FEVER - Seek Medical Attention!");
  }

  delay(2000);
}
