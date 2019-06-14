//Measurement of Angle with MPU-6050

#include<Wire.h>

const int MPU_addr=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int minVal=265; int maxVal=402;

double x; 
double y; 
double z;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop(){ 
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x3B); 
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_addr,14,true); 
  
  /* Note about the next lines:
   * The expression Wire.read() << 8 takes the value returned by Wire.read(), 
   * which is an int, and shifts it 8 bits to the left, which is equivalent to 
   * multiplying by 256. If you are using a 32-bit microcontroller (e.g. 
   * an Arduino Due), this is safe. However, most Arduinos are based on an 
   * 8-bit AVR chip. On them, an int is 16-bits and can only hold values 
   * up to 32767. If the initial value is larger than 127, then the bit shift 
   * causes a signed integer overflow, which in C and C++ is undefined behavior 
   * (read: “illegal operation”). It is likely that everything runs fine 
   * and you get the expected result, but it is unwise to ever rely on 
   * undefined behavior in C or C++.
   * more here: https://arduino.stackexchange.com/questions/36383/what-does-this-notation-stands-for-wire-read-8-wire-read
   */
  AcX=Wire.read()<<8|Wire.read(); 
  AcY=Wire.read()<<8|Wire.read(); 
  AcZ=Wire.read()<<8|Wire.read(); 
  
/* Re-maps a number from one range to another. That is, 
 * a value of fromLow would get mapped to toLow, 
 * a value of fromHigh to toHigh, values in-between 
 * to values in-between, etc.
*/
  int xAng = map(AcX,minVal,maxVal,-90,90); //map(value, fromLow, fromHigh, toLow, toHigh)
  int yAng = map(AcY,minVal,maxVal,-90,90); 
  int zAng = map(AcZ,minVal,maxVal,-90,90);
  
  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
  
  Serial.print("AngleX= "); Serial.println(x);
  Serial.print("AngleY= "); Serial.println(y);
  Serial.print("AngleZ= "); Serial.println(z); 
  
  Serial.println("-----------------------------------------"); 
  
  delay(400); 
}
