// read internal chip temp
void setup() {
    Serial.begin(115200);
}

void loop() {
    float temp = temperatureRead();  // Read internal temperature
    Serial.print("Internal Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");
    
    delay(2000);  // Wait 2 seconds before reading again
}
