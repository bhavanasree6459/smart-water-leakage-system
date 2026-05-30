# ESP32 Integration - Quick Start

Your Smart Water Leakage System is now ready for **real sensor data** from ESP32!

## ✅ What Was Added

### Backend Server
- **server.js** - Node.js server that receives ESP32 data and serves it to the website

### Hardware Integration
- **ESP32_CODE.ino** - Complete Arduino sketch for your ESP32 microcontroller
  - Reads pressure, flow, and leak sensors
  - Connects to WiFi
  - Sends data to Node.js server every 5 seconds

### Documentation
- **SETUP_GUIDE.md** - Complete step-by-step integration guide
- **package.json** - Node.js dependencies (express, cors, body-parser)

### Modified Files
- **dashboard.html** - Now fetches real data instead of hardcoded values
  - Updates metrics from API endpoint
  - Automatically refreshes every 5 seconds
  - Shows alert when leaks detected

## 🚀 Quick Start (3 Steps)

### Step 1: Start Node.js Server
```bash
cd smart-water-leakage-system
npm install
npm start
```

You should see:
```
Server running on http://localhost:5000
Waiting for data from ESP32...
```

### Step 2: Upload Code to ESP32
1. Open `ESP32_CODE.ino` in Arduino IDE
2. Update WiFi credentials:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   const char* serverURL = "http://192.168.1.X:5000/api/sensors";
   ```
   (Replace IP with your computer's IP from `ipconfig`)

3. Upload to ESP32

### Step 3: Open Website
1. Open `index.html` in browser
2. Login to dashboard
3. Watch real sensor values appear! 📊

## 📊 What You'll See

Dashboard shows **real values** from your ESP32:

```
Sensors Online:    24      ← from ESP32
Network Status:    96%     ← from ESP32
Active Leaks:      2       ← from ESP32
Water Pressure:    2.6 bar ← from ESP32
```

Auto-refreshes every 5 seconds with latest readings!

## 🔧 Hardware Connection

Connect to ESP32:
- Pressure sensor → GPIO 34
- Flow sensor → GPIO 35  
- Leak detector → GPIO 32
- GND → GND
- Power → 3.3V/5V

## 📖 Full Guide

See `SETUP_GUIDE.md` for:
- Detailed step-by-step instructions
- Sensor calibration guide
- Troubleshooting tips
- Advanced cloud deployment options

## 🧪 Test Without Hardware

Don't have ESP32 yet? Test with this command:

```bash
# In browser console (F12) while server is running:
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

Dashboard will update instantly! ✨

## 📁 Project Structure

```
smart-water-leakage-system/
├── server.js                 ← Node.js server
├── ESP32_CODE.ino            ← Arduino code
├── SETUP_GUIDE.md            ← Full setup guide
├── dashboard.html            ← Fetches real data
├── index.html
├── login.html
├── register.html
├── monitoring.html
├── alerts.html
├── reports.html
├── settings.html
├── css/style.css
├── js/dashboard.js
├── package.json
├── README.md
└── .gitignore
```

## 🎯 API Endpoints

### GET /api/sensors
Returns latest sensor data

### POST /api/sensors  
ESP32 sends data here

## ✨ Features

✅ Real-time sensor data
✅ Auto-refresh every 5 seconds
✅ Offline cache with localStorage
✅ Alert when leaks detected
✅ Network status percentage
✅ Pressure monitoring

## 🆘 Troubleshooting

### Dashboard shows "--"
- Make sure server is running: `npm start`
- Check console (F12) for errors

### ESP32 won't connect
- Verify WiFi SSID and password (case-sensitive)
- Check your IP address is correct
- Ensure 2.4GHz WiFi (not 5GHz)

### Server not responding
- Port 5000 might be in use
- Check firewall isn't blocking port 5000

See `SETUP_GUIDE.md` for more troubleshooting!

## 📞 Questions?

Refer to `SETUP_GUIDE.md` for complete documentation.

---

**Ready to go!** 🚀 Your Smart Water Leakage System is now connected to hardware!
