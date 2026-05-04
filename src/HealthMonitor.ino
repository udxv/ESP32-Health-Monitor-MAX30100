#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "MAX30100_PulseOximeter.h"

// ================= I2C =================
#define SDA_PIN 21
#define SCL_PIN 22

// ================= LCD =================
#define LCD_ADDR 0x27
LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);

// ================= MAX30100 =================
PulseOximeter pox;

uint32_t lastDisplay = 0;
float hrBuffer[5];
uint8_t hrIndex = 0;
float hrFiltered = 0;

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000);

  lcd.init();
  lcd.backlight();
  lcd.print("Smart Health");
  delay(2000);
  lcd.clear();

  if (!pox.begin()) {
    lcd.print("Sensor Error");
    while (1);
  }

  pox.setIRLedCurrent(MAX30100_LED_CURR_50MA);
  lcd.print("Place Finger");
}

// ================= LOOP =================
void loop() {
  pox.update();

  if (millis() - lastDisplay > 1000) {
    lastDisplay = millis();

    float hr = pox.getHeartRate();
    float spo2 = pox.getSpO2();

    // ===== Heart Rate Validation =====
    if (hr > 50 && hr < 120) {   // realistic range
      hrBuffer[hrIndex++] = hr;
      hrIndex %= 5;

      hrFiltered = 0;
      for (int i = 0; i < 5; i++) {
        hrFiltered += hrBuffer[i];
      }
      hrFiltered /= 5;
    }

    Serial.print("Raw HR=");
    Serial.print(hr);
    Serial.print("  Filtered HR=");
    Serial.print(hrFiltered);
    Serial.print("  SpO2=");
    Serial.println(spo2);

    lcd.clear();

    if (hrFiltered > 0 && spo2 > 90) {
      lcd.setCursor(0, 0);
      lcd.print("HR: ");
      lcd.print(hrFiltered, 0);
      lcd.print(" BPM");

      lcd.setCursor(0, 1);
      lcd.print("SpO2: ");
      lcd.print(spo2, 0);
      lcd.print(" %");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Stabilizing...");
      lcd.setCursor(0, 1);
      lcd.print("Hold Still");
    }
  }
}
