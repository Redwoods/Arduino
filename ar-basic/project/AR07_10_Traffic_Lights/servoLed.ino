#include <Servo.h>

Servo motor1;
int servoMotorPin = 9; //서보모터 연결핀
int redLed = 12; // LED 연결핀
int greenLed = 13;
int pirPin = 2; // 센서 시그널핀
int pirState = LOW; // PIR 초기상태

void setup() {
  pinMode(redLed, OUTPUT); //LED Output 설정
  pinMode(greenLed, OUTPUT);
  pinMode(pirPin, INPUT); // 센서 Input 설정
  motor1.attach(servoMotorPin, 600, 2400);
  Serial.begin(9600);
  motor1.write(90);
}

void loop() {
  pirState = digitalRead(pirPin); // 센서값 읽기
  
  if (pirState == HIGH) { // 인체감지시
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    motor1.write(0);
    Serial.println("Motion detected!");
    delay(20000);
    }
    else {
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);
      motor1.write(90);
      Serial.println("Motion ended!");
    }
}
