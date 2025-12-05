#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// -----------------------------
// Pin Configuration
// -----------------------------
#define DHTPIN 4          // DHT22 signal pin
#define DHTTYPE DHT22

#define SOIL_PIN 34       // Capacitive soil moisture sensor (Analog)
#define LDR_PIN 35        // LDR (Analog)

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht(DHTPIN, DHTTYPE);

// -----------------------------
// Setup
// -----------------------------
void setup() {
  Serial.begin(115200);
  dht.begin();

  // OLED Init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Farm21 Booting...");
  display.display();
  delay(1500);
}

// -----------------------------
// Main Loop
// -----------------------------
void loop() {
  // Read DHT22
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read soil moisture & LDR
  int soilRaw = analogRead(SOIL_PIN);
  int ldrRaw = analogRead(LDR_PIN);

  // Map values for readability (optional)
  int soilPercent = map(soilRaw, 4095, 1200, 0, 100);  // adjust based on calibration
  soilPercent = constrain(soilPercent, 0, 100);

  int lightPercent = map(ldrRaw, 0, 4095, 0, 100);
  lightPercent = constrain(lightPercent, 0, 100);

  // -----------------------------
  // Display: Temperature & Humidity
  // -----------------------------
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2);
  display.println("Temp");
  display.setTextSize(3);
  display.print(temp, 1); display.println("C");
  
  display.setTextSize(2);
  display.println();
  display.print("Hum ");
  display.print(humidity, 1); display.println("%");

  display.display();
  delay(2500);

  // -----------------------------
  // Display: Soil Moisture
  // -----------------------------
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2);
  display.println("Soil");
  
  display.setTextSize(3);
  display.print(soilPercent);
  display.println("%");

  display.display();
  delay(2500);

  // -----------------------------
  // Display: Light Level
  // -----------------------------
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2);
  display.println("Light");
  
  display.setTextSize(3);
  display.print(lightPercent);
  display.println("%");

  display.display();
  delay(2500);
}
