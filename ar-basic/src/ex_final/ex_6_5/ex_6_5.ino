/*
 예제 6.5
 조이스틱 입력
 */
 
// I2C 통신 라이브러리 설정 
#include <Wire.h>
// I2C LCD 라리브러리 설정
#include <LiquidCrystal_I2C.h>

// LCD I2C address 설정 PCF8574:0x27, PCF8574A:0x3F
LiquidCrystal_I2C lcd(0x3f,16,2);  // LCD address:0x27, 16X2 LCD

// 0번 아날로그핀을 X 축 입력으로 설정
const int xAxisPin = 0;
// 1번 아날로그핀을 Y 축 입력으로 설정
const int yAxisPin = 1;
// 2번 디지털 입력 핀을 Z 축 입력으로 설정
const int zAxisPin = 2;

void setup() {
  
  // Z 축 입력은 디지털 입력으로 설정한다.  
  pinMode(zAxisPin,INPUT_PULLUP);
  
  lcd.init(); // LCD 설정
  lcd.backlight();  // 백라이트를 켠다.  

  // 메세지를 표시한다.
  lcd.print("ex 6.5");
  lcd.setCursor(0,1);
  lcd.print("Joystick");
  // 3초동안 메세지를 표시한다.
  delay(3000);

  // 모든 메세지를 삭체한 뒤
  // X축 Y축 문자를 출력한다.
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("X:");
  lcd.setCursor(0,1);
  lcd.print("Y:");
  lcd.setCursor(15,1);
}

void loop(){

  // X, Y, Z 축 값을 읽는다.
  int xValue = analogRead(xAxisPin);
  int yValue = analogRead(yAxisPin);  
  int zValue = digitalRead(zAxisPin);

  // 그래프를 그리기 위해서 X, Y 값을 조절한다.
  int xDisplay = map(xValue,0,1023,6,15);
  int yDisplay = map(yValue,0,1023,6,15);
  
  // 첫 째 줄에 전에 표시했던 내용을 지운다.  
  lcd.setCursor(2,0);
  lcd.print("              "); // 14칸 공백
  // X 축의 ADC 값을 출력한다.
  lcd.setCursor(2,0);
  lcd.print(xValue);
  // 조이스틱의 X 값에 따라 그래프를 출력한다
  lcd.setCursor(xDisplay,0);
  lcd.print("|");

  // 둘째 줄에 전에 표시했던 내용을 지운다.
  lcd.setCursor(2,1);
  lcd.print("              "); // 14칸 공백
  // Y 축의 ADC 값을 출력한다.
  lcd.setCursor(2,1);
  lcd.print(yValue);
  // 조이스틱의 Y 값에 따라 그래프를 출력한다
  lcd.setCursor(yDisplay,1);
  lcd.print("|");

  // Z 방향으로 눌렸을 때 백라이트를 점멸한다.
  if(zValue == LOW){
    lcd.noBacklight();
    delay(300);
    lcd.backlight();    
  }
  delay(100);
}

