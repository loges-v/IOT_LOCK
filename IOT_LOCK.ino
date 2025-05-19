#include <ESP32Servo.h>  // ESP32 Servo library
#include "BluetoothSerial.h"  // ESP32 Bluetooth library

BluetoothSerial SerialBT;  // Create Bluetooth Serial object
Servo lockServo;  // Servo object for the lock

String receivedData = "";  // Store received data
String generatedOTP = "";  // Store generated OTP

String storedUsername = "logesh";  // Predefined username for verification

#define GREEN_LED  2  // GPIO pin for Green LED
#define SERVO_PIN  27 // GPIO pin for Servo motor

void setup() {
    Serial.begin(115200);  // Debugging via Serial Monitor
    SerialBT.begin("ESP32_LOCK");  // Set ESP32 Bluetooth name

    lockServo.attach(SERVO_PIN);  // Attach servo to GPIO 27
    pinMode(GREEN_LED, OUTPUT);  // Set Green LED as output

    // Initialize lock position
    lockServo.write(0);  // Locked position (0°)
    digitalWrite(GREEN_LED, LOW);  // Turn off LED initially
}

void loop() {
    if (SerialBT.available()) {
        receivedData = SerialBT.readStringUntil('\n');  // Read received data
        receivedData.trim();  // Remove extra spaces

        Serial.println("Received: " + receivedData);

        // Check if the request is for OTP
        if (receivedData.startsWith("REQUEST_OTP")) {
            generatedOTP = generateOTP();  // Generate a new OTP
            SerialBT.println("OTP:" + generatedOTP);  // Send OTP to the mobile app
            delay(500);
            Serial.println("Generated OTP: " + generatedOTP);
        } 
        
        // Check if the request is for OTP verification
        else if (receivedData.startsWith("VERIFY")) {
            int firstComma = receivedData.indexOf(",");
            int secondComma = receivedData.indexOf(",", firstComma + 1);

            if (firstComma == -1 || secondComma == -1) {
                SerialBT.println("wrong data");
                return;
            }

            String currentUsername = receivedData.substring(firstComma + 1, secondComma);
            String enteredOTP = receivedData.substring(secondComma + 1);

            Serial.println("Username received: " + currentUsername);
            Serial.println("Entered OTP received: " + enteredOTP);

            // Validate OTP and Username
            if (currentUsername == storedUsername && enteredOTP == generatedOTP) {
                unlockLock();  // Unlock the lock
                SerialBT.println("unlocked");  // Send success response
            } else {
                SerialBT.println("wrongotp");
            }
        }
    }
}

// Function to generate a 6-digit OTP
String generateOTP() {
    String otp = "";
    for (int i = 0; i < 6; i++) {
        otp += String(random(0, 10));  // Generate a random number (0-9)
    }
    return otp;
}

// Function to unlock the lock
void unlockLock() {
    lockServo.write(90);  // Unlock position (90°)
    digitalWrite(GREEN_LED, HIGH);  // Turn on Green LED
    delay(5000);  // Keep unlocked for 10 seconds
    lockServo.write(0);  // Lock position (0°)
    digitalWrite(GREEN_LED, LOW);  // Turn off Green LED
}
