#include <LiquidCrystal_I2C_Hangul.h>
#include <Wire.h>

LiquidCrystal_I2C_Hangul lcd(0x27,16,2);

int nMe; // nMe 라는 변수를 선언합니다.
int nBot; // nBot 이라는 변수를 선언합니다.
int ledPins[7] = {4, 3, 2, 5, 6, 8, 7}; // 7개의 LED와 연결된 핀 번호를 저장하는 배열을 선언합니다.
int dicePatterns[7][7] = { // 7X7 이중배열을 선언합니다.(가로 0~6, 세로 0~6)
  {0, 0, 0, 0, 0, 0, 1}, // 주사위 1
  {1, 0, 0, 0, 0, 1, 0}, // 주사위 2
  {1, 0, 0, 0, 0, 1, 1}, // 주사위 3
  {1, 0, 1, 1, 0, 1, 0}, // 주사위 4
  {1, 0, 1, 1, 0, 1, 1}, // 주사위 5
  {1, 1, 1, 1, 1, 1, 0}, // 주사위 6
  {0, 0, 0, 0, 0, 0, 0} // LED 전부 꺼짐
};
int blank = 6; // LED를 전부 꺼지게 하는 상태 값을 선언합니다.
int sw1 = 12; // push sw1을 디지털 12번 핀에 연결합니다.
int sw2 = 13; // push sw2를 디지털 13번 핀에 연결합니다.

void setup() { // 실행시 가장 먼저 호출되는 함수이며, 최초 1회만 실행됩니다.
  lcd.init();
  lcd.backlight();
  pinMode(sw1,INPUT_PULLUP); // 12번 핀을 입력 핀으로 설정합니다.
  randomSeed(analogRead(A4)); // 매번 재시작 할 때 마다 주사위를 랜덤으로 만들기 위한 함수이며, 이 함수를 제거하면 재시작 할 때마다 같은 순서로 주사위 눈이 출력됩니다.

  lcd.setCursor(0,0); // LCD의 가로 1번째 세로 1 번째 자리
  lcd.print("Bot : "); // LCD의 화면에 Bot : 출력
  lcd.setCursor(0,1);  // LCD의 가로 1번째 세로 2 번째 자리
  lcd.print("Me  : "); // LCD의 화면에 Me : 출력
  
  for(int i = 0; i < 7; i++){ // for문을 이용해 ledPins 배열에 해당하는 핀을 출력 핀으로 설정합니다.
    pinMode(ledPins[i], OUTPUT); // LED핀을 출력 핀으로 설정합니다.
    digitalWrite(ledPins[i], LOW); // LED 전부 꺼짐
  }
  pinMode(sw2, INPUT_PULLUP);   // 13번 핀을 입력 핀으로 설정합니다.
  randomSeed(analogRead(0)); // 매번 재시작 할 때 마다 주사위를 랜덤으로 만들기 위한 함수이며, 이 함수를 제거하면 재시작 할 때마다 같은 순서로 주사위 눈이 출력됩니다.
}

void loop() { // setup() 함수가 호출된 이후, loop() 함수가 호출되며, 블록 안의 코드를 무한히 반복 실행합니다.
  if(digitalRead(sw1)== LOW) { // 1번 스위치를 눌렀을 때
    for(int i=0; i<10; i++) { // 10번 반복
      nMe = random(1,6);  // Me라는 변수에 1~6까지의 랜덤 숫자 저장
      lcd.setCursor(6,0); // LCD의 가로 7번째 세로 첫 번째 자리
      lcd.print(nMe); // LCD의 Me 자리

      nBot = random(1,6); // Bot이라는 변수에 1~6까지의 랜덤 숫자 저장
      lcd.setCursor(6,1); // LCD의 가로 7번째 세로 두번 째 자리
      lcd.print(nBot); // LCD의 Bot 자리

      delay(200); // 0.2초간 딜레이를 줍니다. 
    }

    if(nMe > nBot) { // Me에 나온 숫자가 Bot에 나온 숫자 보다 클 때
      lcd.setCursor(8,0); // LCD의 가로 9번째 세로 첫 번 째 자리
      lcd.print("Win!! "); // LCD에 Win!! 출력
      lcd.setCursor(8,1); // LCD의 가로 9번째 세로 두 번 째 자리
      lcd.print("      "); // LCD에 공백 출력
    }
    else if(nMe < nBot) { // Me에 나온 숫자가 Bot에 나온 숫자 보다 작을 때
      lcd.setCursor(8,0); // LCD의 가로 9번째 세로 첫 번 째 자리
      lcd.print("      "); // LCD에 공백 출력
      lcd.setCursor(8,1); // LCD의 가로 9번째 세로 두 번 째 자리
      lcd.print("Win!! "); // LCD에 Win!! 출력 
    }
    else { // Me에 나온 숫자가 Bot에 나온 숫자와 같을 때
      lcd.setCursor(8,0); // LCD의 가로 9번째 세로 첫 번 째 자리
      lcd.print("Draw!! "); // LCD에 Draw!! 출력
      lcd.setCursor(8,1); // LCD의 가로 9번째 세로 두 번 째 자리
      lcd.print("      "); // LCD에 공백 출력
      delay(200); // 0.2초간 딜레이를 줍니다.
    }
  }
  if(!digitalRead(sw2)){ // 버튼을 눌렀을 경우 
    rollTheDice(); // 주사위를 굴립니다.
  }
  delay(100); // 0.1초간 딜레이를 줍니다.
}

void rollTheDice() {
  int result = 0; // 결과 저장 변수를 선언합니다.
  int lengthOfRoll = random(15, 25); // 주사위를 몇 번 굴릴 것인지 정하는 난수를 생성(15~25번 사이)합니다.
  for(int i = 0; i < lengthOfRoll; i++){ // 위에서 나온 숫자만큼 주사위를 돌립니다.
    result = random(0, 6); // 매번 나오는 주사위를 저장합니다.
    show(result); // 나온 주사위 눈을 LED 로 표시합니다.
    delay(100 + i * 20); // 주사위를 굴릴 때마다 돌아가는 속도를 느리게 해서 실제와 비슷하게 만듭니다.
  }
  for(int j = 0 ; j < 3 ; j++){ // 최종 주사위 눈이 결정되었을 때 강조 하기 위해 blink를 줍니다.
    show(blank); // 모든 LED 불을 OFF 시킵니다.
    delay(500); // 0.5초간 딜레이를 줍니다.
    show(result); // 결과 숫자의 눈을 LED로 표시합니다.
    delay(500); // 0.5초간 딜레이를 줍니다. 
  }
  show(blank); // 끝났으면 LED 전부 꺼짐
}

void show(int result ){ // 숫자를 LED로 표시하는 함수 
  for(int i = 0 ; i < 7 ; i++){ // 6번 반복
    digitalWrite(ledPins[i], dicePatterns[result][i]); // 나온 결과에 따라서 각각의 LED의 점등을 정해줍니다.
  }
}
