/*
 
Medical Signals Box project
Developed by Walid Amriou
2019 
Test of TTP224 switch touch sensor digital 4 

*/

bool val1,val2;
void setup() {
  pinMode(15,INPUT);
  pinMode(2,INPUT);
  Serial.begin(9600);

}

void loop() {
  val1 = digitalRead(15);   // read the input pin
  val2 = digitalRead(2);   // read the input pin
if(digitalRead(15)==HIGH){
  Serial.println("15");
}
if(digitalRead(2)==HIGH){
  Serial.println("2");
}
  }
