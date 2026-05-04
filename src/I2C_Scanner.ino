#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);

  while (!Serial) {
    ; // Wait for Serial Monitor on boards that need it
  }

  Serial.println("\nI2C Scanner");
}

void loop() {
  byte error;
  byte address;
  int deviceCount = 0;

  Serial.println("Scanning...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      deviceCount++;
    } 
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }

  if (deviceCount == 0) {
    Serial.println("No I2C devices found");
  } else {
    Serial.print("Total devices found: ");
    Serial.println(deviceCount);
  }

  Serial.println();
  delay(5000);
}
