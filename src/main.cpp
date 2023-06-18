 #include <SPI.h>
 #include <LoRa.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;
void setup() {
  // VERY IMPORTANT!!!! WHEN CONNECTING BMP280, SCL goes to pin 11 And SDA goes to pin 12!!!!!!!!!!!
  Serial.begin(115200);
  while (!Serial);
  unsigned status;
  status = bmp.begin();
  // if (!status) {
  //   Serial.println(F("BMP Initialisation failed"));
  //       while (1) delay(10);
  // } else {
  //   Serial.println("BMP initialisation successful");
  // }
  Serial.println("LoRa Transmitter");
LoRa.begin(433E6);
//  if (!LoRa.begin(433E6)) {
//    Serial.println("Starting LoRa failed!");
//    while (1);
//   }else {
//    Serial.println("LoRa initialisation successful");
//  }
  
  
}
void Barometer() {
       Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1017)); // as close as i could get to actual latvia sea pressure
    Serial.println(" m");

    Serial.println();
}
void loop() {
  // try to parse packet
  //int packetSize = LoRa.parsePacket();
  //if (packetSize) {
    // received a packet
    //Serial.print("Received packet '");

    // read packet
   // while (LoRa.available()) {
      //Serial.print((char)LoRa.read());
    //}

    // print RSSI of packet
    //Serial.print("' with RSSI ");
    //Serial.println(LoRa.packetRssi());
    Barometer();
    delay(20000);
  }
