#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// MPU6050 I2C address
const int MPU_ADDR = 0x68; 

// Pin Definitions
const int greenLed = 8;
const int yellowLed = 9;
const int redLed = 10;

// Vibration Thresholds
const float thresholdYellow = 2.0; 
const float thresholdRed = 5.0; 

// Variables for blinking logic
unsigned long previousMillis = 0;
bool redLedState = LOW;

void setup() {
  Serial.begin(115200);
  delay(100); // Give hardware a moment to power up

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  // --- BYPASS ADAFRUIT: WAKE UP THE MPU6050 MANUALLY ---
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // Access the Power Management register
  Wire.write(0);     // Write a 0 to wake up the sensor
  byte error = Wire.endTransmission(true);

  if (error != 0) {
    lcd.setCursor(0,0);
    lcd.print("Wiring Error!");
    while (1) { delay(10); } // Stop here if wiring is broken
  }
  
  lcd.clear();
}

void loop() {
  // --- READ RAW ACCELEROMETER DATA ---
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);  // Start reading at register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);  // Request 6 registers (X, Y, Z)

  // Combine the raw high and low bytes for each axis
  int16_t AcX = Wire.read() << 8 | Wire.read();
  int16_t AcY = Wire.read() << 8 | Wire.read();
  int16_t AcZ = Wire.read() << 8 | Wire.read();

  // Convert raw values to m/s^2 to match your thresholds
  // 16384 is the default sensitivity. 9.81 is gravity.
  float ax = (AcX / 16384.0) * 9.81;
  float ay = (AcY / 16384.0) * 9.81;
  float az = (AcZ / 16384.0) * 9.81;

  // Calculate vibration magnitude (isolating from gravity)
  float magnitude = sqrt(ax * ax + ay * ay + az * az);
  float vibration = abs(magnitude - 9.81); 

  // Update LCD Display
  lcd.setCursor(0, 0);
  lcd.print("Vib: "); lcd.print(vibration, 1); lcd.print(" g      ");

  // Logic Control
  if (vibration < thresholdYellow) {
    // Normal Condition
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    lcd.setCursor(0, 1); lcd.print("Status: NORMAL  ");
  } 
  else if (vibration < thresholdRed) {
    // Warning Condition
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(redLed, LOW);
    lcd.setCursor(0, 1); lcd.print("Status: WARNING ");
  } 
  else {
    // Failure Condition (Blinking Red)
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
    
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 300) {
      previousMillis = currentMillis;
      redLedState = !redLedState;
      digitalWrite(redLed, redLedState);
    }
    lcd.setCursor(0, 1); lcd.print("Status: ALERT!  ");
  }
  
  // Add a tiny delay so the LCD text doesn't flicker wildly
  delay(100);
}
