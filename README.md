# Arduino-CO<sub>2</sub> eflux Datalogger
An arduino sketch to log measurements from multiple environmental sensors to an SD card. For use in a soil CO<sub>2</sub> eflux chamber. 

Required Components:
- Arduino UNO
- Adafruit Datalogging Shield 
- Piezo Buzzer
- Adafruit BME680 (Temperature, Humidity, Pressure, VOC)
- DS18B20 waterproof temperature sensor
- T6613 CO<sub>2</sub> analyzer  

## Field Operation
1. Set the chamber down on its side near the preinstalled soil collar you wish to measure from. Turn on the device with the power toggle switch on the battery box.  
2. The device will enter a warmup period for 5 minutes. 
3. At the end of 5 minutes the device will beep for 3 seconds. When this occurs, pick up the device and secure it into the soil collar. 
4. The device will log every 5 seconds for 3 minutes. A red light will blink twice every 5 seconds to indicate logging. 
5. When 3 minutes is complete, the device will beep for 5 seconds. The red light will stop blinking to indicate that logging has ended. 
6. Turn off the device using the power switch on the battery box.  

## Data 
The device logs the following 8 variables to an SD card in .csv format: 
-Site/Location/Station
-Date
-Time
-Atmospheric temperature (in Kelvin)
-Soil temperature (in Kelvin)
-Atmospheric humididy (in Percent)
-Atmospheric pressure (in kPa)
-Atmospheric CO<sub>2,</sub> concentration

Station | Date | Time | Air Temp (K) | Soil temp (K) | Humidity (%) | Air press (kPa) | CO2 (ppm) |
---|---|---|---|---|---|---|---|
Site 1 | 08/05/2020 | 8:51:07 | 298.54 | 298.15 | 67.81 | 100.3 | 380
Site 1 | 08/05/2020	| 8:51:12 |	298.55 | 297.96 | 67.69 | 100.3 | 380
Site 1 | 08/05/2020	| 8:51:17 |	298.56 | 297.9 | 67.51 | 100.3 | 381
Site 1 | 08/05/2020	| 8:51:22 |	298.58 | 297.9 | 67.38 | 100.3 | 381
Site 1 | 08/05/2020	| 8:51:27 |	298.6  | 297.9 | 67.28 | 100.3 | 380




 