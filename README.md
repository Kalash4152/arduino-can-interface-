🚗 CAN Bus Multi-Device Communication (Arduino + MCP2515)
🔧 Project Overview
This project demonstrates how multiple Arduino boards can communicate over a Controller Area Network (CAN) bus using the MCP2515 CAN modules and the arduino-CAN library by Sandeep Mistry.
We’ve implemented a master-slave architecture where:

📤 Sender (Master) sends different coded messages to...

📥 Two Slaves, each listening on its own CAN ID, decoding and responding to specific data.

🧰 Hardware Used
Component	Quantity	Purpose
Arduino Uno	3️⃣	1 Master + 2 Slaves
MCP2515 CAN Module	3️⃣	For CAN communication
T-Coupler / Jumper Wires	✅	Connecting CANH, CANL, GND, VCC
120Ω resistors	2️⃣	Termination resistors on each end
Relay Module	1️⃣	Actuated by Slave 1
LED + Resistor	1️⃣	Controlled by Slave 2

📡 Message Flow
🟢 Sender Code:
Sends two unique messages over the CAN bus:

Sends "ABCD" to Slave 1 (ID: 0x101)

Sends "EFGH" to Slave 2 (ID: 0x102)

c
Copy
Edit
CAN.beginPacket(0x101); CAN.write("ABCD"); CAN.endPacket();
CAN.beginPacket(0x102); CAN.write("EFGH"); CAN.endPacket();
🟠 Slave 1:
Listens for CAN ID 0x101

Prints "ABCD" to serial

Can optionally trigger a relay when this message is received.

🔵 Slave 2:
Listens for CAN ID 0x102

Prints "EFGH" to serial

Can optionally toggle an LED based on message content.

🔌 Wiring Highlights
All MCP2515s connected via CANH ↔ CANH, CANL ↔ CANL, GND ↔ GND

Use 120Ω resistors at the two ends of the CAN line

Each MCP2515 connects to its Arduino via SPI (pins 10 for CS, 2 for INT by default)

💡 What You’ll Learn
✅ CAN bus basics
✅ How to use MCP2515 with Arduino
✅ Sending and decoding custom messages
✅ Building scalable master-slave CAN systems
✅ Real-time control of relays and LEDs via message decoding

🚀 Possible Extensions
⏹ Acknowledge reception from slaves

🧠 Implement error-checking / retry logic

📈 Add sensors and transmit readings

🌐 Add serial-to-CAN bridge using a computer or Raspberry Pi

🟨 Add OLED/LCD for real-time message display
