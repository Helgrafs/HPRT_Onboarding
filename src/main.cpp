#include <Arduino.h>
#include <Adafruit_BMP280.h>
#include <LoRa.h>

 Adafruit_BMP280 bmp; //links the driver for the barometer to that variable


int message = 0; //message for the sender

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)){      //checks if frequency works
     Serial.println("failed");
     while(1);
   }

   Serial.println(F("BMP280 test"));
   unsigned status; //variable to check if it functions
   status = bmp.begin(0x76, 0x56); //this actually initializes sensor
  }


void loop() {
  Serial.println("Sending: ");
  Serial.print(message);

  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(message);
  LoRa.endPacket();

  message+3;
  delay(5000);

  Serial.print(F("Temperature  = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure()/100); 
  Serial.println("  hPa");

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(1019.66)); 
  Serial.println("  m");                   

  Serial.println();   delay(2000);
}