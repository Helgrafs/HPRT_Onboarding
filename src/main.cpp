 #include <SPI.h>
 #include <LoRa.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_BMP280.h>

#define SS      19
#define DI0     23
Adafruit_BMP280 bmp;
void setup() {
  
  SPI.begin(5, 19, 27);
  LoRa.setPins(SS, DI0);
  
  Serial.begin(115200);
  while (!Serial);
  unsigned status;
  status = bmp.begin();
  if (!status) {
    Serial.println(F("BMP Initialisation failed"));
        while (1) delay(10);
  } else {
    Serial.println("BMP initialisation successful")
  }
  Serial.println("LoRa Transmitter");

 //if (!LoRa.begin(433E6)) {
    //Serial.println("Starting LoRa failed!");
    //while (1);
  //}
  
  
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
     Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1017)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(20000);
  }
