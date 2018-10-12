#include "LedControlMS.h"

#define NBR_MTX 1 //number of matrices attached is one

LedControl lc=LedControl(4,3,2, NBR_MTX);//

unsigned long delayTime=1200;  // Delay between Frames

// Put values in arrays
byte invader1a[] =
{
   B00011000,  // First frame of invader #1
   B00111100,
   B01111110,
   B11011011,
   B11111111,
   B00100100,
   B01011010,
   B10100101
};

byte invader1b[] =
{
  B00011000, // Second frame of invader #1
  B00111100,
  B01111110,
  B11011011, 
  B11111111,
  B00100100,
  B01011010,
  B01000010
};

byte invader2a[] =
{
  B00100100, // First frame of invader #2
  B00100100,
  B01111110,
  B11011011,
  B11111111,
  B11111111,
  B10100101,
  B00100100
};

byte invader2b[] =
{
  B00100100, // Second frame of invader #2
  B10100101,
  B11111111,
  B11011011,
  B11111111,
  B01111110,
  B00100100,
  B01000010
};

void setup()
{
  lc.shutdown(0,false); // Wake up displays
//  lc.shutdown(1,false);
    // Set intensity levels
  lc.setIntensity(0,5);
//  lc.setIntensity(1,5);
    // Clear Displays
  lc.clearDisplay(0);
//  lc.clearDisplay(1);
}


//  Take values in Arrays and Display them
void sinvader1a()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,invader1a[i]);
  }
}

void sinvader1b()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,invader1b[i]);
  }
}

//void sinvader2a()
//{
//  for (int i = 0; i < 8; i++)
//  {
//    lc.setRow(1,i,invader2a[i]);
//  }
//}
//
//void sinvader2b()
//{
//  for (int i = 0; i < 8; i++)
//  {
//    lc.setRow(1,i,invader2b[i]);
//  }
//}

void loop()
{
// Put #1 frame on both Display
    sinvader1a();
    delay(delayTime);
//    sinvader2a();
//    delay(delayTime);


// Put #2 frame on both Display
    sinvader1b();
    delay(delayTime);
//    sinvader2b();
//    delay(delayTime);

}
