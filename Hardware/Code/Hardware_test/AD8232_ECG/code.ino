/*
Medical Signals Box project
Developed by Walid Amriou
2019 
Test AD8232 ECG
*/

void setup() {
  // initialize the serial communication:
  Serial.begin(57600);
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -

}

void loop() {
  
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    Serial.println('!');
  }
  else{
    // send the value of analog input 0:
      Serial.println(analogRead(A0));
  }
  //Wait for a bit to keep serial data from saturating
  // 3900 because 256Hz sample rate
  delayMicroseconds(3900);
}
