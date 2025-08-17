#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HTTPClient.h>

const char* ssid =  ;
const char* password =  ;
const char* server =  ;

const int oneWirePin = 4;  
OneWire oneWire(oneWirePin);
DallasTemperature sensors(&oneWire);

const int tdsPin = 34; 

float readTDS() {
    int rawValue = analogRead(tdsPin);
    return rawValue * 0.5;  
}

 
float calculatePH(float temperature, float tds) {
    return constrain(7.0 + (temperature * 0.01) - (tds * 0.001), 0, 14);
}

 
float calculateDissolvedOxygen(float temperature, float tds) {
    return constrain(8.0 - (temperature * 0.02) - (tds * 0.001), 0, 14);
}

void checkWiFiConnection() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi connection lost. Attempting to reconnect...");
        WiFi.disconnect();
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Reconnecting to WiFi...");
        }
        Serial.println("Reconnected to WiFi!");
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");
    sensors.begin();
}

void loop() {
    checkWiFiConnection();
    sensors.requestTemperatures();
    float temperature = sensors.getTempCByIndex(0);
    float tds = readTDS();
    float ph = calculatePH(temperature, tds);
    float dissolvedOxygen = calculateDissolvedOxygen(temperature, tds);

    Serial.printf("Temperature: %.2f°C, TDS: %.2f, pH: %.2f, Dissolved Oxygen: %.2f\n", temperature, tds, ph, dissolvedOxygen);

    // Prepare JSON data
    String jsonData = "{\"temperature\":" + String(temperature) + 
                      ", \"tds\":" + String(tds) + 
                      ", \"ph\":" + String(ph) + 
                      ", \"dissolved_oxygen\":" + String(dissolvedOxygen) + "}";
    Serial.println("Sending data: " + jsonData);

     
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(server);
        http.addHeader("Content-Type", "application/json");
        
        int maxRetries = 3;
        for (int i = 0; i < maxRetries; i++) {
            int httpResponseCode = http.POST(jsonData);
            if (httpResponseCode > 0) {
                Serial.printf("Data sent successfully, response code: %d\n", httpResponseCode);
                break;  
            } else {
                 
                delay(500);  
            }
        }
        http.end();
    }
    delay(5000);  
}void setup() {
   

}

void loop() {
  

}
