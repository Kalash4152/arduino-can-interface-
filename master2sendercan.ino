#include <SPI.h>
#include <CAN.h>

const int CS_PIN = 10;
const int INT_PIN = 2;

unsigned long lastSendTime = 0;
const unsigned long SEND_INTERVAL = 4000;

void setup() {
  Serial.begin(115200);
  CAN.setPins(CS_PIN, INT_PIN);

  while (!CAN.begin(500E3)) {
    Serial.println("CAN init failed, retrying...");
    delay(1000);
  }

  Serial.println("Master 2 ready");
}

void loop() {
  unsigned long now = millis();

  if (now - lastSendTime >= SEND_INTERVAL) {
    lastSendTime = now;

    // Send to Master 1
    const char* msgToMaster1 = "Hi Arnav";
    if (CAN.beginPacket(0x302)) {
      CAN.write((const uint8_t*)msgToMaster1, strlen(msgToMaster1));
      CAN.endPacket();
      Serial.println("Master 2 sent to Master 1: Hi Arnav");
    }

    // Send to Slave 1
    const char* msgToSlave1 = "Hello Heet";
    if (CAN.beginPacket(0x301)) {
      CAN.write((const uint8_t*)msgToSlave1, strlen(msgToSlave1));
      CAN.endPacket();
      Serial.println("Master 2 sent to Slave 1: Hello Heet");
    }
  }
}
