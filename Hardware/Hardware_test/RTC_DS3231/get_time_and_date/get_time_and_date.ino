#include <Wire.h>
#include "DS3231.h"

RTClib RTC;
const int DS3231_address=0x68; 

void setup () {
    Serial.begin(57600);
    Wire.begin();
    Wire.beginTransmission(DS3231_address);
}

void loop () {
  
    delay(1000);
  
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
    
}
