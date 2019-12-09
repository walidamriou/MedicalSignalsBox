/*
Medical Signals Box project
Developed by Walid Amriou
2019 
*/

// Modules library
#include "SPI.h"
#include "TFT_22_ILI9225.h"
#include <sstream>
#include <string>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include "DS3231.h"
#include "Images_of_Interfaces.h"

void page_id(int id_number);
///////////////////////////////////////////////////////////
// RTC and Time of record         //////////////////////////
///////////////////////////////////////////////////////////

int ECG_Time,SPO2_Time,HR_Time;
RTClib RTC;
const int DS3231_address=0x68; 
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// MAX30105 or MAX30102         //////////////////////////
///////////////////////////////////////////////////////////

MAX30105 particleSensor;
#define MAX_BRIGHTNESS 255
uint32_t irBuffer[100]; //infrared LED sensor data
uint32_t redBuffer[100];  //red LED sensor data
int32_t bufferLength; //data length
int32_t spo2; //SPO2 value
int8_t validSPO2; //indicator to show if the SPO2 calculation is valid
int32_t heartRate; //heart rate value
int8_t validHeartRate; //indicator to show if the heart rate calculation is valid

int SPO2_data[20];
int HR_data[20];

int SPO2_valure = 95;
int HR_valure = 120;

///////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////
// BLE bluetooth valures         //////////////////////////
///////////////////////////////////////////////////////////
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
//Just valures for operation of send ..
std::stringstream data_send;
std::string datasend;

///////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////
// Buttons                           //////////////////////
///////////////////////////////////////////////////////////
const int touch_1_down  =  13;     
const int touch_2_up    =  12;      
const int touch_3_ok    =  14;     
const int touch_4_exit  =  27;     

///////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////
// ECG                               //////////////////////
///////////////////////////////////////////////////////////
int ECG_data[1000];
int ECG_data_temp1[1000];
int ECG_data_temp2[1000];
int F=1;
String ECG_data_to_screen;

///////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////
// valures of the TFT screen         //////////////////////
///////////////////////////////////////////////////////////
// valure for know where the Interface
int Page = 1;

//TFT
#define TFT_CLK 18  // SCK
#define TFT_SDI 23  // SDA
#define TFT_RS  2   // RS
#define TFT_RST 15   // RST
#define TFT_CS  5  // CS
#define TFT_LED 0   // Già collegato a +5V/+3.3V

// Use hardware SPI (faster)
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);


// Setup
void setup() {
  Serial.begin(9600);
  
  //Touch
  pinMode(touch_1_down, INPUT);
  pinMode(touch_2_up,INPUT);
  pinMode(touch_3_ok, INPUT);
  pinMode(touch_4_exit,INPUT);
  pinMode(5,OUTPUT);

  digitalWrite(5,HIGH);
  //ECG
  pinMode(32, INPUT); // Setup for leads off detection LO +
  pinMode(33, INPUT); // Setup for leads off detection LO -
  
  delay(1000);
  
  // Login info & logo's
  tft.begin();
  tft.clear();
  tft.drawBitmap(0, 0, Medical_signals_box_logo, 176, 176,COLOR_WHITE);
  delay(1000);
  tft.clear();
  tft.drawBitmap(0, 0, Medical_signals_box_name, 176, 176,COLOR_WHITE);
  delay(1000);
  tft.clear();
  tft.drawBitmap(0, 0, developed_by, 176, 176,COLOR_WHITE);
  delay(1000);
  tft.clear();
  tft.drawBitmap(0, 0, walidamriou_logo, 176, 176,COLOR_WHITE);
  delay(1000);
  tft.clear();
  tft.drawBitmap(0, 0, Home_page_1, 176, 176,COLOR_WHITE);
}

