/*
 예제 7.3
 DC모터 구동
*/
 
// 포텐쇼미터 핀 설정
int potentioMeterPin = 0;

// enable 핀 설정
int ENAPin = 3;
// in1 핀 설정
int in1Pin = 2;
// in2 핀 설정
int in2Pin = 4;

// Enable pin으로 출력할 PWM 신호 변수
int motorPWM;
// 속도 표시를 위한 변수
int motorVelocity;

void setup() {
  // 시리얼 통신 설정  
  Serial.begin(9600);

  // 핀 입출력 설정
  pinMode(ENAPin,OUTPUT);
  pinMode(in1Pin,OUTPUT);
  pinMode(in2Pin,OUTPUT);
}

void loop(){
  // 포텐쇼미터 값을 읽어옴
  int potentioMeter = analogRead(potentioMeterPin);

  // 포텐쇼미터 아날로그 입력값이 0~500 일 때 CW로 동작 
  if((potentioMeter >= 0) && (potentioMeter <=500)){
    // 포텐쇼미터 값에따라 motorPWM값을 변경한다
    motorPWM = map(potentioMeter,500,0,0,255);
    // enable 핀에 PWM 펄스를 출력하여 속도를 조절한다.
    analogWrite(ENAPin,motorPWM);
    // 모터를 CW로 회전
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);

    // 모터의 회전 방향을 출력하고 백분율로 속도를 표시한다    
    motorVelocity = map(potentioMeter,500,0,0,100);
    Serial.print("CW ");
    Serial.print(motorVelocity);
    Serial.println(" %");
  }
  // 포텐쇼미터 아날로그 입력값이 524~1023 일 때 CCW로 동작
  else if((potentioMeter >= 524) && (potentioMeter <=1023)){
    // 포텐쇼미터 값에따라 motorPWM값을 변경한다
    motorPWM = map(potentioMeter,254,1023,0,255);
    // enable 핀에 PWM 펄스를 출력하여 속도를 조절한다.
    analogWrite(ENAPin,motorPWM);
    
    // 모터를 CCW로 회전
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);

    // 모터의 회전 방향을 출력하고 백분율로 속도를 표시한다
    motorVelocity = map(potentioMeter,254,1023,0,100);
    Serial.print("CCW ");
    Serial.print(motorVelocity);
    Serial.println(" %");    
  }
  else{
    // 모터를 정지시킨다
    analogWrite(ENAPin,0);
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    
    // 모터 정지 메세지를 출력한다
    Serial.println("STOP");          
  }
  delay(100);
}

