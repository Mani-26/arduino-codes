#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Initialize the DHT sensor
#define DHTPIN 2          // Pin connected to the DHT sensor
#define DHTTYPE DHT11     // DHT sensor type

DHT dht(DHTPIN, DHTTYPE);

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 columns and 2 rows

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize the DHT sensor
  dht.begin();

  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Temperature:");
  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
}

void loop() {
  // Read temperature and humidity from the DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reading failed
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature and humidity to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Print temperature and humidity to the LCD
  lcd.setCursor(12, 0);
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(9, 1);
  lcd.print(humidity);
  lcd.print(" %");

  delay(2000);  // Wait for 2 seconds
}