void loop() {

/////////////////////////////////////////////////////////
// Home pages
/////////////////////////////////////////////////////////

  if((digitalRead(touch_1_down) == HIGH) && Page == 1 ){
    page_id(2);
  }
 
  if((digitalRead(touch_1_down) == HIGH) && Page == 2 ){
    page_id(3);
  }

  if((digitalRead(touch_1_down) == HIGH) && Page == 3 ){
    page_id(1);
  }

  if((digitalRead(touch_2_up) == HIGH) && Page == 1 ){
    page_id(3);
  }
 
  if((digitalRead(touch_2_up) == HIGH) && Page == 2 ){
    page_id(1);
  }

  if((digitalRead(touch_2_up) == HIGH) && Page == 3 ){
    page_id(2);
  }

/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// Sensors pages
/////////////////////////////////////////////////////////

  //From home 1 to sensors page home 1
  if((digitalRead(touch_3_ok) == HIGH) && Page == 1 ){
    page_id(4);
  }

  // Sensors pages down

  //From page sensors 1 to 2
  if((digitalRead(touch_1_down) == HIGH) && Page == 4 ){
    page_id(5);
  }

  //From page sensors 2 to 3
  if((digitalRead(touch_1_down) == HIGH) && Page == 5 ){
    page_id(6);
  }

  //From page sensors 3 to 1
  if((digitalRead(touch_1_down) == HIGH) && Page == 6 ){
    page_id(4);
  }  

  // Sensors pages up 

  //From page sensors 1 to 3
  if((digitalRead(touch_2_up) == HIGH) && Page == 4 ){
    page_id(6);
  }

  //From page sensors 3 to 2
  if((digitalRead(touch_2_up) == HIGH) && Page == 6 ){
    page_id(5);
  }

  //From page sensors 2 to 1
  if((digitalRead(touch_2_up) == HIGH) && Page == 5 ){
    page_id(4);
  }  

  // Sensors pages exit to home 

  //From page sensors 1 to home 1
  if((digitalRead(touch_4_exit) == HIGH) && Page == 4 ){
    page_id(1);
  }

  //From page sensors 2 to home 1
  if((digitalRead(touch_4_exit) == HIGH) && Page == 5 ){
    page_id(1);
  }

  //From page sensors 2 to home 3
  if((digitalRead(touch_4_exit) == HIGH) && Page == 6 ){
    page_id(1);
  }  

/////////////////////////////////////////////////////////
//ECG
/////////////////////////////////////////////////////////
  //From Sensors_page1 to ECG_page_home
  if((digitalRead(touch_3_ok) == HIGH) && Page == 4 ){
    page_id(7);
  }  

  //From ECG_page_home to ECG_on_record 
  if((digitalRead(touch_3_ok) == HIGH) && Page == 7 ){
    page_id(8);
    // code1 Code of ECG here 
    while (digitalRead(touch_4_exit)==LOW)
    {
      if((digitalRead(32) == 1)||(digitalRead(33) == 1)){
      Serial.println('!');
      }
      else if( F == 1){
        // send the value of analog input 0:
        int y,x=10;
        tft.clear();
        for (int i = 0; i < 100; i++)
        {
           ECG_data_temp1[i] = analogRead(25);
           Serial.println(ECG_data_temp1[i]);
           ECG_data_to_screen = String(i)+" - "+String(ECG_data_temp1[i]);
           //Wait for a bit to keep serial data from saturating
           tft.clear();
           tft.setFont(Terminal6x8);
           tft.drawText(x, y, ECG_data_to_screen);
           y=y+10;
           if(y==50){y=10;tft.clear();}
           //tft.drawText(10, 10, "the data record now");
           delayMicroseconds(10);
        }
        
        F=0; 

        Wire.begin();
        Wire.beginTransmission(DS3231_address);
        DateTime now = RTC.now();
        Serial.print(now.year(), DEC);
        Serial.print('/');
        Serial.print(now.month(), DEC);
        Serial.print('/');
        Serial.print(now.day(), DEC);
        Serial.print(' ');
        Serial.print(now.hour(), DEC);
        Serial.print(':');
        Serial.print(now.minute(), DEC);
        Serial.print(':');
        Serial.print(now.second(), DEC);
        Serial.println();  
        page_id(9);   
      }
      
    }
    F=1;

  }  
  
  //From ECG_on_record to ECG_save_data
  if((digitalRead(touch_3_ok) == HIGH) && Page == 8 ){
    page_id(9);
    // code2 Code of ECG save data to valures 
  }  

  //From ECG_save_data to ECG_page_home
  if((digitalRead(touch_3_ok) == HIGH) && Page == 9 ){
    page_id(7); 
  }  
  
  //from ECG_on_record to ECG_page_home
  if((digitalRead(touch_4_exit) == HIGH) && Page == 8 ){
    page_id(7); 
  }  

  //from ECG_save_data to ECG_page_home
  if((digitalRead(touch_4_exit) == HIGH) && Page == 9 ){
    page_id(7); 
  } 

  //from ECG_page_home to Sensors_page1
  if((digitalRead(touch_4_exit) == HIGH) && Page == 7 ){
    page_id(4); 
  } 
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//SPO2
/////////////////////////////////////////////////////////
  //From Sensors_page2 to SPO2_page_home
  if((digitalRead(touch_3_ok) == HIGH) && Page == 5 ){
    page_id(10);
  }  

  //From SPO2_page_home to SPO2_on_record 
  if((digitalRead(touch_3_ok) == HIGH) && Page == 10 ){
    page_id(11);
    // code1 Code of SPO2 here 
    Serial.println("Start SPO2");
    if (!particleSensor.begin(Wire, I2C_SPEED_FAST,0x57)) //Use default I2C port, 400kHz speed
    {
      Serial.println(F("MAX30105 was not found. Please check wiring/power."));
      //while (1);

    Wire.begin();
    Wire.beginTransmission(DS3231_address);
    DateTime now = RTC.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

      page_id(10); 
    }
    else
    {
    
    
    byte ledBrightness = 60; //Options: 0=Off to 255=50mA
    byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
    byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
    byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    int pulseWidth = 411; //Options: 69, 118, 215, 411
    int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

   particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
   
    bufferLength = 100; //buffer length of 100 stores 4 seconds of samples running at 25sps

    //read the first 100 samples, and determine the signal range
    for (byte i = 0 ; i < bufferLength ; i++)
    {
      while (particleSensor.available() == false) //do we have new data?
      particleSensor.check(); //Check the sensor for new data

      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample(); //We're finished with this sample so move to next sample

      Serial.print(F("red="));
      Serial.print(redBuffer[i], DEC);
      Serial.print(F(", ir="));
      Serial.println(irBuffer[i], DEC);
    }
    delay(1);
    //calculate heart rate and SpO2 after first 100 samples (first 4 seconds of samples)
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
    delay(1);
    //Continuously taking samples from MAX30102.  Heart rate and SpO2 are calculated every 1 second
    for(int i2;i2<10;i2++)
    {
      //dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
      for (byte i = 25; i < 100; i++)
      {
        redBuffer[i - 25] = redBuffer[i];
        irBuffer[i - 25] = irBuffer[i];
      }

      //take 25 sets of samples before calculating the heart rate.
      for (byte i = 75; i < 100; i++)
      {
        while (particleSensor.available() == false) //do we have new data?
        particleSensor.check(); //Check the sensor for new data

        redBuffer[i] = particleSensor.getRed();
        irBuffer[i] = particleSensor.getIR();
        particleSensor.nextSample(); //We're finished with this sample so move to next sample

        //send samples and calculation result to terminal program through UART
        //Serial.print(F("red="));
        //Serial.print(redBuffer[i], DEC);
        //Serial.print(F(", ir="));
        //Serial.print(irBuffer[i], DEC);

        //Serial.print(F(", HR="));
        //Serial.print(heartRate, DEC);

        //Serial.print(F(", HRvalid="));
        //Serial.print(validHeartRate, DEC);

        Serial.print(F(", SPO2="));
        Serial.print(spo2, DEC);

        Serial.print(F(", SPO2Valid="));
        Serial.println(validSPO2, DEC);
        if(validSPO2 == 1){
          SPO2_data[i]=spo2;
        }
      }

      //After gathering 25 new samples recalculate HR and SP02
      maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
  }
  for(int i=0;i<20;i++){
    Serial.print(SPO2_data[i]);
  }

  Wire.begin();
    Wire.beginTransmission(DS3231_address);
    DateTime now = RTC.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
page_id(12);
  }   



  }  
  ////////// end read SPIO2 page

  //From SPO2_on_record to SPO2_save_data
  if((digitalRead(touch_3_ok) == HIGH) && Page == 11 ){
    page_id(12);
    // code2 Code of SPO2 save data to valures 
  }  

  //From SPO2_save_data to SPO2_page_home
  if((digitalRead(touch_3_ok) == HIGH) && Page == 12 ){
    page_id(10); 
  }  
  
  //from SPO2_on_record to SPO2_page_home
  if((digitalRead(touch_4_exit) == HIGH) && Page == 11 ){
    page_id(10); 
  }  

  //from SPO2_save_data to SPO2_page_home
  if((digitalRead(touch_4_exit) == HIGH) && Page == 12 ){
    page_id(10); 
  } 

  //from SPO2_page_home to Sensors_page2
  if((digitalRead(touch_4_exit) == HIGH) && Page == 10 ){
    page_id(5); 
  } 
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//HR
/////////////////////////////////////////////////////////
  //From Sensors_page3 to HR_page_home
  if((digitalRead(touch_3_ok) == HIGH) && Page == 6 ){
    page_id(13);
  }  

  //From HR_page_home to HR_on_record 
  if((digitalRead(touch_3_ok) == HIGH) && Page == 13 ){
    page_id(14);
    // code1 Code of HR here
       Serial.println("Start HR");
    if (!particleSensor.begin(Wire, I2C_SPEED_FAST,0x57)) //Use default I2C port, 400kHz speed
    {
      Serial.println(F("MAX30105 was not found. Please check wiring/power."));
      //while (1);
      page_id(13); 
    }
    else
    {
    
    
    byte ledBrightness = 60; //Options: 0=Off to 255=50mA
    byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
    byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
    byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    int pulseWidth = 411; //Options: 69, 118, 215, 411
    int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

   particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
   
    bufferLength = 100; //buffer length of 100 stores 4 seconds of samples running at 25sps

    //read the first 100 samples, and determine the signal range
    for (byte i = 0 ; i < bufferLength ; i++)
    {
      while (particleSensor.available() == false) //do we have new data?
      particleSensor.check(); //Check the sensor for new data

      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample(); //We're finished with this sample so move to next sample

      Serial.print(F("red="));
      Serial.print(redBuffer[i], DEC);
      Serial.print(F(", ir="));
      Serial.println(irBuffer[i], DEC);
    }
    delay(1);
    //calculate heart rate and SpO2 after first 100 samples (first 4 seconds of samples)
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
    delay(1);
    //Continuously taking samples from MAX30102.  Heart rate and SpO2 are calculated every 1 second
    for(int i2;i2<10;i2++)
    {
      //dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
      for (byte i = 25; i < 100; i++)
      {
        redBuffer[i - 25] = redBuffer[i];
        irBuffer[i - 25] = irBuffer[i];
      }

      //take 25 sets of samples before calculating the heart rate.
      for (byte i = 75; i < 100; i++)
      {
        while (particleSensor.available() == false) //do we have new data?
        particleSensor.check(); //Check the sensor for new data

        redBuffer[i] = particleSensor.getRed();
        irBuffer[i] = particleSensor.getIR();
        particleSensor.nextSample(); //We're finished with this sample so move to next sample

        //send samples and calculation result to terminal program through UART
        //Serial.print(F("red="));
        //Serial.print(redBuffer[i], DEC);
        //Serial.print(F(", ir="));
        //Serial.print(irBuffer[i], DEC);

        Serial.print(F(", HR="));
        Serial.print(heartRate, DEC);

        Serial.print(F(", HRvalid="));
        Serial.print(validHeartRate, DEC);

        //Serial.print(F(", SPO2="));
        //Serial.print(spo2, DEC);

        //Serial.print(F(", SPO2Valid="));
        //Serial.println(validSPO2, DEC);
        if(validSPO2 == 1){
          HR_data[i]=spo2;
        }
      }

      //After gathering 25 new samples recalculate HR and SP02
      maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
  }
  for(int i=0;i<20;i++){
    Serial.print(HR_data[i]);
  }
  }  
    
  }  
  
  //From HR_on_record to HR_save_data
  if((digitalRead(touch_3_ok) == HIGH) && Page == 14 ){
    page_id(15);
    // code2 Code of SPO2 save data to valures 
  }  

  //From HR_save_data to HR_page_home
  if((digitalRead(touch_3_ok) == HIGH) && Page == 15 ){
    page_id(13); 
  }  
  
  //from HR_on_record to HR_page_home
  if((digitalRead(touch_4_exit) == HIGH) && Page == 14 ){
    page_id(13); 
  }  

  //from HR_save_data to HR_page_home
  if((digitalRead(touch_4_exit) == HIGH) && Page == 15 ){
    page_id(13); 
  } 

  //from HR_page_home to Sensors_page3
  if((digitalRead(touch_4_exit) == HIGH) && Page == 13 ){
    page_id(6); 
  } 
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//Info
/////////////////////////////////////////////////////////
  //From Home_page_3 to info_page
  if((digitalRead(touch_3_ok) == HIGH) && Page == 3 ){
    page_id(16);
  }  

  //From info_page to Home_page_3 
  if((digitalRead(touch_4_exit) == HIGH) && Page == 16 ){
    page_id(3);    
  }  
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//Data pages
/////////////////////////////////////////////////////////
  //From Home_page_2 to data_page1
  if((digitalRead(touch_3_ok) == HIGH) && Page == 2 ){
    page_id(17);
  }  

  //From data_page1 to data_page2 
  if((digitalRead(touch_1_down) == HIGH) && Page == 17 ){
    page_id(18);    
  }  
  //From data_page2 to data_page1 
  if((digitalRead(touch_1_down) == HIGH) && Page == 18 ){
    page_id(17);    
  }  
  //From data_page1 to data_page2 
  if((digitalRead(touch_2_up) == HIGH) && Page == 18 ){
    page_id(17);    
  }  
   //From data_page2 to data_page1
  if((digitalRead(touch_2_up) == HIGH) && Page == 17 ){
    page_id(18);    
  }  
  //From data_page1 to Home_page_2 
  if((digitalRead(touch_4_exit) == HIGH) && Page == 17 ){
    page_id(2);    
  } 
  //From data_page2 to Home_page_2 
  if((digitalRead(touch_4_exit) == HIGH) && Page == 18 ){
    page_id(2);    
  } 
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//SD card
/////////////////////////////////////////////////////////
  //From data_page1 to data_sd_card_1
  if((digitalRead(touch_3_ok) == HIGH) && Page == 17 ){
    page_id(19);
  }  

  //From data_sd_card_1 to data_sd_card_2 or Sensors_page2
  if((digitalRead(touch_3_ok) == HIGH) && Page == 19 ){
    // code of save here and in no save call page_id(21)
    // if save call page_id(20);    
  }  
  //From data_sd_card_2 to data_sd_card_1 
  if((digitalRead(touch_4_exit) == HIGH) && Page == 20 ){
    page_id(19);    
  }  
  //From data_sd_card_3 to data_sd_card_1 
  if((digitalRead(touch_4_exit) == HIGH) && Page == 21 ){
    page_id(19);    
  }  
  //From data_sd_card_1 to data_page1 
  if((digitalRead(touch_4_exit) == HIGH) && Page == 19 ){
    page_id(17);    
  } 
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//SD card
/////////////////////////////////////////////////////////
  //From data_page1 to data_sd_card_1
  if((digitalRead(touch_3_ok) == HIGH) && Page == 17 ){
    page_id(19);
  }  

  //From data_sd_card_1 to data_sd_card_2 or Sensors_page2
  if((digitalRead(touch_3_ok) == HIGH) && Page == 19 ){
    // code of save here and in no save call page_id(21)
    // if save call page_id(20);    
  }  
  //From data_sd_card_2 to data_sd_card_1 
  if((digitalRead(touch_4_exit) == HIGH) && Page == 20 ){
    page_id(19);    
  }  
  //From data_sd_card_3 to data_sd_card_1 
  if((digitalRead(touch_4_exit) == HIGH) && Page == 21 ){
    page_id(19);    
  }  
  //From data_sd_card_1 to data_page1 
  if((digitalRead(touch_4_exit) == HIGH) && Page == 19 ){
    page_id(17);    
  } 
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//BLE_Bluetooth
/////////////////////////////////////////////////////////
  //From data_page2 to BLE1
  if((digitalRead(touch_3_ok) == HIGH) && Page == 18 ){
    page_id(22);
  }  
  //From BLE1 to BLE2
  if((digitalRead(touch_3_ok) == HIGH) && Page == 22 ){
    // open BLE and put the data in the chanal
    btStart();
    Serial.println("Starting BLE work!");
/////////////////////////////////////// 
//BLE
//////////////////////////////////////
  BLEDevice::init("MedicalSignalsBox");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

    //send as JSON look to be easy in the receive

    //ECG  
    data_send << "{";
    data_send << "ECG" <<":";
    data_send << "{";
    //ECG from array to one string 
    for (int i = 0; i < 100; i++)
    {
      data_send << ECG_data_temp1[i];
      if(i<99){
        data_send << ",";
      }
    }
    data_send << "}";
    data_send <<",";

    //ECG Time  
    data_send << "{";
    data_send << "ECG_Time" <<":";
    data_send << "{";
    data_send << "70714062019";
    //data_send << ECG_Time;
    data_send << "}";
    data_send <<",";


    //SPO2
    data_send << "{";
    data_send << "SPO2" <<":";
    data_send << "{";
    data_send << SPO2_valure;
    data_send << "}";
    data_send <<",";

    //SPO2 Time  
    data_send << "{";
    data_send << "SPO2_Time" <<":";
    data_send << "{";
    data_send << "70714062019";
    //data_send << SPO2_Time;
    data_send << "}";
    data_send <<",";

    //HR   
    data_send << "{";
    data_send << "HR" <<":";
    data_send << "{";
    data_send << HR_valure;
    data_send << "}";
    data_send <<",";

    //HR Time  
    data_send << "{";
    data_send << "HR_Time" <<":";
    data_send << "{";
    data_send << "70714062019";
    //data_send << ECG_Time;
    data_send << "}";
    data_send <<",";


    datasend = data_send.str();
    pCharacteristic->setValue(datasend);
    pService->start();
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();

    Serial.println("The data in the bluetooth channel Now");
    //pService->stop();
    //pAdvertising->stop();
    page_id(23);   

  }  
  //From BLE2 to BLE1 
  if((digitalRead(touch_4_exit) == HIGH) && Page == 23 ){
    //close the BLE here

    page_id(22);    
  }  
  //From BLE1 to data_page2 
  if((digitalRead(touch_4_exit) == HIGH) && Page == 22 ){
    page_id(18);    
  }  
/////////////////////////////////////////////////////////

 
}
//////////////////////// end loop 


