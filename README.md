# Medical Signals Box project source (for Educational Purposes)
The Medical Signals Box is an embedded system designed to collect, transmit, and store medical sensors data, with companion software that enables data reception on computers and smart devices.

### Partial Implementation of Firmware (Hardware Testing and Configuration)
- ESP32 Bluetooth data transmission (BLE server).
- TFT ILI9225 display module integrated with ESP32 LOLIN32.
- TTP224 four-channel touch sensor.
- RTC DS3231 for setting and reading real-time clock data.
- Heart rate and SpO₂ acquisition using MAX30102.
- ECG signal plotting from AD8232.
- Display of the Medical Signals Box logo and additional startup visuals.
- MPU-6050 accelerometer and gyroscope integration.
- I²C scanner for detecting module I²C addresses.

### Software: 
* __Partial Building__;
1. __receive the data from the hardware via bluetooth by Nodejs (software/Linux/code.js) in linux (test it in ubuntu 18.04.2)__
2. __receive the data from the hardware via bluetooth by Nodejs (software/Windows/code.js) in Windows (test it in windows 10)__ <br/>
   __Update of 06 may 2019 for the app for Windows:__ there are a problems when I try to program the bluetooth receive in windows, the philosophy of windows with the hardware is not like the linux, in Linux any thing is file for that the play with the hardware is so easy, I will stop develop the app for windows in this time and complete develop the app just in linux, in the future I try to develep it by C#. 
* __Full building__:<br/>
When complete the partial building, I use a methode from prepreprocessor to use the special code for special OS, so when the software run in Linux the software choose the code 1 and when run in windows the software choose the code 2. 


### Disclaimer and Usage Notice
This project is provided solely for educational purposes. The software, code, scripts, and any other files in this source are provided “as is,” and their use is not permitted without explicit authorization. The author disclaims all warranties, including implied warranties of merchantability and fitness for a particular purpose. In no event shall the author be liable for any special, direct, indirect, or consequential damages, or any damages arising from loss of use, data, or profits, whether in contract, negligence, or any other tortious action, arising out of or in connection with the use or performance of these materials.
 
