#include <Wire.h>
#include <Adafruit_AHTX0.h>

#define SDA_PIN 27  // Set SDA to GPIO 27
#define SCL_PIN 33  // Set SCL to GPIO 33

// collect temperature and humidity from on board aht10
// NAP3XD 

Adafruit_AHTX0 aht;

void setup() {
    Serial.begin(115200);
    
    // Initialize I2C with custom SDA and SCL pins
    Wire.begin(SDA_PIN, SCL_PIN);

    // Correct the aht.begin() function
    if (!aht.begin(&Wire, 0x60)) {  // Pass Wire instance and I2C address
        Serial.println("AHT10 sensor not found! Check wiring.");
        while (1);
    }
    
    Serial.println("AHT10 sensor initialized successfully!");
}

void loop() {
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);  // Get temperature and humidity data

    Serial.print("Temperature: ");
    Serial.print(temp.temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity.relative_humidity);
    Serial.println(" %");

    delay(7000);  // Read every 7 seconds
}
