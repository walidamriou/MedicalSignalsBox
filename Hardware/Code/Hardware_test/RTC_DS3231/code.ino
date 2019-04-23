/*
Medical Signals Box project
Developed by Walid Amriou
2019 
set the time & the date to RTC DS3231
*/

#include <Wire.h>
#include "DS3231.h"

RTClib RTC;

void setup () {
    Serial.begin(9600);
    Wire.begin();
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
    
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");
}
