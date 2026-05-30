// Simple Node.js/Express Server for ESP32 Integration
// Install: npm install express cors body-parser

const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');

const app = express();
const PORT = 5000;

// Middleware
app.use(cors());
app.use(bodyParser.json());

// Store latest sensor data
let sensorData = {
    sensorsOnline: 24,
    networkStatus: '96%',
    activeLeaks: 2,
    waterPressure: '2.6 bar',
    timestamp: new Date().toISOString()
};

// GET endpoint - fetch latest sensor data
app.get('/api/sensors', (req, res) => {
    res.json(sensorData);
});

// POST endpoint - receive data from ESP32
app.post('/api/sensors', (req, res) => {
    const { sensorsOnline, networkStatus, activeLeaks, waterPressure } = req.body;
    
    // Update sensor data
    if (sensorsOnline !== undefined) sensorData.sensorsOnline = sensorsOnline;
    if (networkStatus !== undefined) sensorData.networkStatus = networkStatus;
    if (activeLeaks !== undefined) sensorData.activeLeaks = activeLeaks;
    if (waterPressure !== undefined) sensorData.waterPressure = waterPressure;
    
    sensorData.timestamp = new Date().toISOString();
    
    console.log('Data received from ESP32:', sensorData);
    res.json({ success: true, data: sensorData });
});

// Start server
app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
    console.log('Waiting for data from ESP32...');
});
