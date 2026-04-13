#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "Jay";
const char* password = "imnoone@123";

// Pin configuration
#define DHTPIN 4
#define DHTTYPE DHT11
#define MQPIN 34
#define FLAMEPIN 17
#define RELAYPIN 26
#define BUZZERPIN 15
#define LEDGREEN 14
#define LEDRED 12

// Logic configuration
const bool RELAY_ACTIVE_LOW = true;
const bool BUZZER_ACTIVE_HIGH = true;

// Thresholds
const int MQ_THRESHOLD = 350;
const float TEMP_THRESHOLD = 60.0;
const unsigned long SAMPLE_INTERVAL_MS = 1500;

// Global variables
float latestTemp = 0, latestHum = 0;
int latestMQRaw = 0, latestFlame = 1;
unsigned long lastSampleMillis = 0;
bool manualOverride = false;

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

// ---------- Forward Declarations (Fixes your error) ----------
void setRelay(bool on);
void setBuzzer(bool on);
// ------------------------------------------------------------

// ---------- Function Definitions ----------
void setRelay(bool on) {
  digitalWrite(RELAYPIN, RELAY_ACTIVE_LOW ? (on ? LOW : HIGH) : (on ? HIGH : LOW));
}

void setBuzzer(bool on) {
  digitalWrite(BUZZERPIN, BUZZER_ACTIVE_HIGH ? (on ? HIGH : LOW) : (on ? LOW : HIGH));
}

