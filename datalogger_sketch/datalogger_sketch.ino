//Include required libraries
#include <SD.h> //Library for SD card Logger
#include <Wire.h> //Library for I2C Interface
#include <SPI.h> //Library for SPI interface
#include <Adafruit_Sensor.h> //Common Library for Adafruit Sensors 
#include "Adafruit_BME680.h" // Library for Combined Environmental Sensor BME680
#include "SoftwareSerial.h" //Library for Configuring Serial Interface for T66 CO2 Sensor
#include "RTClib.h" //Library for Real Time Clock RTC_PCF8523
#include <OneWire.h> //Interface for DS18B20 Temperature Sensor
#include <DallasTemperature.h> //Library for DS18B20 Temperature Sensor
//----------------------------------------------------------------------

//Set up UART connection for CO2 sensor
SoftwareSerial T66_Serial(6,7); //Sets up a virtual serial port on pin 6 for Rx and pin 7 for Tx
byte readCO2[] = {0xFF, 0XFE,2,2,3}; //T66 read CO2 command: 5 bytes
byte response[] = {0,0,0,0,0}; //create an array to store the response
//---------------------------------------------------------------------

//Set up BME 680 sensor
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define ONE_WIRE_BUS 8
#define SEALEVELPRESSURE_HPA (1013.25)
//---------------------------------------------------------------------

// Misc Configuration for Buzzer, BME680, RTC, Dattalogger, DS18B20
const int buzzer = 9; //Set up buzzer on arduino pin 9
Adafruit_BME680 bme; //Set up BME680 I2C
RTC_PCF8523 rtc; //Setup real time clock
const int pinCS = 10; // Set up logging sheild 10 for the SD cs line
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float Celcius=0;
DateTime sampleinit;
//----------------------------------------------------------------------

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600); //Start serial console for debugging
  SD.begin(pinCS); //Start SD card
  bme.begin(); //Start bme sensor
  rtc.begin(); //Start real time clock
 
  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
  sensors.begin();
  sensors.setWaitForConversion(false);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output

  T66_Serial.begin(19200); //Opens the virtual serial port with a baud of 19200

  Serial.println(" Datalogger Start");
  Serial.print("\n");

  delay(300000); //wait 5 minutes for CO2 sensor to warm up before entering the loop
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(3000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec  
  sampleinit = rtc.now(); //Store sampling initiated time
}

void loop() {
  if(rtc.now() == (sampleinit+TimeSpan(0,0,3,0))) //Edit to change total sampling duration (day, hour, minute, second)
    { 
      tone(buzzer, 5000); // Send 2KHz sound signal...
      delay(5000);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      while(1) { }        //Endless loop, program ends. 
      }
  DateTime now = rtc.now(); // Check time at begining of loop

  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  
  File dataFile = SD.open("log.csv", FILE_WRITE); //opens or creates file

  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  sendRequest(readCO2);   //Sends request to CO2 meter
  unsigned long valCO2 = getValue(response);// Request from sensor 5 bytes of data

if (dataFile)
  {
    dataFile.print("Site 1"); //Edit to change site information 
    dataFile.print(",");
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
    dataFile.print(bme.temperature + 273.15);     //Temperature in Kelvin
    dataFile.print(",");
    dataFile.print(Celcius + 273.15);       //Temperature in Kelvin
    dataFile.print(",");
    dataFile.print(bme.humidity);           //Humidity in %
    dataFile.print(",");
    dataFile.print(bme.pressure / 1000);    //Pressure in kPa
    dataFile.print(",");
    dataFile.print(valCO2);                 //Concentration in ppm
    dataFile.println();
    dataFile.close();

    while(rtc.now() != (now+TimeSpan(0,0,0,5))); //Edit to change total sampling interval (day, hour, minute, second)
    
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
