#include <WiFi.h>

#include <WebServer.h>



// ---------------- Pins ----------------

#define PIR_PIN   23    // PIR sensor

#define LED1_PIN  21    // Light 1

#define LED2_PIN  19    // Light 2

#define LED3_PIN  18    // Light 3

#define FAN_PIN   5     // Fan

#define LDR_PIN   34    // LDR pin (analog)



// ---------------- WiFi ----------------

const char* ssid = "jainam";        // << CHANGE THIS

const char* password = "87654321"; // << CHANGE THIS



WebServer server(80);



// ---------------- Variables ----------------

int lightThreshold = 2000; // adjust this for brightness

bool manualMode = false;   // default AUTO mode



// State variables for devices

bool stateLight1 = false;

bool stateLight2 = false;

bool stateLight3 = false;

bool stateFan    = false;



// ---------------- Functions ----------------

void updateOutputs() {

  digitalWrite(LED1_PIN, stateLight1 ? HIGH : LOW);

  digitalWrite(LED2_PIN, stateLight2 ? HIGH : LOW);

  digitalWrite(LED3_PIN, stateLight3 ? HIGH : LOW);

  digitalWrite(FAN_PIN,  stateFan ? HIGH : LOW);

}



void sendStatus() {

  String json = "{";

  json += "\"manual\":" + String(manualMode ? "true" : "false");

  json += ",\"light1\":" + String(stateLight1 ? "true" : "false");

  json += ",\"light2\":" + String(stateLight2 ? "true" : "false");

  json += ",\"light3\":" + String(stateLight3 ? "true" : "false");

  json += ",\"fan\":" + String(stateFan ? "true" : "false");

  json += "}";

  server.send(200, "application/json", json);

}



// ---------------- Setup ----------------

void setup() {

  Serial.begin(115200);



  pinMode(PIR_PIN, INPUT);

  pinMode(LED1_PIN, OUTPUT);

  pinMode(LED2_PIN, OUTPUT);

  pinMode(LED3_PIN, OUTPUT);

  pinMode(FAN_PIN, OUTPUT);



  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);



  int retries = 0;

  while (WiFi.status() != WL_CONNECTED && retries < 30) { // 15s timeout

    delay(500);

    Serial.print(".");

    retries++;

  }



  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("\n✅ Connected to WiFi");

    Serial.print("ESP32 IP Address: ");

    Serial.println(WiFi.localIP());

  } else {

    Serial.println("\n❌ Failed to connect to WiFi");

  }



  // ---- Routes ----

  server.on("/manual=on", []() {

    manualMode = true;

    server.send(200, "text/plain", "Manual Mode ON");

  });

  server.on("/manual=off", []() {

    manualMode = false;

    server.send(200, "text/plain", "Manual Mode OFF");

  });



  server.on("/light1=on", []() { if (manualMode) stateLight1 = true;  updateOutputs(); server.send(200, "text/plain", "Light1 ON"); });

  server.on("/light1=off", []() { if (manualMode) stateLight1 = false; updateOutputs(); server.send(200, "text/plain", "Light1 OFF"); });



  server.on("/light2=on", []() { if (manualMode) stateLight2 = true;  updateOutputs(); server.send(200, "text/plain", "Light2 ON"); });

  server.on("/light2=off", []() { if (manualMode) stateLight2 = false; updateOutputs(); server.send(200, "text/plain", "Light2 OFF"); });



  server.on("/light3=on", []() { if (manualMode) stateLight3 = true;  updateOutputs(); server.send(200, "text/plain", "Light3 ON"); });

  server.on("/light3=off", []() { if (manualMode) stateLight3 = false; updateOutputs(); server.send(200, "text/plain", "Light3 OFF"); });



  server.on("/fan=on",    []() { if (manualMode) stateFan = true;    updateOutputs(); server.send(200, "text/plain", "Fan ON"); });

  server.on("/fan=off",   []() { if (manualMode) stateFan = false;   updateOutputs(); server.send(200, "text/plain", "Fan OFF"); });



  // ---- Status endpoint ----

  server.on("/status", sendStatus);



  server.begin();

  Serial.println("HTTP server started");

}



// ---------------- Loop ----------------

void loop() {

  server.handleClient();



  // Reconnect if WiFi lost

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("⚠ WiFi lost! Reconnecting...");

    WiFi.reconnect();

    delay(1000);

    return;

  }



  // AUTO Mode (PIR + LDR controlling Light1..3)

  if (!manualMode) {

    int pirValue = digitalRead(PIR_PIN);

    int ldrValue = analogRead(LDR_PIN);



    Serial.print("PIR: "); Serial.print(pirValue);

    Serial.print(" | LDR: "); Serial.println(ldrValue);



    if (pirValue == HIGH) {

      Serial.println("⚡ Motion detected → LEDs ON");

      stateLight1 = stateLight2 = stateLight3 = true;

    } 

    else if (ldrValue < lightThreshold) {

      Serial.println("🌑 Dark environment (no motion) → LEDs ON");

      stateLight1 = stateLight2 = stateLight3 = true;

    } 

    else {

      Serial.println("❌ No motion & Bright → LEDs OFF");

      stateLight1 = stateLight2 = stateLight3 = false;

    }



    updateOutputs();

    delay(500);

  }

}
