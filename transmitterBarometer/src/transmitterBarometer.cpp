//Code for the transmitter and BMP280 sensor
//Library definitons
#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_BMP280.h>
// LoRa definitions, shamelessly stolen from VIP code, after cross referencing to datasheet, I get it now.
#define SS 18
#define RST 14
#define DI0 26
#define SCK 5
#define MISO 19
#define MOSI 27
Adafruit_BMP280 bmp;
//variables for header
String outgoing = "string";
int syncWord = 0xF7;
byte _localAddress = 0xFF;
byte _destination = 0xFF;
boolean _canPrintHeaderMessage = false;
void setup()
{
  // VERY IMPORTANT!!!! WHEN CONNECTING BMP280, SCL goes to pin 11 And SDA goes to pin 12!!!!!!!!!!!
  Serial.begin(115200);
  while (!Serial);
  unsigned status;
  status = bmp.begin(); //initialises bmp280
  SPI.begin(SCK, MISO, MOSI, SS); //starting LoRa
  LoRa.setPins(SS, RST, DI0);
  if (!status) //checks if the barometer actually started
  {
    Serial.println(F("BMP Initialisation failed"));
    while (1)
      delay(10);
  }
  else
  {
    Serial.println("BMP initialisation successful");
  }
  Serial.println("LoRa Transmitter");
  if (!LoRa.begin(433E6)) //checks if lora started
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  else
  {
    Serial.println("LoRa initialisation successful");
  }
  LoRa.setSyncWord(0xF7); //lora parameters
  LoRa.setTxPower(20);
  LoRa.setSpreadingFactor(7);
  LoRa.setCodingRate4(8);
  LoRa.setSignalBandwidth(25E4);
}
void transmitter(String outgoing, int messageId) //function to use when sending info
{
  LoRa.beginPacket();
  LoRa.write(_destination);
  LoRa.write(_localAddress);
  LoRa.write(messageId);
  LoRa.write(outgoing.length());
  LoRa.print(outgoing);
  LoRa.endPacket();
  Serial.println("Package sent");
}
void loop()
{
  Serial.println("Sending barometer data");
  //read sensor data
  float Temperature = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude(1017);
  //create message to transmit
  String Message = "Temperature: " + String(Temperature) + "*C; Pressure: " + String(pressure) + "Pa; Altitude: " + String(altitude);
  //transmit message
  transmitter(Message, 0);
  delay(3000);
}