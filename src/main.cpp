#include <Arduino.h>
#include <Adafruit_BMP280.h>

//Defining pins used, side note, gotta remember to wire it up exactly like this
#define BMP_SCK (12)
#define BMP_MISO (11)
#define BMP_MOSI (10)

Adafruit_BMP280 bmp; //links the driver for the barometer to that variable
// put function declarations here:


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while ( !Serial ) delay(100);
  Serial.println(F("BMP280 test"));
  unsigned status;
  status = bmp.begin(); //this actually initializes sensor

  }


void loop() {
  // put your main code here, to run repeatedly:
}