/*
Medical Signals Box project
Developed by Walid Amriou
2019

MedicalSignalsBox.h - MedicalSignalsBox library for Wiring - description

*/

// ensure this library description is only included once
#ifndef Test_h
#define Test_h

// include types & constants of Wiring core API
#include "WConstants.h"

// library interface description
class Test
{
  // user-accessible "public" interface
  public:
    Test(int);
    void doSomething(void);

  // library-accessible "private" interface
  private:
    int value;
    void doSomethingSecret(void);
};

#endif