void handleRoot() {
  String page = R"rawliteral(
<!doctype html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>Industrial Safety Dashboard</title>
  <style>
    body { font-family: Arial, sans-serif; margin: 10px; background:#f5f7fa; }
    h2 { text-align:center; color:#333; }
    .grid { display:grid; grid-template-columns:repeat(auto-fit,minmax(180px,1fr)); gap:12px; margin-top:10px; }
    .card { border-radius: 12px; padding: 15px; box-shadow: 0 3px 6px rgba(0,0,0,0.15); background:white; text-align:center; }
    .title { font-weight:bold; color:#555; margin-bottom:6px; font-size:17px; }
    .value { font-size:22px; margin-top:5px; color:#0078D7; }
    .alert { color:red; font-weight:bold; }
    .safe { color:green; font-weight:bold; }
    .btnBox { text-align:center; margin-top:20px; }
    button { padding:8px 16px; margin:5px; border:none; border-radius:6px; cursor:pointer; background:#2196F3; color:white; font-size:15px; transition:0.3s; }
    button:hover { background:#1976D2; }
  </style>
</head>
<body>
  <h2>⚙️ Industrial Safety Dashboard</h2>
  
  <div class="grid">
    <div class="card">
      <div class="title">🌡 Temperature (°C)</div>
      <div id="temp" class="value">--</div>
    </div>
    <div class="card">
      <div class="title">💧 Humidity (%)</div>
      <div id="hum" class="value">--</div>
    </div>
    <div class="card">
      <div class="title">💨 Gas (MQ-2)</div>
      <div id="gas" class="value">--</div>
    </div>
    <div class="card">
      <div class="title">🔥 Flame</div>
      <div id="flame" class="value safe">--</div>
    </div>
    <div class="card">
      <div class="title">🛡 System Status</div>
      <div id="alarmMsg" class="value safe">--</div>
    </div>
  </div>

  <div class="btnBox">
    <button onclick="toggleFan()">🌀 Toggle Fan</button>
    <button onclick="autoMode()">🤖 Auto Mode</button>
  </div>

  <script>
    async function updateData() {
      try {
        const res = await fetch('/data.json');
        const j = await res.json();
        document.getElementById('temp').textContent = j.temperature.toFixed(1);
        document.getElementById('hum').textContent = j.humidity.toFixed(1);
        document.getElementById('gas').textContent = j.mqRaw;
        const flameEl = document.getElementById('flame');
        if (j.flame == 1) {
          flameEl.textContent = 'SAFE';
          flameEl.className = 'value safe';
        } else {
          flameEl.textContent = '🔥 DETECTED';
          flameEl.className = 'value alert';
        }
        const msg = document.getElementById('alarmMsg');
        if (j.alarm) {
          msg.textContent = '⚠️ Unsafe Condition!';
          msg.className = 'value alert';
        } else {
          msg.textContent = '✅ All Safe';
          msg.className = 'value safe';
        }
      } catch(e) {
        console.error(e);
      }
    }
    async function toggleFan() { await fetch('/fan/toggle'); }
    async function autoMode() { await fetch('/fan/auto'); }
    setInterval(updateData, 1000);
    window.onload = updateData;
  </script>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", page);
}

void handleData() {
  bool gasAlarm = (latestMQRaw > MQ_THRESHOLD);
  bool tempAlarm = (latestTemp > TEMP_THRESHOLD);
  bool flameAlarm = (latestFlame == 0);
  bool alarm = gasAlarm || tempAlarm || flameAlarm;

  String json = "{";
  json += "\"temperature\":" + String(latestTemp, 1) + ",";
  json += "\"humidity\":" + String(latestHum, 1) + ",";
  json += "\"mqRaw\":" + String(latestMQRaw) + ",";
  json += "\"flame\":" + String(latestFlame) + ",";
  json += "\"alarm\":" + String(alarm ? "true" : "false");
  json += "}";
  server.send(200, "application/json", json);
}

void handleFanToggle() {
  manualOverride = true;
  int state = digitalRead(RELAYPIN);
  bool isOn = (RELAY_ACTIVE_LOW ? (state == LOW) : (state == HIGH));
  setRelay(!isOn);
  server.send(200, "text/plain", "Fan toggled");
}

void handleFanAuto() {
  manualOverride = false;
  server.send(200, "text/plain", "Auto mode enabled");
}

void sampleSensors() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(t) || isnan(h)) { delay(100); t = dht.readTemperature(); h = dht.readHumidity(); }

  int mqRaw = analogRead(MQPIN);
  int flame = digitalRead(FLAMEPIN);

  latestTemp = t;
  latestHum = h;
  latestMQRaw = mqRaw;
  latestFlame = flame;

  Serial.print("Temp: "); Serial.print(t);
  Serial.print(" °C | Hum: "); Serial.print(h);
  Serial.print(" % | MQ: "); Serial.print(mqRaw);
  Serial.print(" | Flame: "); Serial.print(flame == 1 ? "SAFE" : "DETECTED");
  Serial.print(" | Fan: ");
  Serial.println((digitalRead(RELAYPIN) == (RELAY_ACTIVE_LOW ? LOW : HIGH)) ? "ON" : "OFF");

  if (!manualOverride) {
    bool gasAlarm = (mqRaw > MQ_THRESHOLD);
    bool tempAlarm = (t > TEMP_THRESHOLD);
    bool flameAlarm = (flame == 0);
    bool alarm = gasAlarm || tempAlarm || flameAlarm;

    setRelay(alarm);
    setBuzzer(alarm);
    digitalWrite(LEDRED, alarm ? HIGH : LOW);
    digitalWrite(LEDGREEN, alarm ? LOW : HIGH);
  }
}

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println("\nIndustrial Safety System Booting...");

  pinMode(FLAMEPIN, INPUT);
  pinMode(RELAYPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(LEDGREEN, OUTPUT);
  pinMode(LEDRED, OUTPUT);
  setRelay(false); 
  setBuzzer(false);

  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) { delay(300); Serial.print("."); }
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP: "); Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/data.json", handleData);
  server.on("/fan/toggle", handleFanToggle);
  server.on("/fan/auto", handleFanAuto);
  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  server.handleClient();
  unsigned long now = millis();
  if (now - lastSampleMillis >= SAMPLE_INTERVAL_MS) {
    lastSampleMillis = now;
    sampleSensors();
  }
}