////////////////////////////////////////////////////
// page_id fonction to get the page intarface  /////
////////////////////////////////////////////////////

void page_id(int id_number){
  if(id_number == 1){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, Home_page_1, 176, 176,COLOR_WHITE);
  }
  else if (id_number == 2){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, Home_page_2, 176, 176,COLOR_WHITE);
  }
  else if (id_number == 3){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, Home_page_3, 176, 176,COLOR_WHITE);  
  }
  else if (id_number == 4){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, Sensors_page1, 176, 176,COLOR_WHITE);   
  }
  else if (id_number == 5){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, Sensors_page2, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 6){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, Sensors_page3, 176, 176,COLOR_WHITE);   
  }
  else if (id_number == 7){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, ECG_page_home, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 8){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, ECG_on_record, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 9){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, ECG_save_data, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 10){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, SPO2_page_home, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 11){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, SPO2_on_record, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 12){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, SPO2_save_data, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 13){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, HR_page_home, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 14){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, HR_on_record, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 15){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, HR_save_data, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 16){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, info_page, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 17){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, data_page1, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 18){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, data_page2, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 19){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, data_sd_card_1, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 20){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, data_sd_card_2, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 21){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, data_sd_card_3, 176, 176,COLOR_WHITE);    
  }
  else if (id_number == 22){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, BLE1, 176, 176,COLOR_WHITE);
  }
  else if (id_number == 23){
    Page=id_number;
    tft.clear();
    tft.drawBitmap(0, 0, BLE2, 176, 176,COLOR_WHITE);    
  }
}