# ESP32 Integration Guide

Complete guide to connect your ESP32 hardware with the Smart Water Leakage System website.

## Overview

The website fetches real sensor data from your ESP32 microcontroller via a Node.js server. The flow is:

```
ESP32 (Sensors) → POST Data → Node.js Server → Website (Fetch & Display)
```

## Setup Steps

### Step 1: Install Node.js Server

1. **Install Node.js** (if not already installed):
   - Download from https://nodejs.org/
   - Install the LTS version

2. **Create package.json** in your project folder:
   ```json
   {
     "name": "water-leakage-server",
     "version": "1.0.0",
     "main": "server.js",
     "dependencies": {
       "express": "^4.18.2",
       "cors": "^2.8.5",
       "body-parser": "^1.20.2"
     }
   }
   ```

3. **Install dependencies**:
   ```bash
   cd smart-water-leakage-system
   npm install
   ```

4. **Start the server**:
   ```bash
   node server.js
   ```
   
   You should see:
   ```
   Server running on http://localhost:5000
   Waiting for data from ESP32...
   ```

### Step 2: Configure ESP32

1. **Install Arduino IDE**:
   - Download from https://www.arduino.cc/en/software

2. **Add ESP32 Board**:
   - File → Preferences
   - Add to "Additional Boards Manager URLs":
     `https://dl.espressif.com/dl/package_esp32_index.json`
   - Tools → Board Manager → Search "ESP32" → Install

3. **Install ArduinoJson Library**:
   - Sketch → Include Library → Manage Libraries
   - Search "ArduinoJson" → Install (by Benoit Blanchon)

4. **Open ESP32_CODE.ino** in Arduino IDE

5. **Configure for your setup**:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";           // Your WiFi network
   const char* password = "YOUR_WIFI_PASSWORD";   // Your WiFi password
   const char* serverURL = "http://192.168.1.X:5000/api/sensors";
   ```
   
   Replace `192.168.1.X` with your computer's IP address:
   - Windows: `ipconfig` in Command Prompt
   - Mac/Linux: `ifconfig` in Terminal

### Step 3: Hardware Connection

Connect your sensors to ESP32:

```
Pressure Sensor  → GPIO 34 (ADC)
Flow Sensor      → GPIO 35 (ADC)
Leak Detector    → GPIO 32 (ADC)
GND              → GND
3.3V/5V          → VCC (with voltage divider if 5V)
```

### Step 4: Upload Code to ESP32

1. Select Board: **ESP32 Dev Module**
2. Select Port: **COM3** (or your ESP32 port)
3. Click **Upload**
4. Wait for upload to complete

### Step 5: Verify Connection

1. **Open Serial Monitor** in Arduino IDE (115200 baud)
2. You should see:
   ```
   Connecting to WiFi: MyNetwork
   ..........
   WiFi Connected!
   IP: 192.168.1.150
   
   === Sensor Readings ===
   Sensors Online: 24
   Water Pressure: 2.5 bar
   Active Leaks: 0
   Network Status: 100.0%
   
   HTTP Response Code: 200
   Server Response: {"success":true,...}
   ```

3. **Check Node.js Server Output**:
   ```
   Data received from ESP32: {
     sensorsOnline: 24,
     networkStatus: '100.0%',
     activeLeaks: 0,
     waterPressure: '2.5 bar'
   }
   ```

4. **Open Website**: Open `index.html` in browser
   - Login to dashboard
   - Check metrics - they should update every 5 seconds!

## Customizing Sensor Reading

Modify the `readSensors()` function in ESP32_CODE.ino:

```cpp
void readSensors() {
    // Example: Pressure sensor on ADC pin
    int rawPressure = analogRead(SENSOR1_PIN);
    waterPressure = (rawPressure / 4095.0) * 10.0;  // 0-10 bar range
    
    // Adjust the formula based on your sensor:
    // - ADC range: 0-4095 for ESP32
    // - Your sensor range: check sensor datasheet
    // - Formula: (rawValue / 4095.0) * maxValue
}
```

## Testing Without ESP32

If you don't have ESP32 yet, test the system:

1. Run server: `node server.js`
2. Open browser console and run:
   ```javascript
   fetch('http://localhost:5000/api/sensors', {
     method: 'POST',
     headers: { 'Content-Type': 'application/json' },
     body: JSON.stringify({
       sensorsOnline: 24,
       networkStatus: '96%',
       activeLeaks: 2,
       waterPressure: '2.6 bar'
     })
   })
   ```
3. Watch dashboard update!

## Troubleshooting

### "Cannot connect to ESP32"
- Check server is running: `node server.js`
- Check ESP32 is connected to WiFi (see Serial Monitor)
- Verify IP address in ESP32_CODE.ino matches your server

### "HTTP Error" in Serial Monitor
- Make sure Node.js server is running
- Check firewall isn't blocking port 5000
- Verify IP address is correct

### Dashboard shows "--"
- Check browser console for errors (F12)
- Verify server URL in dashboard.html
- Make sure localStorage isn't blocking data

### ESP32 won't connect to WiFi
- Check SSID and password are correct (case-sensitive)
- Verify WiFi is 2.4GHz (ESP32 doesn't support 5GHz)
- Check router allows ESP32 device connection

## Advanced: Deploy to Cloud

To access from anywhere (not just local network):

1. Use cloud service: **Firebase**, **AWS**, or **Heroku**
2. Deploy Node.js server to cloud
3. Update serverURL in ESP32_CODE.ino to cloud URL
4. Update API_URL in dashboard.html

Example with Firebase:
```javascript
const API_URL = 'https://your-firebase-app.firebaseapp.com/api/sensors';
```

## File Structure After Setup

```
smart-water-leakage-system/
├── index.html
├── dashboard.html          ← Fetches from API
├── server.js               ← Node.js server
├── ESP32_CODE.ino          ← Arduino code
├── SETUP_GUIDE.md          ← This file
├── css/
│   └── style.css
└── js/
    └── dashboard.js
```

## Real-Time Data Flow

1. **ESP32** reads sensors every 5 seconds
2. **ESP32** sends POST request to Node.js server
3. **Server** stores latest sensor data
4. **Website** fetches data via GET request every 5 seconds
5. **Dashboard** displays real-time metrics

## API Endpoints

### GET /api/sensors
Returns latest sensor data
```
Response:
{
  "sensorsOnline": 24,
  "networkStatus": "96%",
  "activeLeaks": 2,
  "waterPressure": "2.6 bar",
  "timestamp": "2026-05-30T12:34:56.789Z"
}
```

### POST /api/sensors
Receives data from ESP32
```
Request Body:
{
  "sensorsOnline": 24,
  "networkStatus": "96%",
  "activeLeaks": 2,
  "waterPressure": "2.6 bar"
}
```

## Support

For issues:
1. Check Serial Monitor output (Arduino IDE)
2. Check Node.js server console output
3. Check browser console (F12 Developer Tools)
4. Verify all IP addresses and ports match

Good luck! 🚀
