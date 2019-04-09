/*
 
Medical Signals Box project
Developed by Walid Amriou
2019 

Test of ILI9225 by ESP32 - LOLIN32
*/

#include "SPI.h"
#include "TFT_22_ILI9225.h"

#define TFT_CLK 18  // SCK
#define TFT_SDI 23  // SDA
#define TFT_RS  2   // RS
#define TFT_RST 15   // RST
#define TFT_CS  5  // CS
#define TFT_LED 0   // Già collegato a +5V/+3.3V

// Use hardware SPI (faster)
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);

const unsigned char gImage_ic[3872] PROGMEM = {/*add image hex here*/};

String duration;
unsigned long startTime;
// Setup
void setup() {
  tft.begin();
  Serial.begin(9600);
}

// Loop
void loop() {
  startTime = millis();
  //tft.drawBitmap(0, 0, gImage_ic, 176, 176, COLOR_CYAN);
  tft.setBackgroundColor(COLOR_BLACK);
  tft.setFont(Terminal6x8);
  tft.drawText(0, 178, "www.walidamriou.com", COLOR_CYAN);
  tft.drawText(0, 188, "Test of ILI9225 176x220 TFT screen", COLOR_GREEN);
  tft.drawText(0, 198, "SPI faster", COLOR_YELLOW);
  duration = String(millis() - startTime);
  tft.drawText(0, 208, duration, COLOR_WHITE);
  while (true);

}
