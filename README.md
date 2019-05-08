# Medical Signals Box
#### Embedded system project to collect,send and save medical data with software for receive the data in computers and smart devices.

### Hardware: 
* Hardware test and config:
1. ESP32 Bluetooth send data or ble_server.
2. TFT ILI9225 with ESP32 LOLIN32.
3. TTP224 Switch Touch Sensor Digital 4.
4. RTC_DS3231: set time and date, read the time and date now.
5. Get the data of Heart Rate and SpO2 from MAX30102.
6. AD8232 ECG

### Software: 
1. __receive the data from the hardware via bluetooth by Nodejs (software/Linux/code.js) in linux (test it in ubuntu 18.04.2)__
2. __receive the data from the hardware via bluetooth by Nodejs (software/Windows/code.js) in Windows (test it in windows 10)__ <br/>
   __Update of 06 may 2019 for the app for Widnows:__ there are a problems when I try to program the bluetooth receive in windows, the philosophy of windows with the hardware is not like the linux, in Linux any thing is file for that the play with the hardware is so easy, I will stop develop the app for windows in this time and complete develop the app just in linux, in the future I try to develep it by C#. 
 
