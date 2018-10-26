/*
 예제 5.3
 디지털 신호 입력 시간 측정하기
 */
#include <Wire.h>
// I2C LCD 라리브러리 설정
#include <LiquidCrystal_I2C.h>
 // LCD I2C address 설정 
 // PCF8574:0x27, PCF8574A:0x3F
LiquidCrystal_I2C lcd(0x27,16,2);  
// LCD address:0x27, 16X2 LCD, 0x3F

// 2번핀을 스위치 입력으로 설정
const int inputPin = 2;

// 현재의 시간을 저장하기 위한 변수
long startTime = 0;
// 실제 스위치가 눌린 후 지연되는 시간
long swCountTimer = 0;

void setup() {
  
  // 스위치 입력을 위하여 2번핀을 입력으로 설정하고 풀업시킨다
  pinMode(inputPin, INPUT_PULLUP);
  // 시리얼 통신을 설정한다  
  Serial.begin(9600);  
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Press button"); 
}

void loop(){
  // 스위치 입력이 발생하였을 경우 실행
  if(digitalRead(inputPin) == LOW){ 
    // 현재의 시간을 startTime 변수에 넣는다.    
    startTime=millis();
    // 스위치가 입력되는 동안 지연시킨다.
    while(digitalRead(inputPin)==LOW);
    // swCountTimer 변수에 스위치가 눌려진 시간을 넣는다.
    // 여기까지 측정된 시간에서 앞서 저장한 시간이 
    // 스위치가 눌려진 시간이 된다
    swCountTimer = millis() - startTime;
    // LCD로 경과 시간을 출력한다..
    delay(100);
    // 모두 삭제
    lcd.clear();
     // 커서를 좌측 상단으로
    lcd.setCursor(0,0);
    lcd.print("ARnn time span");
    // 커서를 두 번째 줄로
    lcd.setCursor(0,1);
    lcd.print(swCountTimer);
    lcd.print(" ms");    
  };
}

