#include <WiFi.h>
// sets up simple http server on the dev board that allows a user to connect
// to a webpage and turn the light on and off

const char *ssid = "enter wifi nane here";
const char *passwd = "enter password here";

// set up server on port 8080
NetworkServer server(8080);

// esp-32 setup loop
void setup() {
    serial.begin(115200);
    pinMode(2, OUTPUT); // select LED pin IO

    delay(7);

    Serial.println();
    Serial.print("Starting server on ");
    Serial.println(ssid);

    WiFi.begin(ssid, passwd);

    while (WiFi.status() != WL_CONNECTED) {
        delay(700);
        Serial.print(".");
    }

    Serial.println("Successfully Connected!");
    Serial.println("Check this IP:");
    Serial.println(WiFi.localIP());

    server.begin();
}