# 🏠 Smart Home Automation System  
### 🚀 Built at <Tech-Tonic> Hackathon 2025 | CMPICA, CHARUSAT  

---

## 👨‍💻 Team Members  
- **Jainam Khetani**  
- **Jash Joshi**  
- **Palak Donga**  
- **Khushi Ka.Patel**  

> *Team Smart Space Innovators — passionate about blending IoT, automation, and web technologies to create smarter homes.*

---

## 🧠 Project Overview  

The **Smart Home Automation System** is an **IoT-based intelligent control system** that enables users to manage household appliances such as lights and fans **automatically** or **manually** via a **web interface**.  

Developed during the **<Tech-Tonic> Hackathon 2025**, this project demonstrates how **ESP32**, **sensors**, and **web technologies** can collaborate to make a living environment smarter, more energy-efficient, and user-friendly.  

---

## 🎯 Problem Statement  

Many households waste electricity due to **unattended appliances** like lights or fans left running.  
The goal of this project was to design a **cost-effective**, **sensor-driven**, and **Wi-Fi-controlled automation system** that:  
- Saves energy 💡  
- Provides comfort 🏡  
- Enables remote accessibility 📱  

---

## ⚙️ Key Features  

### 🤖 **1. Automation Mode**  
- Uses **PIR (Passive Infrared) sensor** to detect motion in the room.  
- Uses **LDR (Light Dependent Resistor)** to detect ambient light levels.  
- Automatically switches **lights** and **fans** ON when motion is detected or environment is dark.  
- Turns them **OFF** when no motion is detected or room is bright enough.  

### 📱 **2. Manual Mode (Web App Control)**  
- Built-in **Web Server** running on ESP32 allows users to manually control devices through a **mobile or desktop browser**.  
- The interface is simple, intuitive, and accessible from any device connected to the same Wi-Fi network.  

### 🌐 **3. Real-time Status Monitoring**  
- The `/status` endpoint returns real-time JSON data showing the ON/OFF state of each device and the mode currently active (manual or automatic).  

---

## 🧰 Components Used  

| Component | Quantity | Description |
|------------|-----------|-------------|
| 🧩 **ESP32 DevKit V1** | 1 | Main microcontroller with Wi-Fi and GPIO pins |
| 🕵️ **PIR Sensor (HC-SR501)** | 1 | Detects human motion in the environment |
| ☀️ **LDR (Light Dependent Resistor)** | 1 | Measures ambient light intensity |
| 💡 **LEDs or Relays** | 3 | Represent lights or control AC devices |
| 🌬️ **Fan (or DC Motor + Relay)** | 1 | Controlled automatically or manually |
| 🔌 **10kΩ Resistor** | 1 | Used for LDR voltage divider circuit |
| ⚡ **Jumper Wires, Breadboard** | — | Circuit connections and prototyping |
| 🔋 **USB Power / 5V Supply** | — | Powering ESP32 and sensors |

---

## 🔌 Circuit Connections  

| Device | ESP32 Pin | Type | Description |
|---------|------------|------|-------------|
| **PIR Sensor** | GPIO 23 | Input | Detects motion |
| **Light 1 (LED/Relay 1)** | GPIO 21 | Output | Light 1 control |
| **Light 2 (LED/Relay 2)** | GPIO 19 | Output | Light 2 control |
| **Light 3 (LED/Relay 3)** | GPIO 18 | Output | Light 3 control |
| **Fan (Relay/Transistor)** | GPIO 5 | Output | Fan control |
| **LDR (via voltage divider)** | GPIO 34 | Analog Input | Light intensity sensor |
| **5V Power (VIN)** | — | Power | For PIR & Relay modules |
| **3.3V Power** | — | Power | For LDR sensor circuit |
| **GND** | — | Common Ground | Connect all GNDs together |

> **Note:**  
> - Use **VIN (5V)** for PIR & relay modules (they need 5V).  
> - Use **3.3V** for LDR (to protect analog pin).  
> - Connect all **GNDs** together.  

