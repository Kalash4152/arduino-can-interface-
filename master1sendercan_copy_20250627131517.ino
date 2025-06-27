#include <SPI.h>
#include <CAN.h>

const int CS_PIN = 10;
const int INT_PIN = 2;

unsigned long lastSendTime = 0;
const unsigned long SEND_INTERVAL = 3000;

void setup() {
  Serial.begin(115200);
  CAN.setPins(CS_PIN, INT_PIN);

  while (!CAN.begin(500E3)) {
    Serial.println("CAN init failed, retrying...");
    delay(1000);
  }

  Serial.println("Master 1 ready");
}

void loop() {
  unsigned long now = millis();

  // Send every 3 seconds
  if (now - lastSendTime >= SEND_INTERVAL) {
    lastSendTime = now;

    const char* msg = "Hi Kalash";

    if (CAN.beginPacket(0x301)) {
      CAN.write((const uint8_t*)msg, strlen(msg));
      CAN.endPacket();
      Serial.println("Master 1 sent to Slave 1: Hi Kalash");
    }
  }

  // Listen for message from Master 2
  int packetSize = CAN.parsePacket();
  if (packetSize && CAN.packetId() == 0x302) {
    Serial.print("Master 1 received from Master 2: ");
    while (CAN.available()) {
      char c = (char)CAN.read();
      Serial.print(c);
    }
    Serial.println();
  }
}

