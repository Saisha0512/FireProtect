# include <WiFi.h>
# include <HTTPClient.h>
# include "DHT.h"

// SENSOR PINS 
# define DHTPIN 14
# define PIR_PIN 5
# define FLAME_PIN 18
# define GAS_PIN 34
# define BUZZER_PIN 13 

// DHT CONFIG 
# define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// WIFI CONFIG
const char* ssid = "Saisha 5G";
const char* password = "Saisha@2025";

// THINGSPEAK
String apiKey = "VW4ORHL73DUR7GOJ";
const char* server = "http://api.thingspeak.com/update";

// FIRE THRESHOLDS
int gasThreshold = 1000;
int tempThreshold = 30;

// BUZZER CONTROL
void buzzerOn() {
  ledcWrite(BUZZER_PIN, 128);   // 50% duty = ON
}

void buzzerOff() {
  ledcWrite(BUZZER_PIN, 0);     // OFF
}

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(FLAME_PIN, INPUT);
  pinMode(GAS_PIN, INPUT);

  dht.begin();

  // BUZZER SETUP 
  ledcAttach(BUZZER_PIN, 2000, 8);
  buzzerOff();

  // WIFI 
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
}

void loop() {

  // Read Sensors 
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int flame = digitalRead(FLAME_PIN);  // 0 = FIRE
  int gasValue = analogRead(GAS_PIN);
  int pir = digitalRead(PIR_PIN);

  Serial.println("\n---- SENSOR DATA ----");
  Serial.print("Temperature: "); Serial.println(temp);
  Serial.print("Humidity: "); Serial.println(hum);
  Serial.print("Flame: "); Serial.println(flame == 0 ? "🔥 FIRE" : "No Flame");
  Serial.print("Gas Value: "); Serial.println(gasValue);
  Serial.print("PIR Motion: "); Serial.println(pir);

  // Alarm Mapping 
  bool fireDetected = (flame == LOW);
  bool highGas = (gasValue > gasThreshold);
  bool highTemp = (temp > tempThreshold);

  if (fireDetected || highGas || highTemp) {
    buzzerOn();
  } else {
    buzzerOff();
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = String(server) +
      "?api_key=" + apiKey +
      "&field1=" + String(temp) +
      "&field2=" + String(hum) +
      "&field3=" + String(flame) +      // 0 or 1
      "&field4=" + String(gasValue) +
      "&field5=" + String(pir);

    Serial.println("Uploading to ThingSpeak...");
    http.begin(url);

    int httpCode = http.GET();
    Serial.print("ThingSpeak Response Code: ");
    Serial.println(httpCode);

    http.end();
  }

  delay(15000);  
}
