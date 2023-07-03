#include <Arduino.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_I2CDevice.h>
#include <LoRa.h>
#define SS 18 
#define RST 14
#define DI0 26
#define SCK 5
#define MISO 19
#define MOSI 27
int syncWord = 0xF7;
byte _localAddress = 0xFF;
byte _destination = 0xBB;
boolean _canPrintHeaderMessage = false;
void Receiver(int packetSize) {
  if(packetSize == 0) return;
  int recipient = LoRa.read();
  byte sender = LoRa.read();
  byte MessageID = LoRa.read();
  byte receivedLength = LoRa.read();
  String Received = "";
  while(LoRa.available()){
    Received += (char)LoRa.read();
  }
  if (receivedLength != Received.length()){
    Serial.println("length mismatch");
    return;
  }
  if (recipient != _localAddress && recipient != 0xFF ){
    Serial.println("wrong address");
  }
  Serial.println("Transmission: " + Received);
  Serial.println();
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
   }else {
    Serial.println("LoRa initialisation successful");
 }
  LoRa.setTxPower(20);
  LoRa.setSpreadingFactor(7);
  LoRa.setCodingRate4(8);
  LoRa.setSignalBandwidth(25E4);  

}


void loop() {
  Receiver(LoRa.parsePacket());
}