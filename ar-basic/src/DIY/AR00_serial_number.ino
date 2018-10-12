/*
  예제 2.3
  컴퓨터로부터 시리얼 통신을 통하여 데이터 수신하기
*/

// LED 출력을 할 핀 번호 설정
const int ledPin = 13;

// 점멸횟수 변수 설정
int blinkNumber = 0;

// 문자열 배열을 설정한다.
String stringValue[] = {"Binary:", "Octal:"}; 

void setup() {
  // 9600bps로 시리얼 통신 설정
  Serial.begin(9600);
  // 13번 핀을 출력으로 설정
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 시리얼 통신으로 입력 받은 데이터가 있는지를 검사하여
  // 데이터가 있을 경우에 if문 안의 명령어를 실행
  if (Serial.available()) {
    // val 변수에 시리얼 통신값 읽어오기
    char val = Serial.read();
    // 입력된 값이 0~9의 숫자인지를 판단
    if (isDigit(val)) {
      // val은 ASCII 코드값이므로 숫자로 바꿔주기 위하여
      // '0'의 아스키 코드값을 빼줌
      // blinkNumber에는 실제 숫자가 저장된다.
      blinkNumber = (val - '0');
      if (blinkNumber < 10) {
        Serial.print("입력한 수:");
        Serial.print(blinkNumber);
        Serial.print(", ");
        Serial.print(stringValue[0]);
        Serial.print(blinkNumber, BIN);
        Serial.print(", ");
        Serial.print(stringValue[1]);
        Serial.println(blinkNumber, OCT);
        delay(2000);
      }
    }
  }
  // blinkNumber 만큼 LED를 점멸시킴
  for (char i = 0; i < blinkNumber; i++) {
    digitalWrite(ledPin, HIGH);
    delay(100 * blinkNumber);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  // 점멸 횟수를 리셋함
  blinkNumber = 0;
}
