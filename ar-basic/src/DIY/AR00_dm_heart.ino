#include "LedControlMS.h"

#define NBR_MTX 1 //number of matrices attached is one

LedControl lc=LedControl(4,3,2, NBR_MTX);//

unsigned long delayTime=1200;  // Delay between Frames

// Put values in arrays
byte heart1a[] =
{
   B00100100,  // First frame of heart
   B01011010,
   B10000001,
   B10000001,
   B10000001,
   B01000010,
   B00100100,
   B00011000
};

byte heart1b[] =
{
  B00000000, // Second frame of heart
  B01100110,
  B11111111,
  B11111111, 
  B11111111,
  B01111110,
  B00111100,
  B00011000
};

void setup()
{
  lc.shutdown(0,false);  // Wake up displays
  lc.setIntensity(0,5); // Set intensity levels
  lc.clearDisplay(0); // Clear Displays
}

//  Take values in Arrays and Display them
void heart1()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,heart1a[i]);
  }
}

void heart2()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,heart1b[i]);
  }
}

void loop()
{
// Put #1 frame on the first Display
    heart1();
    delay(delayTime);

// Put #2 frame on the first Display
    heart2();
    delay(delayTime);
}
