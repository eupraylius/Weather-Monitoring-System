#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Pins
#define DHTPIN 2 
#define DHTTYPE DHT22    

DHT dht(DHTPIN, DHTTYPE);

// OLED dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  pinMode(A2, INPUT);
  Serial.begin(9600);

  dht.begin();

// error checking
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Weather Monitor");
  display.display();
  delay(2000);
}

void loop() {
  // Read temperature and humidity
   int gas_lavel= analogRead(A2);
  Serial.println("Gas level: ");
  Serial.println(gas_lavel);
  

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Print to Serial Monitor
  Serial.print(F("Temp: "));
  Serial.print(temperature);
  Serial.print(F(" °C  |  Humidity: "));
  Serial.print(humidity);
  Serial.println(F(" %"));

  // Display on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Weather Monitor");
  display.setCursor(0, 10);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");
  display.setCursor(0, 20);
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");
  
  display.setCursor(0, 30);
  display.println("Gas level: ");
  display.print(gas_lavel);
  display.println("PPM");

  display.display();

  delay(2000); // Update every 2 seconds
}
