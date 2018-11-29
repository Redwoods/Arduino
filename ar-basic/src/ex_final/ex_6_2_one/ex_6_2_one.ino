/*
 예제 6.2
 빛 입력
*/
 
// I2C 통신 라이브러리 설정 
#include <Wire.h>
// I2C LCD 라리브러리 설정
#include <LiquidCrystal_I2C.h>

// LCD I2C address 설정 PCF8574:0x27, PCF8574A:0x3F
LiquidCrystal_I2C lcd(0x3f,16,2);  // LCD address:0x27, 16X2 LCD

// 0번 아날로그핀을 CdS 셀 입력으로 설정한다.
const int CdSPin = 0;
const int ledPin = 13;

void setup() {
  
  lcd.init(); // LCD 설정
  lcd.backlight();  // 백라이트를 켠다.  

// 메세지를 표시한다.
  lcd.print("ex 6.2");
  lcd.setCursor(0,1);
  lcd.print("CdS Cell Test");
// 3초동안 메세지를 표시한다.
  delay(3000);

// 모든 메세지를 삭체한 뒤
// 숫자를 제외한 부분들을 미리 출력시킨다.
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ADC :  ");
  lcd.setCursor(0,1);
  lcd.print("Illuminance:");
  lcd.setCursor(15,1);
  lcd.print("%");

  pinMode(ledPin,OUTPUT);

}

void loop(){

  int adcValue; // 실제 센서로부터 읽은 값 (0~1023)
  int illuminance; // 현재의 밝기. 0~100%
    
  // CdS cell을 통하여 입력되는 전압을 읽는다.
  adcValue = analogRead(CdSPin);
  // 아날로그 입력 값을 0~100의 범위로 변경한다.
  illuminance = map(adcValue, 0, 1023, 100, 0);

  // 전에 표시했던 내용을 지우고
  // LCD에 ADC 값과 밝기를 출력한다.
  // 지우지 않으면 이전에 표시했던 값이 남게 된다.

  // 전에 표시했던 내용을 지운다.  
  lcd.setCursor(9,0);
  lcd.print("    "); 
  // ADC 값을 표시한다  
  lcd.setCursor(9,0);
  lcd.print(adcValue);

  // 전에 표시했던 내용을 지운다.
  lcd.setCursor(13,1);  
  lcd.print("  ");
  // 밝기를 표시한다  
  lcd.setCursor(12,1);  
  lcd.print(illuminance);

  if(adcValue <= 450)  digitalWrite(ledPin, LOW);
  else                  digitalWrite(ledPin, HIGH);


  delay(1000);
}

