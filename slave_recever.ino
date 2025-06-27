#include <SPI.h>
#include <CAN.h>

const int CS_PIN = 10;
const int INT_PIN = 2;

unsigned long lastHeartbeat = 0;
const unsigned long HEARTBEAT_INTERVAL = 3000;

void setup() {
  Serial.begin(74880);
  CAN.setPins(CS_PIN, INT_PIN);

  while (!CAN.begin(500E3)) {
    Serial.println("CAN init failed, retrying...");
    delay(1000);
  }

  Serial.println("Slave 1 ready, listening for ID 0x301");
}

void loop() {
  unsigned long now = millis();

  int packetSize = CAN.parsePacket();
  if (packetSize && CAN.packetId() == 0x301) {
    Serial.print("Slave 1 received: ");
    String msg = "";
    while (CAN.available()) {
      char c = (char)CAN.read();
      msg += c;
    }
    Serial.println(msg);

    // Identify sender based on message content
    if (msg == "Hi Kalash") {
      Serial.println("→ This came from Master 1");
    } else if (msg == "Hello Heet") {
      Serial.println("→ This came from Master 2");
    } else {
      Serial.println("→ Sender unknown");
    }
  }

  if (now - lastHeartbeat >= HEARTBEAT_INTERVAL) {
    lastHeartbeat = now;
    Serial.println("Slave 1 alive, waiting for messages...");
  }
}