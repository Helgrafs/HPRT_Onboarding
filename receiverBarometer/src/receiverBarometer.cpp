// code for the receiver
#include <Wire.h>
#include <Arduino.h>
#include <SPI.h>
//for bmp280
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_I2CDevice.h>
//for LoRa
#include <LoRa.h>
// LoRa pin defintions
#define SS 18
#define RST 14
#define DI0 26
#define SCK 5
#define MISO 19
#define MOSI 27

//for LittleFS
#include <LITTLEFS.h>
#define FORMAT_LITTLEFS_IF_FAILED true
//function prototypes
// variables for lora
int syncWord = 0xF7;
byte _localAddress = 0xFF;
byte _destination = 0xBB;
boolean _canPrintHeaderMessage = false;
// function to use when receiving packet
void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }
    unsigned writer = file.println(message);
        Serial.println("- file written");
     if(!writer) {
        Serial.println("- write failed");
        return;
    }
    file.close();
}
void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("- failed to open file for appending");
        return;
    }
    if(file.println(message)){
        Serial.println("- message appended");
    } else {
        Serial.println("- append failed");
    }
    file.close();
}
void Receiver(int packetSize)
{
  String Received = "";
  if (packetSize == 0)
    return;
  int recipient = LoRa.read();
  byte sender = LoRa.read();
  byte MessageID = LoRa.read();
  byte receivedLength = LoRa.read();
  
  while (LoRa.available())
  {
    Received += (char)LoRa.read();
  }
  if (receivedLength != Received.length())
  {
    Serial.println("length mismatch");
    return;
  }
  if (recipient != _localAddress && recipient != 0xFF)
  {
    Serial.println("wrong address");
  }
  Serial.println("Transmission: " + Received);
  Serial.println();  
  const char * flashReceived = Received.c_str();
  appendFile(LITTLEFS, "/data/receivedData.txt", flashReceived);
}
//function for reading files
void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path); //indicates which file is being read + the path

    File file = fs.open(path); //opens file
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }

    Serial.println("- read from file:");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}


//function to create new directories
void createDir(fs::FS &fs, const char * path){
    Serial.printf("Creating Dir: %s\n", path);
    if(fs.mkdir(path)){ //this actually makes the directory
        Serial.println("Dir created");
    } else {
        Serial.println("mkdir failed");
    }
}


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("LoRa Receiver");
  // initialises LoRa
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(433E6)) // checks if LoRa initialised
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  else
  {
    Serial.println("LoRa initialisation successful");
  }
    if(!LITTLEFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
    Serial.println("LittleFS failed to mount");
    } else{
      Serial.println("LittleFS mounted successfully");
    }
  // LoRa parameters
  LoRa.setTxPower(20);
  LoRa.setSpreadingFactor(7);
  LoRa.setCodingRate4(8);
  LoRa.setSignalBandwidth(25E4);
  //createDir(LITTLEFS, "/data");
  readFile(LITTLEFS, "/data/receivedData.txt");
  //next line is for resetting data, uncomment and run once to get a clean file to fill up with numbers
  //writeFile(LITTLEFS, "/data/receivedData.txt", "reset");
}

void loop()
{
  Receiver(LoRa.parsePacket());
}

