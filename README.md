IoT-Based Locking System Using OTP software

**BlueLock** is a smart, secure locking system that uses OTP-based authentication over Bluetooth. It combines hardware (ESP32, servo motor, LED) and a custom mobile app (built using MIT App Inventor) to control access via dynamically generated OTPs.

---

## Features

- User authentication using login and registration system
- OTP generation via mobile app
- OTP verification over Bluetooth
- Servo motor-based locking mechanism
- Unlock indication with green LED
- Data flow between ESP32 and mobile app using Bluetooth Classic

---

## Tech Stack

- **Microcontroller**: ESP-32S V1.1
- **App Development**: MIT App Inventor
- **Communication**: Bluetooth Classic
- **Programming Language**: Arduino C/C++
- **Storage**: TinyDB (App)
- **Power Supply**: Mobile power bank (via USB)

---

## Project Flow

1. User logs into the app.
2. User connects to ESP32 via Bluetooth.
3. App sends `REQUEST_OTP,Username` to ESP32.
4. ESP32 generates OTP and sends it back.
5. User enters OTP and taps submit.
6. App sends `VERIFY,Username,EnteredOTP` to ESP32.
7. ESP32 checks the OTP and username:
   - If correct: Unlocks the lock and turns on LED for 10 seconds.
   - If incorrect: Remains locked, sends "Wrong OTP".

---

## Hardware Components

- ESP-32S V1.1 microcontroller
- Servo motor (SG90)
- Green LED (unlock indicator)
- Jumper wires
- Breadboard
- Mobile power bank (for ESP32 power)

---

## Mobile App Screens

1. **Login Page**
   - Email & password login
2. **Register Page**
   - Name, email, password
3. **OTP Screen**
   - Generate OTP
   - Enter & verify OTP
   - Bluetooth connection

---

