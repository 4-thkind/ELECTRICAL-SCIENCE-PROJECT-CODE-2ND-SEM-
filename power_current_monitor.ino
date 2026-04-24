#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // FIXED

const int sensorPin = A0;   
const int relayPin = 7;     

float R = 220.0;
float supplyVoltage = 5.0;
float thresholdMW = 50.0;

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("System Booting");
  lcd.setCursor(0, 1);
  lcd.print("Checking LCD...");
  delay(2000);
  lcd.clear();
}
