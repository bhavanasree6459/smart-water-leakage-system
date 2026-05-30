// ESP32 CODE - Arduino IDE
// Install: ESP32 Board Package in Arduino IDE
// Libraries: WiFi.h, HTTPClient.h

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi Configuration
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Server Configuration
const char* serverURL = "http://YOUR_IP:5000/api/sensors";
// Example: http://192.168.1.100:5000/api/sensors

// Sensor Pins (Adjust based on your hardware)
const int SENSOR1_PIN = 34;  // ADC pin for pressure sensor
const int SENSOR2_PIN = 35;  // ADC pin for flow sensor
const int SENSOR3_PIN = 32;  // ADC pin for leak detector

// Variables for sensor readings
int sensorsOnline = 0;
float networkStatus = 0.0;
int activeLeaks = 0;
float waterPressure = 0.0;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    pinMode(SENSOR1_PIN, INPUT);
    pinMode(SENSOR2_PIN, INPUT);
    pinMode(SENSOR3_PIN, INPUT);
    
    // Connect to WiFi
    connectToWiFi();
}

void loop() {
    // Read sensors
    readSensors();
    
    // Send data to server
    if (WiFi.status() == WL_CONNECTED) {
        sendDataToServer();
    } else {
        connectToWiFi();
    }
    
    // Send every 5 seconds
    delay(5000);
}

// Connect to WiFi
void connectToWiFi() {
    Serial.println("\nConnecting to WiFi: ");
    Serial.println(ssid);
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connected!");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nFailed to connect to WiFi");
    }
}

// Read sensor values
void readSensors() {
    // Read Pressure Sensor (0-5V to 0-10 bar)
    int rawPressure = analogRead(SENSOR1_PIN);
    waterPressure = (rawPressure / 4095.0) * 10.0;  // Convert to bar
    
    // Read Flow Sensor (count pulses)
    int rawFlow = analogRead(SENSOR2_PIN);
    sensorsOnline = map(rawFlow, 0, 4095, 0, 50);  // Map to 0-50 sensors
    
    // Read Leak Detector (digital or analog)
    int rawLeak = analogRead(SENSOR3_PIN);
    activeLeaks = (rawLeak > 2000) ? 1 : 0;  // Threshold at 2000
    
    // Calculate network status (based on sensors responding)
    networkStatus = (sensorsOnline > 10) ? 100 : (sensorsOnline * 10);
    
    // Print to Serial
    Serial.println("=== Sensor Readings ===");
    Serial.print("Sensors Online: ");
    Serial.println(sensorsOnline);
    Serial.print("Water Pressure: ");
    Serial.print(waterPressure);
    Serial.println(" bar");
    Serial.print("Active Leaks: ");
    Serial.println(activeLeaks);
    Serial.print("Network Status: ");
    Serial.print(networkStatus);
    Serial.println("%");
}

// Send data to server
void sendDataToServer() {
    HTTPClient http;
    
    // Create JSON payload
    StaticJsonDocument<200> doc;
    doc["sensorsOnline"] = sensorsOnline;
    doc["networkStatus"] = String(networkStatus, 1) + "%";
    doc["activeLeaks"] = activeLeaks;
    doc["waterPressure"] = String(waterPressure, 1) + " bar";
    
    String jsonString;
    serializeJson(doc, jsonString);
    
    // Send POST request
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");
    
    int httpCode = http.POST(jsonString);
    
    if (httpCode > 0) {
        Serial.print("HTTP Response Code: ");
        Serial.println(httpCode);
        String payload = http.getString();
        Serial.println("Server Response: " + payload);
    } else {
        Serial.println("Error sending data to server");
    }
    
    http.end();
}

/* ========== SETUP INSTRUCTIONS ==========

1. INSTALL LIBRARIES:
   - Go to Sketch > Include Library > Manage Libraries
   - Search and install: "ArduinoJson" by Benoit Blanchon
   - Ensure WiFi.h is included (comes with ESP32 board)

2. SETUP HARDWARE:
   - Connect pressure sensor to GPIO 34 (ADC)
   - Connect flow sensor to GPIO 35 (ADC)
   - Connect leak detector to GPIO 32 (ADC)
   - Power all sensors with 3.3V or 5V (with voltage divider)
   - Add pull-down resistors (10k) for sensor inputs

3. CONFIGURE CODE:
   - Replace "YOUR_WIFI_SSID" with your WiFi network name
   - Replace "YOUR_WIFI_PASSWORD" with your WiFi password
   - Replace "YOUR_IP" with your server's IP address
   - Adjust sensor pins if using different GPIO pins
   - Calibrate analog readings based on your sensors

4. UPLOAD:
   - Select Board: ESP32 Dev Module
   - Select Port: COM# (your ESP32 port)
   - Click Upload

5. VERIFY:
   - Open Serial Monitor (115200 baud)
   - Should show WiFi connection and sensor readings
   - Check website dashboard for real-time updates

========== EXPECTED OUTPUT ==========
Connecting to WiFi: 
MyNetwork
...........
WiFi Connected!
IP: 192.168.1.100

=== Sensor Readings ===
Sensors Online: 24
Water Pressure: 2.5 bar
Active Leaks: 0
Network Status: 100.0%

HTTP Response Code: 200
Server Response: {"success":true,"data":{...}}

*/