---

## 🌐 Web Server API Endpoints  

| Endpoint | Description |
|-----------|-------------|
| `/manual=on` | Switches control mode to **Manual** |
| `/manual=off` | Switches control mode to **Automatic** |
| `/light1=on`, `/light1=off` | Turns Light 1 ON/OFF |
| `/light2=on`, `/light2=off` | Turns Light 2 ON/OFF |
| `/light3=on`, `/light3=off` | Turns Light 3 ON/OFF |
| `/fan=on`, `/fan=off` | Controls Fan ON/OFF |
| `/status` | Returns JSON response of all device states |

---

## 🖥️ How It Works  

### 🧾 Step-by-Step Flow  
1. The ESP32 connects to the local Wi-Fi network on startup.  
2. Once connected, it launches a **web server** that listens for commands.  
3. If the system is in **Auto Mode**:
   - PIR detects motion, and LDR checks brightness.  
   - Lights and fan toggle automatically based on sensor input.  
4. If the system is in **Manual Mode**:
   - User accesses the ESP32’s IP (e.g., `http://192.168.x.x/`) on a browser.  
   - Toggles lights/fan using the buttons or endpoints.  
5. `/status` returns a JSON showing current mode and state of all devices.

---

## 📡 Example Serial Output  

✅ Connected to WiFi
ESP32 IP Address: 192.168.43.205
HTTP server started
PIR: 1 | LDR: 1800
⚡ Motion detected → LEDs ON
🌑 Dark environment (no motion) → LEDs ON
❌ No motion & Bright → LEDs OFF

---


## 🧩 Software Used  

- **Arduino IDE 2.x** — for programming ESP32  
- **ESP32 Board Library**  
- **WebServer.h** — for hosting local web server  
- **WiFi.h** — for handling Wi-Fi connectivity  

---

## 🧱 Project Architecture  

    ┌────────────────────────────┐
    │        ESP32 Board         │
    │                            │
    │ ┌──────────┐ ┌──────────┐  │
    │ │   PIR     │ │   LDR     │
    │ └──────────┘ └──────────┘  │
    │       │            │        │
    │  Motion & Light  Sensor Data │
    │       ▼            ▼        │
    │ ┌──────────────────────────┐│
    │ │   Decision Controller    ││
    │ └──────────────────────────┘│
    │       │            │        │
    │  Control Relays / LEDs / Fan│
    │       ▼            ▼        │
    │ ┌──────────────────────────┐│
    │ │     Web Server API       ││
    │ └──────────────────────────┘│
    └────────────────────────────┘


---

## 🌟 Achievements  

🏆 **Successfully demonstrated** the project at **<Tech-Tonic> Hackathon 2025**, organized by CMPICA, CHARUSAT.  
💡 Showcased real-time control and automation of devices via IoT.  
🔌 Created a bridge between hardware (ESP32) and software (Web interface).  

---

## 🧭 Future Scope  

- 🗣️ Integration with Google Assistant / Alexa  
- 📱 Development of a dedicated mobile app (Flutter)  
- ⏰ Scheduling system for time-based automation  
- 🌡️ Add temperature/humidity sensors for better environment control  
- ☁️ Cloud-based remote monitoring (Firebase / MQTT)  

---

## 🔗 Project Repository  

📁 **GitHub Repository:** [👉 View the Code Here](#https://github.com/24CS039Jainam/Smart-Home-Automation)  

---

## 🏁 Conclusion  

The **Smart Home Automation System** represents a step toward the **future of intelligent living**.  
By integrating hardware sensors, embedded control, and wireless communication, our project aims to make home environments more **responsive**, **efficient**, and **sustainable** 🌱.  

We learned not only about IoT and embedded systems, but also about collaboration, time management, and rapid prototyping — making this hackathon journey truly unforgettable! 💪  

---

### ❤️ Developed by  
**Team Smart Space Innovators** | *<Tech-Tonic> Hackathon 2025*  
> *"Turning ideas into innovation, one circuit at a time."* ⚡  


