/*
 예제 6.1
 포텐쇼미터 입력
 */

// 0번 아날로그핀을 포텐쇼미터 입력으로 설정한다.
const int potentioMeterPin = 0;

//13번 핀에 연결되어 있는 내장 LED를 출력으로 사용한다.
const int ledPin = 13;

void setup() {
// 13번 핀을 출력으로 설정한다. 아날로그 입력핀은 설정이 불필요하다.
  pinMode(ledPin, OUTPUT);
// 시리얼 통신을 설정한다.  
  Serial.begin(9600);
}

void loop(){

  int adcValue; // 실제 센서로부터 읽은 값 (0~1023)
  int duty;     // LED 점멸 주기 (0~100%)
  
// 포텐쇼미터 값을 읽는다.
  adcValue = analogRead(potentioMeterPin);
// 포텐쇼미터 값을 0~100의 범위로 변경한다.
  duty = map(adcValue, 0, 1023, 0, 100);
  
// LED를 duty ms 만큼 점등한다.
  digitalWrite(ledPin, HIGH);
  delay(duty);
  
// 나머지 시간에는 소등시킨다.
  digitalWrite(ledPin, LOW);
  delay(100-duty);
  
// 시리얼 통신으로 ADC 값과 Duty를 출력한다.
  Serial.print("ADC Value is ");
  Serial.print(adcValue);
  Serial.print(". Duty cycle is ");
  Serial.print(duty);
  Serial.println("%");  
}

