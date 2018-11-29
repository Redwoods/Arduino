/*
 예제 5.1
 스위치 입력
*/

// 내장된 LED를 사용하기 위해
// LED pin을 13번으로 설정
const int ledPin = 13;   
// 2번 핀을 스위치 입력으로 설정
const int inputPin = 2;

void setup() {
  // Arduino 13번 핀에 내장된 LED를 출력으로 설정한다.  
  pinMode(ledPin, OUTPUT);
  // 스위치 입력을 위하여 2번핀을 입력으로 설정하고 풀업시킨다.
  pinMode(inputPin, INPUT_PULLUP);
}

void loop(){
  int swInput = digitalRead(inputPin);  // 스위치 입력을 받는다
  int ledOutput = digitalRead(ledPin);  // LED의 출력 상태를 확인한다
  
  if (swInput == LOW){
    if (ledOutput)  digitalWrite(ledPin, LOW);// LED가 점등되어 있으면 소등
    else   digitalWrite(ledPin, HIGH);// LED가 소등되어 있으면 점등
  }

}   
    
