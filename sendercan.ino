#include <SPI.h>
#include <CAN.h>

const int CS_PIN   = 10;
const int INT_PIN  = 2;
const unsigned long SEND_INTERVAL    = 1000;
const unsigned long HEARTBEAT_INTERVAL = 2000;

unsigned long lastSendTime     = 0;
unsigned long lastHeartbeatTime = 0;

bool initCAN() {
  CAN.setPins(CS_PIN, INT_PIN);
  if (CAN.begin(500E3)) return true;
  Serial.println("Starting CAN failed!");
  return false;
}

void setup() {
  Serial.begin(115200);
  while (!initCAN()) {
    Serial.println("Retry CAN init in 1 s…");
    delay(1000);
  }
  Serial.println("Sender ready");
}

void loop() {
  unsigned long now = millis();

  // Send hex packet every SEND_INTERVAL
  if (now - lastSendTime >= SEND_INTERVAL) {
    lastSendTime = now;
    if (CAN.beginPacket(0x123)) {
      uint8_t payload[] = { 0xAB, 0xCD };
      CAN.write(payload, sizeof(payload));
      if (CAN.endPacket()) {
        Serial.println("Message sent successfully");
      } else {
        Serial.println("Error: endPacket() failed");
      }
    } else {
      Serial.println("Error: beginPacket() failed");
    }
  }

  // Heartbeat every HEARTBEAT_INTERVAL
  if (now - lastHeartbeatTime >= HEARTBEAT_INTERVAL) {
    lastHeartbeatTime = now;
    Serial.println("Sender heartbeat");
  }
}
