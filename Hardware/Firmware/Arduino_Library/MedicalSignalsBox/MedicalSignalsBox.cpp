/*
Medical Signals Box project
Developed by Walid Amriou
2019 
*/

// include core Wiring API
#include "WProgram.h"

// include this library's description file
#include "MedicalSignalsBox.h"

// include description files for other libraries used (if any)
#include "HardwareSerial.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

MedicalSignalsBox::MedicalSignalsBox()
{
  Serial.begin(9600);
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

void MedicalSignalsBox::print_test(void)
{
  // eventhough this function is public, it can access
  // and modify this library's private variables
  Serial.print("value is ");
  Serial.println(value);

  // it can also call private functions of this library
  doSomethingSecret();
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

void MedicalSignalsBox::getimage(int valure_of_image)
{
//if --- 

//else if ---


}

