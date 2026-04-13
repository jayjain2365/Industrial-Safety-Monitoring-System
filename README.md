🔥 Industrial Safety & Monitoring System (ESP32)

This project is a real-time Industrial Safety and Environmental Monitoring System built using ESP32. It is designed to detect hazardous conditions such as gas leakage, fire, abnormal temperature, and humidity, and automatically trigger safety mechanisms while providing a live monitoring dashboard.

The system hosts a local web-based dashboard accessible from any device connected to the same network, enabling real-time monitoring without internet dependency.

🚀 Features
    🌡 Real-time Temperature Monitoring
    💧 Humidity Detection
    💨 Gas Leakage Detection (MQ-2)
    🔥 Flame Detection
    🚨 Automatic Safety System (Auto Mode)
    🔔 Buzzer Alert System
    🔴 Visual LED Indicators (Safe / Unsafe)
    🌐 Local Web Dashboard (ESP32 Web Server)
    📱 Mobile-Friendly UI
    🔄 Live Data Updates using AJAX
    🔌 Relay-Controlled Fan System
    🔁 Manual / Auto Fan Control
    📡 JSON API Output for Integration
🛠 Hardware Components Used
    ESP32 Wi-Fi Microcontroller
    DHT11 Temperature & Humidity Sensor
    MQ-2 Gas Sensor
    Flame Sensor Module
    2-Channel Relay Module
    Active Buzzer
    LED Indicators (Red & Green)
    Cooling Fan
    Breadboard & Jumper Wires
⚙️ Software & Technologies
    Arduino IDE
    ESP32 Web Server (WiFi.h, WebServer.h)
    HTML + CSS + JavaScript
⚡ Working Principle

The ESP32 continuously reads sensor values at a fixed interval (~1.5 seconds).

🚨 Unsafe Condition (Triggered when threshold exceeded):
    Fan turns ON automatically
    Buzzer starts alert sound
    Red LED turns ON
    Web dashboard displays: ⚠️ UNSAFE CONDITION
    ✅ Safe Condition:
    Fan turns OFF
    Green LED turns ON
    System returns to normal monitoring mode
🌐 Web Dashboard Features
    Real-time sensor data display
    Visual safety indicators (Green / Red)
    Manual Fan ON/OFF control buttons
    Responsive design for mobile devices
    Live updates using AJAX
    JSON-based API (/data.json)
    📊 Sensor Data Displayed
    🌡 Temperature (°C)
    💧 Humidity (%)
    💨 Gas Levels (Analog value)
    🔥 Flame Detection Status
    🏭 Applications
    Industrial Safety Monitoring
    Chemical & Gas Plants
    Fire Detection Systems
    Smart Factories
    Warehouse Monitoring
    Laboratory Safety
    🔮 Future Enhancements
    ☁️ Cloud Integration (Firebase / AWS / ThingSpeak)
    📲 SMS / WhatsApp Alerts
    📱 Dedicated Android Application
    🤖 Machine Learning for predictive safety
    🔋 Solar + Battery Backup System
    🌍 Remote Monitoring over Internet
💡 Why This Project?

This system demonstrates:

    Real-time IoT monitoring
    Embedded system design
    Safety automation
    Web-based visualization
    Scalable industrial architecture
🧠 Author:
Jay Jain | Dhruvi Chavda | Kanchan Kumari
