#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <WebServer.h>

// WiFi Credentials
const char* SSID = "SSID";
const char* PASSWORD = "PASSWORD";

#define SDA_PIN 27  // Set SDA to GPIO 27
#define SCL_PIN 33  // Set SCL to GPIO 33

Adafruit_AHTX0 aht;
WebServer server(8082);  // set port for server

void handleTemperature() {
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);

    String json = "{";
    json += "\"temperature\": " + String(temp.temperature) + ",";
    json += "\"humidity\": " + String(humidity.relative_humidity);
    json += "}";

    server.send(200, "application/json", json);
}

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);

    if (!aht.begin(&Wire, 0x60)) {
        Serial.println("AHT10 not found!");
        while (1);
    }
    Serial.println("AHT10 initialized!");

    // Connect to WiFi
    WiFi.begin(SSID, PASSWORD);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");
    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());

    // Setup Web Server Routes
    server.on("/temperature", handleTemperature);
    server.begin();
    Serial.println("HTTP Server Started!");
}

void loop() {
    server.handleClient();
}
