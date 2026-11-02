# Smart Washroom Automation & Monitoring System (Arduino)

An embedded IoT automation system designed for commercial and institutional facilities to automate sanitation, monitor environmental safety, and conserve utilities. Implemented on Arduino Uno as the Level 3 Jackfruit Final Project for the Microprocessors and Computer Architecture curriculum (UE24CS242A) at PES University.

---

## 📌 Project Overview

The Smart Washroom System automates key physical touchpoints and monitors facility health in real time:
1. **Touchless Automated Tap**: Uses an Infrared (IR) obstacle avoidance sensor to activate water flow when hands are detected, preventing cross-contamination and eliminating water wastage.
2. **Occupancy-Triggered Automatic Lighting**: Uses an HC-SR04 ultrasonic distance sensor to detect user entry ($< 30\text{ cm}$) and automatically illuminate the facility via a high-output LED.
3. **Air Quality & Toxic Gas Monitoring**: Uses an MQ series gas sensor (Analog A0) to monitor odor and harmful volatile organic compounds (VOCs). If gas concentration crosses threshold ($> 600$), an audible safety buzzer alarm triggers.
4. **Water Leakage & Overflow Alert**: Uses an analog resistive moisture fork probe (Analog A1) to detect floor pooling or pipe leakage ($< 750$). Triggers a dedicated warning LED and emergency alert.
5. **Real-Time I2C LCD Priority Telemetry**: Displays the current status on a $16 \times 2$ Liquid Crystal Display over the I2C bus (`0x27`) with prioritized diagnostic alerts.
6. **UART Serial Telemetry Feed**: Broadcasts continuous sensor metrics over 9600 baud serial connection for logging and debugging.

---

## 🔌 Hardware Circuit & Pinout Table

All components are powered via the Arduino Uno 5V and Ground rails through a solderless breadboard.

| Component | Sensor / Actuator | Arduino Pin | Type | Trigger / Threshold Logic |
| :--- | :--- | :--- | :--- | :--- |
| **Ultrasonic Trigger** | HC-SR04 | `Digital 9` | Output | 10 $\mu s$ pulse emission |
| **Ultrasonic Echo** | HC-SR04 | `Digital 10` | Input | Distance calculation: $t \times 0.034 / 2$ |
| **Occupancy Light** | 5mm High-Intensity LED | `Digital 13` | Output | Active when Distance $< 30\text{ cm}$ |
| **Touchless Tap** | IR Proximity Module | `Digital 2` | Input (Pullup) | Active when `LOW` (Hand detected) |
| **Odor / Gas Sensor** | MQ Series Analog Sensor | `Analog A0` | Input | Triggers alarm when raw ADC $> 600$ |
| **Safety Buzzer** | Piezoelectric Buzzer | `Digital 8` | Output | Sounds alarm on high gas detection |
| **Moisture / Leakage** | Resistive Fork Probe | `Analog A1` | Input | Triggers warning when raw ADC $< 750$ |
| **Leakage Warning LED**| 5mm Red Indicator LED | `Digital 12` | Output | Active on floor moisture detection |
| **LCD Screen SDA** | $16 \times 2$ I2C Display | `Analog A4` | Bidirectional | I2C Serial Data line |
| **LCD Screen SCL** | $16 \times 2$ I2C Display | `Analog A5` | Output | I2C Serial Clock line |

---

## 📊 LCD Priority Alert Hierarchy

The $16 \times 2$ I2C LCD implements priority-based message queuing on Row 2 to ensure safety-critical alerts override routine status updates:

1. **Priority 1 (Critical)**: `LEAKAGE DETECTED` (if moisture ADC $< 750$)
2. **Priority 2 (Warning)**: `BAD ODOR ALERT` (if gas ADC $> 600$)
3. **Priority 3 (Utility)**: `TAP STATUS: ON` (if IR tap active `LOW`)
4. **Priority 4 (Occupancy)**: `MOTION DETECTED` (if ultrasonic distance $< 30\text{ cm}$)
5. **Default State**: `MONITORING...` (all parameters nominal)

---

## 📂 Repository Contents

```
smart-washroom-arduino-system/
├── src/
│   └── smart_washroom_system.ino      # Core Arduino firmware & sensor logic
├── circuit/
│   ├── connections.txt               # Step-by-step breadboard wiring instructions
│   └── connections.jpeg              # High-resolution physical circuit photograph
├── docs/
│   └── Smart_Washroom_System_Project_Report.pdf  # Comprehensive project report
├── README.md                         # Architecture, pinouts, and documentation
└── .gitignore
```

---

## 🛠️ Installation & Upload Instructions

1. **Prerequisites**: Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. **Required Libraries**:
   * `Wire.h` (Built-in Arduino I2C communication)
   * `LiquidCrystal_I2C.h` by Frank de Brabander (Install via Arduino Library Manager)
3. **Upload**:
   * Open [`src/smart_washroom_system.ino`](./src/smart_washroom_system.ino).
   * Select **Board: Arduino Uno** and the appropriate COM port.
   * Click **Upload**.
4. **Serial Monitor**:
   * Open the Serial Monitor at **9600 baud** to view real-time distance, gas, and moisture telemetry.

---

## 👤 Author
* **Tanmayi Nagabhairava** ([@Tanmayi-n14](https://github.com/Tanmayi-n14)) — `PES1UG24CS493`
* Department of Computer Science & Engineering, PES University
