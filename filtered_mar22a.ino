#include <DHT.h>

#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Number of samples for moving average
#define NUM_SAMPLES 5

float tempSamples[NUM_SAMPLES];
float humSamples[NUM_SAMPLES];

int sampleIndex = 0;   // renamed from 'index' to avoid conflict

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Initialize arrays
  for (int i = 0; i < NUM_SAMPLES; i++) {
    tempSamples[i] = 0;
    humSamples[i] = 0;
  }
}

void loop() {
  delay(2000);

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Store new values
  tempSamples[sampleIndex] = t;
  humSamples[sampleIndex] = h;

  sampleIndex = (sampleIndex + 1) % NUM_SAMPLES;

  // Calculate average
  float tempSum = 0;
  float humSum = 0;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    tempSum += tempSamples[i];
    humSum += humSamples[i];
  }

  float tempAvg = tempSum / NUM_SAMPLES;
  float humAvg = humSum / NUM_SAMPLES;

  // Print results
  Serial.println("----- RAW VALUES -----");
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  Serial.println("----- FILTERED VALUES -----");
  Serial.print("Temp (Avg): ");
  Serial.print(tempAvg);
  Serial.println(" C");

  Serial.print("Humidity (Avg): ");
  Serial.print(humAvg);
  Serial.println(" %");

  Serial.println("---------------------------");
}