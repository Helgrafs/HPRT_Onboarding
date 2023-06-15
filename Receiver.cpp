#include <Arduino.h>
#include <Adafruit_BMP280.h>
#include <LoRa.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
    Serial.println("LoRa Receiver");
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}