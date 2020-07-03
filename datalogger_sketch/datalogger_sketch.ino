//Include required libraries
#include <SD.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "SoftwareSerial.h"
#include "RTClib.h"
#include <OneWire.h>
#include <DallasTemperature.h>
//----------------------------------------------------------------------

//Set up UART connection for CO2 sensor
SoftwareSerial T66_Serial(6,7); //Sets up a virtual serial port
 //Using pin 12 for Rx and pin 13 for Tx
byte readCO2[] = {0xFF, 0XFE,2,2,3}; //T66 read CO2 command: 5 bytes

byte response[] = {0,0,0,0,0}; //create an array to store the response
//---------------------------------------------------------------------
//
//Set up BME 680 sensor
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define ONE_WIRE_BUS 8
#define SEALEVELPRESSURE_HPA (1013.25)


Adafruit_BME680 bme; // I2C
//----------------------------------------------------------------------
//Setup real time clock
RTC_PCF8523 rtc; // define the Real Time Clock object
//---------------------------------------------------------------------
// for the data logging shield, we use digital pin 10 for the SD cs line

const int pinCS = 10;
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

 float Celcius=0;

// the logging file


//-----------------------------------------------------------------------


//----------------------------------------------------------------------
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  SD.begin(pinCS);
  bme.begin();
  rtc.begin();
 

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
  sensors.begin();
  sensors.setWaitForConversion(false);

  T66_Serial.begin(19200); //Opens the virtual serial port with a baud of 19200

  Serial.println(" Datalogger Start");
  Serial.print("\n");

  
delay(1000); //wait 10 monutes for sensors to warm up before entering the loop
}

void loop() {
  

  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  File dataFile = SD.open("log.txt", FILE_WRITE); //opens or creates file

  sensors.requestTemperatures(); 
  

  //Print Values to Serial Monitor
  Serial.println(bme.temperature);
  Celcius=sensors.getTempCByIndex(0);
  Serial.println(Celcius);
  Serial.println(bme.humidity);
  Serial.println(bme.pressure / 100.0);
  

  sendRequest(readCO2);   //Locate the problem of program reset whduring this function call
  unsigned long valCO2 = getValue(response);// Request from sensor 5 bytes of data
  Serial.println(valCO2);
  Serial.println();
  
  DateTime now = rtc.now();

if (dataFile)
  {
    dataFile.print(now.year(), DEC);
    dataFile.print("/");
    dataFile.print(now.month(), DEC);
    dataFile.print("/");
    dataFile.print(now.day(), DEC);
    dataFile.print(",");
    dataFile.print(now.hour(), DEC);
    dataFile.print(":");
    dataFile.print(now.minute(), DEC);
    dataFile.print(":");
    dataFile.print(now.second(), DEC);
    dataFile.print(",");
    dataFile.print(bme.temperature);
    dataFile.print(",");
    dataFile.print(Celcius);
    dataFile.print(",");
    dataFile.print(bme.humidity);
    dataFile.print(",");
    dataFile.print(bme.pressure / 100.0);
    dataFile.print(",");
    dataFile.print(valCO2);
    dataFile.println();
    dataFile.close();

    delay(1000); //T6613 spec indicates signal update every 4 seconds
  }
  else
  {
    Serial.print(dataFile);
  }
}

void sendRequest(byte packet[])
{
 while(!T66_Serial.available()) //keep sending request until we start to get a response
 {
 T66_Serial.write(readCO2,5);// Write to sensor 5 byte command
 delay(50);
 delay(1000);
 }
 int timeout=0; //set a timeoute counter
 while(T66_Serial.available() < 5 ) //Wait to get a 7 byte response
 {
 timeout++;
 if(timeout > 10) //if it takes to long there was probably an error
 Serial.print("Timeout");
 {
 while(T66_Serial.available()) //flush whatever we have
 T66_Serial.read();

 break; //exit and try again
 }
 delay(50);
 }
  for (int i=0; i < 5; i++) response[i] = T66_Serial.read();
}

unsigned long getValue(byte packet[])
{
 int high = packet[3]; //high byte for value is 4th byte in packet in the packet
 int low = packet[4]; //low byte for value is 5th byte in the packet
 unsigned long val = high*256 + low; //Combine high byte and low byte with this formula to get value
 return val;
 
}
