/*
Medical Signals Box project
Developed by Walid Amriou
2019 
Test bluetooth (BLE) send data 
*/


#include <sstream>
#include <string>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

//valures of data send 
std::string body_position="unknown";
double body_temperature=0.1;
double HearRate=0.15;
double SpO2=0.65;
std::string time_record="unknown";

//Just valures for operation of send ..
std::stringstream data_send;
std::string datasend;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("MedicalSignalsBox");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );


  data_send << body_position << "," << body_temperature << "," << HearRate << "," << SpO2 << "," << time_record;
  datasend = data_send.str();

  pCharacteristic->setValue(datasend);


  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  Serial.println("The data in the bluetooth channel Now");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}
