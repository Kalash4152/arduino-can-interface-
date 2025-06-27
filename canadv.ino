#include <SPI.h>
#include <CAN.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int CS_PIN = 10;
const int INT_PIN = 2;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust address if needed

void setup() {
  Serial.begin(115200);
  CAN.setPins(CS_PIN, INT_PIN);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Slave Ready");

  while (!CAN.begin(500E3)) {
    Serial.println("CAN init failed. Retrying...");
    delay(1000);
  }

  Serial.println("Slave Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  int packetSize = CAN.parsePacket();
  if (packetSize && CAN.packetId() == 0x101) {
    char buffer[9] = {0}; // 8 chars + null terminator
    int i = 0;

    while (CAN.available() && i < 8) {
      buffer[i++] = CAN.read();
    }

    buffer[i] = '\0'; // Null terminate the string

    Serial.print("Received: ");
    Serial.println(buffer);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("🚦 SIGNAL:");
    lcd.setCursor(0, 1);
    lcd.print(buffer);
  }
}
