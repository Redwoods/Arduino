#include <SoftwareSerial.h>
SoftwareSerial AR1923BT(2, 3); // AR1923BT(Rx, Tx)
int BTstates=0;       // 블루투스 신호 상태 저장용 변수


const int X_AXIS =0; //마우스 X 축 (A0)
const int Y_AXIS =1; //마우스 Y 축 (A1) 
int xVal=0;
int yVal=0;

void setup() {
  AR1923BT.begin(9600);  
  Serial.begin(9600);
}

void loop() {
  xVal=map(analogRead(X_AXIS),0,1023,100,0); //x축값 읽어 저장 
  yVal=map(analogRead(Y_AXIS),0,1023,300,200); //Y축값 읽어 저장
  
  // 모터 전진 //
  if (xVal >= 60 && yVal >= 225 && yVal <=275)  { 
    AR1923BT.write('f');
    Serial.println('f');
  }
  // 모터 후진 //
  else if (xVal <= 40 && yVal >= 225 && yVal <=275)  { 
    AR1923BT.write('b');
    Serial.println('b');
  }
  // 모터 좌회전 //
  else if (yVal <= 240 && xVal >= 25 && xVal <= 75)  { 
    AR1923BT.write('l');
    Serial.println('l');
  }
  // 모터 우회전 //
  else if (yVal >= 260 && xVal >= 25 && xVal <= 75)  { 
    AR1923BT.write('r');
    Serial.println('r');
  }
 else { 
    AR1923BT.write('s');
    Serial.print('s');
  }
  delay(100); 
}
