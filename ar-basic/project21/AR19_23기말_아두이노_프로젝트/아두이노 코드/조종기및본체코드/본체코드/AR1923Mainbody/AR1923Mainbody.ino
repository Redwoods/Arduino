#include <SoftwareSerial.h>
SoftwareSerial AR1923BT(2, 3); // AR1923BT(Rx, Tx)
int A_1A = 9;
int A_1B = 10;
int B_1A = 5;
int B_1B = 6;
int speed = 250;   // speed: 0~ 255
char AR1923joyBT;
/* L9110s 모터드라이버
   오른쪽모터는
   L9110s A_1A 9
   L9110s A_1B 10
   왼쪽모터는
   L9110s B_1A 5
   L9110s B_1B 6
*/
void setup() {
  //핀을 초기화 하고, 출력설정
  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, LOW);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);
  Serial.begin(9600);  
  AR1923BT.begin(9600);
}

void loop() {
  if (AR1923BT.available()) {      
    AR1923joyBT = AR1923BT.read();
    Serial.println(AR1923joyBT);        
    switch (AR1923joyBT) { 
     case 'f' :        // 모터 전진        
        //모터A
        analogWrite(A_1A, speed);
        analogWrite(A_1B, 0);    
        //모터B
        analogWrite(B_1A, speed);
        analogWrite(B_1B, 0);
        break;
     
    case 'b' :        // 모터 후진                
        analogWrite(A_1A, 0);
        analogWrite(A_1B, speed);            
        analogWrite(B_1A, 0);
        analogWrite(B_1B, speed);  
        break;
       
    case 'l' :        // 모터 좌회전                
        analogWrite(A_1A, speed);
        analogWrite(A_1B, 0);            
        analogWrite(B_1A, 0);
        analogWrite(B_1B, speed);        
        break;    
    
    case 'r' :        //모터 우회전                
        analogWrite(A_1A, 0);
        analogWrite(A_1B, speed);            
        analogWrite(B_1A, speed);
        analogWrite(B_1B, 0);
        break;
    
    case 's' :        // 모터 정지      
      analogWrite(A_1A, 0);  
      analogWrite(A_1B, 0);    
      analogWrite(B_1A, 0);
      analogWrite(B_1B, 0);
      break;    
    }
  }
}
