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

// esp32 running loop

void loop() {
    NetworkClient client = server.accept();

    if (client) {
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        client.println("Http/:1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();

                        client.print("Click <a href=\"/on\"> here to turn LED on.<br>");
                        client.print("Click <a href=\"/off\"> here to turn LED off.<br>");

                        client.println();

                        break;

                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += "";
                }

                if (currentLine.endsWith("GET /on")) {
                    digitalWrite(2, HIGH);
                }
                if (currentLine.endsWith("GET /off")) {
                    digitalWrite(2, LOW);
                }
            }
        }
        client.stop();
        Serial.println("Client Disconnected.");
}
}