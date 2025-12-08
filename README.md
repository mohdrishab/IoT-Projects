# Ultrasonic Object Detection & IoT Alert System

This repository contains two related projects built using ultrasonic sensors:

1. **Arduino Uno – Local Object Detection with Buzzer Alert**
2. **NodeMCU (ESP8266) – Object Detection with Cloud Integration (IFTTT Alerts)**

---

## 1. Arduino Uno – Local Object Detection + Buzzer

### Features

- Real-time distance measurement using HC-SR04 ultrasonic sensor  
- Distance-based alert zones:
  - Safe: distance > 30 cm → no sound
  - Warning: 10–30 cm → intermittent beeps
  - Danger: < 10 cm → continuous alarm
- Serial Monitor output for distance debugging

### Connections

**HC-SR04 → Arduino Uno**
- VCC → 5V  
- GND → GND  
- TRIG → D2  
- ECHO → D3  

**Buzzer → Arduino Uno**
- + → D8  
- – → GND  

---

## 2. NodeMCU (ESP8266) – Object Detection + Cloud Alert (IFTTT)

### Features

- Uses NodeMCU + HC-SR04 for distance measurement  
- Local buzzer alert for close objects  
- Sends web request to IFTTT Webhooks when object is closer than a threshold  
- IFTTT can trigger phone notification, email, etc.

### Connections

**HC-SR04 → NodeMCU**
- VCC → VIN  
- GND → GND  
- TRIG → D5  
- ECHO → (through resistor divider) → D6  

**Buzzer → NodeMCU**
- + → D7  
- – → GND  

---
