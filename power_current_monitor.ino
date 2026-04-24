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

void loop() {
  int adcValue = analogRead(sensorPin);
  float vAtA0 = adcValue * (supplyVoltage / 1023.0);

  float voltageDrop = supplyVoltage - vAtA0;
  float current = voltageDrop / R; 

  float powerMW = supplyVoltage * current * 1000.0;

  // CLEAN PRINT (prevents leftover garbage)
  lcd.setCursor(0, 0);
  lcd.print("I:");
  lcd.print(current, 3);
  lcd.print("A   ");

  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print(powerMW, 1);
  lcd.print("mW  ");

  if (powerMW > thresholdMW) {   
    digitalWrite(relayPin, LOW);
    lcd.setCursor(12,1);
    lcd.print("OFF");
  } else {
    digitalWrite(relayPin, HIGH);
    lcd.setCursor(12,1);
    lcd.print("ON ");
  }
  
  delay(500);
}