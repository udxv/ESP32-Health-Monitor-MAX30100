# ❤️ Arduino Nano Health Monitor using MAX30100

This project measures **Heart Rate (BPM)** and **SpO2 (Oxygen Level)** using the MAX30100 sensor and displays it on a 16x2 I2C LCD.

---

## 📖 What is MAX30100?

The MAX30100 is a **pulse oximeter + heart-rate sensor**.

It uses:

* Infrared light
* Red light
* Photodetector

To measure:

* ❤️ Heart Rate (BPM)
* 🫁 Blood Oxygen (SpO2)

---

## ❓ Why is it Used?

* Real-time health monitoring
* Non-invasive measurement
* Widely used in IoT health devices

---

## ✅ Advantages

* Measures both BPM & SpO2
* Simple I2C interface
* Low cost and compact
* Easy to integrate with microcontrollers

---

## 🧰 Requirements

### 🔧 Hardware

* Arduino Nano
* MAX30100 Sensor
* 16x2 I2C LCD
* Breadboard
* Jumper wires
* USB data cable

---

## 💻 Software

* Arduino IDE
  Download: https://www.arduino.cc/en/software

---

## 📚 Required Libraries

### 1. MAX30100 Library

https://github.com/oxullo/Arduino-MAX30100

### 2. LiquidCrystal_I2C

https://github.com/johnrickman/LiquidCrystal_I2C

### 3. Wire Library

(Built-in)

---

## 🔌 IMPORTANT: I2C CONNECTION (VERY IMPORTANT)

### ⚠️ SAME PINS FOR BOTH DEVICES

Both LCD and MAX30100 use **I2C communication**, so they share the same pins:

| Signal | Arduino Nano |
| ------ | ------------ |
| SDA    | A4           |
| SCL    | A5           |

👉 **YES — both LCD and MAX30100 connect to A4 and A5 together**

---

### 📌 Full Connections

#### MAX30100 → Arduino Nano

| MAX30100 | Nano |
| -------- | ---- |
| VCC      | 3.3V |
| GND      | GND  |
| SDA      | A4   |
| SCL      | A5   |

---

#### LCD → Arduino Nano

| LCD | Nano |
| --- | ---- |
| VCC | 5V   |
| GND | GND  |
| SDA | A4   |
| SCL | A5   |

---

## ⚠️ IMPORTANT NOTE

Even though both devices use same pins:

* They will NOT conflict
* Because each device has a **different I2C address**

Example:

* LCD → 0x27
* MAX30100 → 0x57

---

## 🔍 Find Your LCD Address (IMPORTANT)

Sometimes LCD address is not 0x27.

Use this code to find it:

---

### 📜 I2C Scanner Code

```cpp id="i2cscan1"
#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);

  Serial.println("Scanning...");
}

void loop() {
  byte error, address;

  for(address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Found I2C device at: 0x");
      Serial.println(address, HEX);
    }
  }

  delay(5000);
}
```

---

### ▶️ How to Use Scanner

1. Upload this code
2. Open Serial Monitor
3. Note the address (example: 0x27 or 0x3F)
4. Update in code:

```cpp id="lcdaddr"
LiquidCrystal_I2C lcd(0x27, 16, 2);
```

---

## 🧪 Troubleshooting

### ✅ Step 1: Normal Connection

* Connect SDA → A4
* Connect SCL → A5

---

### ✅ Step 2: Add Pull-up Resistors

If no data or unstable values:

* Add **4.7kΩ resistors**

  * SDA → VCC
  * SCL → VCC

---

### ✅ Step 3: Use Interrupt Pin (Final Fix)

If still not working:

* Connect **INT → D2 (GPIO 2)**
* Add **4.7kΩ pull-up resistor**

👉 This improves timing and gives stable readings

---

## ⚙️ How It Works

* MAX30100 reads pulse using IR light
* Library converts signal → BPM & SpO2
* Code filters noise
* Stable values are displayed on LCD
* Blink effect shows confirmed reading

---

## 📂 Code Location

* Main code → `src/HealthMonitor.ino`
* Scanner → `src/I2C_Scanner.ino`

---

## ▶️ How to Use

1. Connect all components
2. Upload scanner → find LCD address
3. Update LCD address in main code
4. Upload main code
5. Place finger on sensor
6. View readings

---

## 📄 License

Free to use and modify

---

## 🙌 Contribution

You can improve:

* Filtering
* Accuracy
* UI display
* IoT integration
