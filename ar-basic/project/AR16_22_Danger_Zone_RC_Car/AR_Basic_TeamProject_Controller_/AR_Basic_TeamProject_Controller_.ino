//Dot Matrix
#include "LedControlMS.h"
#define NBR_MTX 1

LedControl lc = LedControl(6, 5, 4, NBR_MTX);

//LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
//

//potentiometer
const int pin_potentio = A2;

//joystick
const int pin_xAxis = A0;
const int pin_yAxis = A1;
const int pin_zAxis = 3;
//

void setup() {
  Serial.begin(115200);
  
  //Dot matrix
  lc.shutdown(0, false);
  lc.setIntensity(0, 5);
  lc.clearDisplay(0);
  //

  //LCD
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Arduino Project");
  lcd.setCursor(0, 1);
  lcd.print("set READY");
  //
  
  //joystick
  pinMode(pin_zAxis, INPUT_PULLUP);
  //

  delay(1000);
}

int temperature = 0;
int humidity = 0;
char state = 0;

int CurrentSpeed = 0;
int xValue=0;
int yValue=0;
bool zValue=false;

char buf[80];

void loop() {
  potentiometer();
  joystick();
  community();
  print_lcd();
  dot_matrix();  
}

void community(){
  String data = "";
  while(Serial.available()){
    char temp = Serial.read();
    data.concat(temp);
  }
    Serial.println(data);
  delay(10);
  
    if(data[0] == 'a'){
      temperature = (data.substring(2, 5)).toInt();
      humidity = (data.substring(5, 8)).toInt();

      state = data[8];
    }

    String TX;
    sprintf(buf, "b)%3d%4d%4d", CurrentSpeed, xValue, yValue);
    TX = buf;
    
    TX += zValue == HIGH ? "1" : "0";

    delay(100);
}

void dot_matrix(){
  if(state == '1') print_safe();
  else if(state == '2') print_help();
  else print_nothing();

  delay(100);
}


void print_help(){
  lc.writeString(0,"HELP");
}

void print_safe(){
  lc.writeString(0,"safe");
}

void print_nothing() {
  lc.writeString(0," ");
}
//
void print_lcd(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp=");
  lcd.setCursor(5, 0);
  lcd.print(temperature);
  lcd.setCursor(8, 0);
  lcd.print("humid=");
  lcd.setCursor(14,0);
  lcd.print(humidity);
  lcd.setCursor(0, 1);
  lcd.print("Speed = ");
  lcd.setCursor(8,1);
  lcd.print(CurrentSpeed);
  delay(10);
}

void potentiometer(){
  int adcValue;
  adcValue = analogRead(pin_potentio);
  CurrentSpeed = map(adcValue, 0, 1023, 0, 255);

  delay(10);
}

void joystick(){
  xValue = analogRead(pin_xAxis);
  yValue = analogRead(pin_yAxis);
  zValue = digitalRead(pin_zAxis);

  delay(100);
}
