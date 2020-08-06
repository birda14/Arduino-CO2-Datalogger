# Arduino-CO<sub>2</sub> efflux Datalogger
An arduino sketch to log measurements from multiple environmental sensors to an SD card. For use in a soil CO<sub>2</sub> efflux chamber. 

## Construction 
Required Components:
Component | Quantity | Store Link
---|---|---
 Arduino UNO | 1 | https://amzn.to/2EKhSgj
 Adafruit Datalogging Shield | 1 | https://bit.ly/3kf1W69
 CR1220 Coin Cell Battery | 1 | https://bit.ly/2DmNJ6x
 SD Card | 1 | https://amzn.to/3ibLDoG
 Headers | 1 | https://amzn.to/3gwQX5M
 Perma-proto Half Sized Breadboard | 1 | https://bit.ly/3kfBTf6
 Adafruit BME680 (Temperature, Humidity, Pressure, VOC) | 1 | https://bit.ly/39WR7AS
 DS18B20 Waterproof Temperature Sensor | 1 | https://amzn.to/3keA4Po
 T6613 CO<sub>2</sub> Analyzer | 1 | https://bit.ly/2DdPLpG
 Piezo Buzzer | 1 | https://amzn.to/3gAVuEg
 4.7K Resistor | 1 | https://amzn.to/39Ylmau
 Cable gland | 2 | https://bit.ly/31ouS2S
 Case | 1 | https://amzn.to/39YkZwC
 50cm of 3' PVC pipe | 1 | Local Retail
 3' PVC cap | 1 | Local Retail
 Velcro Tape | 1 | https://amzn.to/2EKnJ5h
 18 AWG Wire | 1 | https://amzn.to/3ki2Q1w
 22 AWG Wire | 1 | https://amzn.to/2XtdvN6
 Battery Box | 1 | https://bit.ly/3fvNumH
 Power Connector | 1 | https://amzn.to/3gCqHHm
 AA Batteries 8 pack | 1 | https://amzn.to/2PoqyLD
 
 ### Assemble Arduino

 1. Solder header pins onto the datalogger shield.
 2. Connect the datalogger shield to the Arduino Uno. 
 3. Install the real time clock CR1220 coin cell battery into the datalogger shield.
 ![Shield and Uno](https://raw.githubusercontent.com/birda14/Arduino-CO2-Datalogger/master/Images/Logger%20and%20Shield%20.png) 

 ### Assemble Sensor Board
 
 1. Solder header pins to all connections on the BME680
 2. Solder individual header pins to only pins 1, 3, 10, and 11 of the T6613 CO<sub>2</sub> sensor (see pinout below).
 ![T6113 pinout](https://github.com/birda14/Arduino-CO2-Datalogger/blob/master/Images/T6613%20pinout.png)
 3. Connect all componets to the board as per the diagram and tabel below. 

 ![Sensor board](https://github.com/birda14/Arduino-CO2-Datalogger/blob/master/Images/breadboard.png) 
 

 Component | Pin | Board Position
 ---|---|---
 BME680 | VIN | E1
 BME680 | 3Vo | E2
 BME680 | GND | E3
 BME680 | SCK | E4
 BME680 | SDO | E5
 BME680 | SDI | E6
 BME680 | CS | E7
 Buzzer | - | I9
 Buzzer | + | I12
 T6613 | 1 | D25
 T6613 | 3 | D26
 T6613 | 10 | E29
 T6613 | 11|  D30

 
 Component | Board Position 1 | Board Position 2
 ---|---|---
 Black Wire 1 | Ground 3 | B3 
 Black Wire 2 | Ground 9 | C9
 Black Wire 3 | E9 | F9
 Black Wire 4 | Ground 26 | B26
 Red Wire 1 | Positive 1 | A1
 Red Wire 2 | Positive 10 | A10
 Red Wire 3 | Positive 25 | A25
 4.7K Resistor | C10 | C13

 ### Assemble Chamber

 ### Wiring 
 ![Connected](https://github.com/birda14/Arduino-CO2-Datalogger/blob/master/Images/connected.png)
## Programming The Arduino 

### Required Libraries  

### Preparing the Real-Time-Clock (RTC)

### Preparing the SD Card 

### Customizing and Uploading the Program



## Field Operation
1. Set the chamber down on its side near the preinstalled soil collar you wish to measure from. Turn on the device with the power toggle switch on the battery box.  
2. The device will enter a warmup period for 5 minutes.
3. While you wait, unclip the soil moisture sensor and insert it into the soil beside the collar. 
4. At the end of 5 minutes the device will beep for 3 seconds. When this occurs, pick up the device and secure it into the soil collar. 
5. The device will log every 5 seconds for 3 minutes. A red light will blink twice every 5 seconds to indicate logging. 
6. When 3 minutes has elapsed, the device will beep for 5 seconds. The red light will stop blinking to indicate that logging has ended. 
7. Turn off the device using the power switch on the battery box.  

## Data 
The device logs the following 8 variables to an SD card in .csv format: 
- Site/Location/Station
- Date
- Time
- Atmospheric temperature (in Kelvin)
- Soil temperature (in Kelvin)
- Atmospheric humididy (in Percent)
- Atmospheric pressure (in kPa)
- Atmospheric CO<sub>2,</sub> concentration

Station | Date | Time | Air Temp (K) | Soil temp (K) | Humidity (%) | Air press (kPa) | CO2 (ppm) |
---|---|---|---|---|---|---|---|
Site 1 | 08/05/2020 | 8:51:07 | 298.54 | 298.15 | 67.81 | 100.3 | 380
Site 1 | 08/05/2020	| 8:51:12 |	298.55 | 297.96 | 67.69 | 100.3 | 380
Site 1 | 08/05/2020	| 8:51:17 |	298.56 | 297.9 | 67.51 | 100.3 | 381
Site 1 | 08/05/2020	| 8:51:22 |	298.58 | 297.9 | 67.38 | 100.3 | 381
Site 1 | 08/05/2020	| 8:51:27 |	298.6  | 297.9 | 67.28 | 100.3 | 380




 