// find onboard devices on esp32 dev board
#include <Wire.h>

#define SDA_PIN <ENTER SDA GUESS HERE>  // Your custom SDA pin
#define SCL_PIN <ENTER SCL GUESS HERE>  // Your custom SCL pin

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);  // Initialize I²C with custom pins
    Serial.println("\nScanning for I2C devices...");
}

void loop() {
    byte count = 0;
    Serial.println("--------------------------------------------------");
    
    for (byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        if (Wire.endTransmission() == 0) {
            Serial.print("Found I2C device at address: 0x");
            Serial.println(address, HEX);
            count++;
        } else {
            Serial.print("No response at address: 0x");
            Serial.println(address, HEX);
        }
    }
    
    Serial.println("--------------------------------------------------");
    
    if (count == 0) {
        Serial.println("No I2C devices found. Check wiring!");
    } else {
        Serial.print("Total I2C devices found: ");
        Serial.println(count);
    }

    delay(5000);  // Scan every 5 seconds
}
