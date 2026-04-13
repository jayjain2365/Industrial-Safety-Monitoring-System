# Industrial Safety & Monitoring System (ESP32)

This project is a real-time Industrial Safety and Environmental Monitoring System built using ESP32.

It is designed to detect hazardous conditions such as gas leakage, fire, abnormal temperature, and humidity, and automatically trigger safety mechanisms while providing a live monitoring dashboard.

The system hosts a local web-based dashboard accessible from any device connected to the same network.

--------------------------------------------------

FEATURES

- Real-time Temperature Monitoring
- Humidity Detection
- Gas Leakage Detection (MQ-2)
- Flame Detection
- Automatic Safety System (Auto Mode)
- Buzzer Alert System
- LED Indicators (Safe / Unsafe)
- Local Web Dashboard (ESP32 Web Server)
- Mobile-Friendly UI
- Live Data Updates using AJAX
- Relay-Controlled Fan System
- Manual / Auto Fan Control
--------------------------------------------------

HARDWARE COMPONENTS USED

- ESP32 Wi-Fi Microcontroller
- DHT11 Temperature & Humidity Sensor
- MQ-2 Gas Sensor
- Flame Sensor Module
- 2-Channel Relay Module
- Active Buzzer
- LED Indicators (Red & Green)
- Cooling Fan
- Breadboard & Jumper Wires

--------------------------------------------------

SOFTWARE & TECHNOLOGIES

- Arduino IDE
- ESP32 Web Server (WiFi.h, WebServer.h)
- HTML, CSS, JavaScript

--------------------------------------------------

WORKING PRINCIPLE

The ESP32 continuously reads sensor values at an interval of approximately 1.5 seconds.

UNSAFE CONDITION:
- Fan turns ON automatically
- Buzzer activates
- Red LED turns ON
- Dashboard displays: UNSAFE CONDITION

SAFE CONDITION:
- Fan turns OFF
- Green LED turns ON
- System returns to monitoring mode

--------------------------------------------------

WEB DASHBOARD FEATURES

- Live sensor value display
- Safety indicators (Green / Red)
- Fan ON/OFF control buttons
- Mobile-friendly interface
- Real-time updates using AJAX
- JSON API endpoint (/data.json)

--------------------------------------------------

SENSOR DATA DISPLAYED

- Temperature (°C)
- Humidity (%)
- Gas Levels
- Flame Detection Status

--------------------------------------------------

APPLICATIONS

- Industrial Safety Monitoring
- Chemical & Gas Plants
- Fire Detection Systems
- Smart Factories
- Warehouse Monitoring
- Laboratory Safety

--------------------------------------------------

FUTURE ENHANCEMENTS

- Cloud Integration (Firebase / AWS / ThingSpeak)
- SMS / WhatsApp Alerts
- Android Application
- Machine Learning Prediction
- Solar + Battery Backup
- Remote Monitoring

--------------------------------------------------

WHY THIS PROJECT?

- Demonstrates IoT-based real-time monitoring
- Combines embedded systems and web technology
- Provides safety automation
- Scalable for industrial applications

AUTHOR

Jay Jain | Dhruvi Chavda | Kanchan Kumari
