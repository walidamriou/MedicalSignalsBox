![panal with left menu](https://github.com/walidamriou/MedicalSignalsBox/blob/master/about/github_cover.png)

# Medical Signals Box project source 
#### Medical signals box is an Embedded system project to collect,send and save medical data with software for receive the data in computers and smart devices.

------------------------------------------------------------
* __You can see my graduation thesis to get more about this project, design, ideas, and more (my Master Degree in Electronic of Embedded Systems thesis)__:
* [From university of M'sila website](http://dspace.univ-msila.dz:8080/xmlui/handle/123456789/16122)
* [From google drive](https://drive.google.com/open?id=166BeP_vbR_HBgyp62OKz9IQIrJ2khRgF)

------------------------------------------------------------

### Hardware: 
* __Partial Building of Firmware (Hardware test and config)__:
1. ESP32 Bluetooth send data or ble_server.
2. TFT ILI9225 with ESP32 LOLIN32.
3. TTP224 Switch Touch Sensor Digital 4.
4. RTC_DS3231: set time and date, read the time and date now.
5. Get the data of Heart Rate and SpO2 from MAX30102.
6. plot the signal of ECG from AD8232 
7. Display logo of Medical Signals box and more in the start.
8. make Hardware intarface.
9. Develop an Arduino Library to samplify the main code of the firemware. _We focus to this part in the next prototype v2 to focus in education use of the Medical Signals Box_ 
10. MPU-6050 accelerometer and gyroscope. 
11. I2C scanner for get the I2C address of the module

* __full building of Firemware__: the firemware writing by c++ and arduino lang<br/>
source code of the firemware here (under development): https://github.com/walidamriou/MedicalSignalsBox/tree/master/Prototype_v1/Hardware/Firmware/MedicalSignalsBox_version2

* __Full building of the hardware__:
1. Circuit: Soon
2. PCB: Soon

### Software: 
* __Partial Building__;
1. __receive the data from the hardware via bluetooth by Nodejs (software/Linux/code.js) in linux (test it in ubuntu 18.04.2)__
2. __receive the data from the hardware via bluetooth by Nodejs (software/Windows/code.js) in Windows (test it in windows 10)__ <br/>
   __Update of 06 may 2019 for the app for Windows:__ there are a problems when I try to program the bluetooth receive in windows, the philosophy of windows with the hardware is not like the linux, in Linux any thing is file for that the play with the hardware is so easy, I will stop develop the app for windows in this time and complete develop the app just in linux, in the future I try to develep it by C#. 
* __Full building__:<br/>
When complete the partial building, I use a methode from prepreprocessor to use the special code for special OS, so when the software run in Linux the software choose the code 1 and when run in windows the software choose the code 2. 


### Copyright CC 2020 Walid Amriou

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.

__You are free to:__
  * Share — copy and redistribute the material in any medium or format
  * Adapt — remix, transform, and build upon the material
The licensor cannot revoke these freedoms as long as you follow the license terms.  

__Under the following terms:__
  * Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
  * NonCommercial — You may not use the material for commercial purposes.
  * ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.
  * No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.


the software or Code or Scripts or any files in this source is provided "as is" and the author disclaims all warranties with regard to this files including all implied warranties of merchantability and fitness. in no event shall the author be liable for any special, direct, indirect, or consequential damages or any damages whatsoever resulting from loss of use, data or profits, whether in an action of contract, negligence or other tortious action, arising out of or in connection with the use or performance of this software or code or scripts or any files in this source.
 
