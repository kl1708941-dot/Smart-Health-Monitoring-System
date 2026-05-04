#include <DHT.h>

#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Moving average settings
#define NUM_SAMPLES 5

float tempSamples[NUM_SAMPLES];
float humSamples[NUM_SAMPLES];

int sampleIndex = 0;

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
  delay(1000);   // Faster for smoother graph

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

  // Calculate averages
  float tempSum = 0;
  float humSum = 0;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    tempSum += tempSamples[i];
    humSum += humSamples[i];
  }

  float tempAvg = tempSum / NUM_SAMPLES;
  float humAvg = humSum / NUM_SAMPLES;

  // ===== NORMAL SERIAL OUTPUT =====
  Serial.println("----- RAW VALUES -----");
  Serial.print("Temp: "); Serial.print(t); Serial.println(" C");
  Serial.print("Humidity: "); Serial.print(h); Serial.println(" %");

  Serial.println("----- FILTERED VALUES -----");
  Serial.print("Temp (Avg): "); Serial.print(tempAvg); Serial.println(" C");
  Serial.print("Humidity (Avg): "); Serial.print(humAvg); Serial.println(" %");

  // ===== THRESHOLD ALERTS (LOW FOR TESTING) =====
  if (tempAvg > 30) {
    Serial.println("WARNING: High Temperature!");
  }

  if (humAvg > 60) {
    Serial.println("WARNING: High Humidity!");
  }

  Serial.println("---------------------------");

  // ===== PROFESSIONAL SERIAL PLOTTER OUTPUT =====
  // DO NOT CHANGE THIS FORMAT

  Serial.print("RawTemp:");
  Serial.print(t);
  Serial.print("\t");

  Serial.print("AvgTemp:");
  Serial.print(tempAvg);
  Serial.print("\t");

  Serial.print("RawHum:");
  Serial.print(h);
  Serial.print("\t");

  Serial.print("AvgHum:");
  Serial.println(humAvg);
}