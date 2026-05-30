# Smart Water Leakage System

A modern mobile-optimized web application for real-time detection and monitoring of water leakages in public water distribution networks.

## Features

✅ **Live Monitoring**
- Real-time sensor monitoring dashboard
- Network status overview
- Active sensors and pressure tracking

✅ **Leak Detection**
- Automatic leakage alerts
- Multi-level alert system (Active/Resolved)
- Severity indicators (High/Medium/Low)

✅ **Interactive Map**
- Live network map with custom location search
- Add custom zones/locations dynamically
- Zone status visualization

✅ **Reports & Analytics**
- Water loss analysis
- Usage statistics
- Historical reports with resolution status

✅ **User Management**
- User profile editing
- Login & Registration
- Logout functionality

✅ **Settings & Customization**
- Editable user profile
- Notification preferences
- Emergency contact management
- App theme (Light/Dark mode)
- System information

## Pages

1. **index.html** - Splash/Welcome screen
2. **login.html** - User login with modern UI
3. **register.html** - User registration
4. **dashboard.html** - Main dashboard with system overview
5. **monitoring.html** - Live network map with location search
6. **alerts.html** - Leakage alerts with filtering (All/Active/Resolved)
7. **reports.html** - Water loss and usage reports
8. **settings.html** - User settings, profile, notifications, theme

## Technologies Used

- HTML5
- CSS3 (with responsive design & dark theme)
- JavaScript (vanilla)
- Font Awesome Icons
- LocalStorage API

## How to Use

1. Open `index.html` in a web browser
2. Click "Login" or "Register"
3. Access the dashboard to:
   - View system status and metrics
   - Search locations on the map
   - Check alerts and reports
   - Manage settings and profile

## Features Breakdown

### Dashboard
- System status indicator
- Real-time metrics (Sensors, Network Status, Active Leaks, Water Pressure)
- Quick action buttons

### Map
- Search existing zones or add new locations
- View sensor data for each location
- Real-time status updates

### Alerts
- Filterable alert list (All/Active/Resolved)
- Color-coded severity levels
- Location and timestamp information

### Reports
- Water intake analysis
- Leakage statistics
- Historical report tracking

### Settings
- **Profile** - Edit name, email, phone, role
- **Notifications** - Toggle leak/pressure alerts, email, SMS
- **Emergency Contacts** - Control room, field service, technical support
- **App Theme** - Switch between light and dark modes
- **About** - System version and features

## LocalStorage Features

- Custom location data persists
- Theme preference saved
- User settings retained

## Responsive Design

- Mobile-first approach
- Optimized for 500px width devices
- Bottom navigation bar
- Touch-friendly interface

## Dark Theme

Comprehensive dark theme with:
- Dark backgrounds
- Light text
- Adjusted colors for visibility
- Toggleable from Settings

## Version

v1.0.0 - Initial Release (May 2026)

## ESP32 Integration

Connect your ESP32 microcontroller to display **real sensor data** on the dashboard!

### How It Works
1. ESP32 reads pressure, flow, and leak sensors
2. Sends data to Node.js server via HTTP POST
3. Website fetches real-time data via HTTP GET
4. Dashboard updates every 5 seconds

### Quick Setup
1. Install Node.js dependencies: `npm install`
2. Start server: `npm start` (runs on port 5000)
3. Upload `ESP32_CODE.ino` to your ESP32 board
4. Dashboard automatically shows real sensor values!

### Files
- `server.js` - Node.js server for data relay
- `ESP32_CODE.ino` - Arduino code for ESP32
- `SETUP_GUIDE.md` - Complete integration guide
- `package.json` - Node.js dependencies

### Real Sensor Data
- **Sensors Online** - Number of active water sensors
- **Network Status** - Percentage of responding sensors
- **Active Leaks** - Count of detected leaks
- **Water Pressure** - Current pressure in bar

📖 See `SETUP_GUIDE.md` for detailed integration instructions

## Support

For issues or feature requests, contact:
- Email: support@watersystem.com
- Phone: +91-8765432109
