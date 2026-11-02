// PES University - Smart Washroom Final Project

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Initialize LCD (Address 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin Definitions
const int trigPin = 9;
const int echoPin = 10;
const int irPin = 2;
const int buzzerPin = 8;
const int ledPin = 13;       
const int moistureLED = 12;  
const int gasPin = A0;
const int moisturePin = A1;  

void setup() {
  Serial.begin(9600);
  
  // LCD Startup
  lcd.init();
  lcd.backlight();
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irPin, INPUT_PULLUP); 
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(moistureLED, OUTPUT);
  
  // New Clean Splash Screen
  lcd.setCursor(0, 0);
  lcd.print(" SMART WASHROOM "); // Row 1
  lcd.setCursor(0, 1);
  lcd.print("     SYSTEM     "); // Row 2
  delay(3000); // Stays for 3 seconds
  lcd.clear();
  
  Serial.println("SYSTEM INITIALIZED: MONITORING ALL SENSORS");
}

void loop() {
  // 1. SENSOR READS
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int distance = pulseIn(echoPin, HIGH) * 0.034 / 2;
  
  int tapState = digitalRead(irPin);
  int gasValue = analogRead(gasPin);
  int moistureValue = analogRead(moisturePin);

  // 2. HARDWARE LOGIC
  if (distance > 0 && distance < 30) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);

  if (gasValue > 600) digitalWrite(buzzerPin, HIGH);
  else digitalWrite(buzzerPin, LOW);

  if (moistureValue < 750) digitalWrite(moistureLED, HIGH);
  else digitalWrite(moistureLED, LOW);

  // 3. LCD PRIORITY DISPLAY
  // Line 1: Team SRNs
  lcd.setCursor(0, 0);
  lcd.print("SRN:493 525 547 ");

  // Line 2: Priority Alerts
  lcd.setCursor(0, 1);
  if (moistureValue < 750) {
    lcd.print("LEAKAGE DETECTED"); 
  } 
  else if (gasValue > 600) {
    lcd.print("BAD ODOR ALERT  "); 
  } 
  else if (tapState == LOW) {
    lcd.print("TAP STATUS: ON  "); 
  } 
  else if (distance > 0 && distance < 30) {
    lcd.print("MOTION DETECTED "); 
  } 
  else {
    lcd.print("MONITORING...   "); 
  }

  // 4. SERIAL MONITOR DATA
  if (tapState == LOW) Serial.print(" [TAP ACTIVE] ");
  Serial.print("Dist: "); Serial.print(distance);
  Serial.print("cm | Gas: "); Serial.print(gasValue);
  Serial.print(" | Leakage Level: "); Serial.println(moistureValue);

  delay(150); 
}