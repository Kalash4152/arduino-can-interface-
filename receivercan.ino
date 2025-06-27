#include <SPI.h>
#include <CAN.h>

const int CS_PIN   = 10;
const int INT_PIN  = 2;
const unsigned long WAIT_HEARTBEAT = 3000;

unsigned long lastWaitTime = 0;

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
  Serial.println("Receiver ready");
}

void loop() {
  unsigned long now = millis();

  int packetSize = CAN.parsePacket();
  if (packetSize) {
    Serial.print("Got ID=0x");
    Serial.print(CAN.packetId(), HEX);
    Serial.print(" len=");
    Serial.println(packetSize);

    // Read and print each byte in hex
    while (CAN.available()) {
      uint8_t b = CAN.read();
      if (b < 0x10) Serial.print('0');
      Serial.print(b, HEX);
      Serial.print(' ');
    }
    Serial.println();
    lastWaitTime = now;  // reset waiting timer
  }
  else if (now - lastWaitTime >= WAIT_HEARTBEAT) {
    lastWaitTime = now;
    Serial.println("Receiver waiting for messages...");
  }
}
