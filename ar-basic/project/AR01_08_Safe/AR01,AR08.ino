#include <Keypad.h>  // Keypad.h 라이브러리 호출 [ 키패드 사용]
#include<Servo.h> // 서버사용

Servo locker; 
char secretCode[4] = {'1','2','3','4'};  // 비밀번호를 설정(초기비밀번호 1234)
char Change;
int position = 0; 
int wrong = 0;
// 비밀번호 비교시 쓸 변수 선언(맞는 경우[position]와 틀린경우[wrong] 2가지)

// 키패드 함수 시작
const byte rows = 4; 
const byte cols = 4;
// 키패드의 행, 열의 갯수

char keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
// 키패드 버튼 위치 설정

byte rowPins[rows] = {6, 7, 8, 9};
byte colPins[cols] = {5, 4, 3, 2};
// 키패드에 연결된 핀번호 설정(데이터 시트 참고)

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);
// 키패드 오브젝트 생성

// 키패드 관련 함수 끝

int redPin = 13;
int greenPin = 12;
// LED 2개의 핀번호 설정

// 각도 0으로 초기화(value), a 역시 체크 함수, 피에조 함수
int a=-1;
int b=-1;
int c=-1;
int piezo = 11;

// 각 키값에 대한 확인 변수 설정 [G,N,M]
boolean G =false;
boolean N =false;
boolean M =false;


//Led 출력 설정, 잠금 설정 함수 (초기값 잠금으로 설정), 서보모터인 10번핀 초기화, 피에조 초기화
void setup(){
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  setLocked(true);
  locker.attach(10);
  pinMode(piezo, OUTPUT); 
}
// 2개의 LED를 세팅해주고, 잠금상태를 기본으로 세팅해 줍니다.


void loop(){
  char key = keypad.getKey(); // 키패드에서 입력된 값을 가져옵니다.

if(key=='#') // # 버튼 눌러졌을경우 마스터 키 동작
{
  a=1; // a를 1로바꿔줌
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
// 두 LED를 켜줌으로 작동하고 있음을 보여줌
}

 if(a==1&&key >= 'A' && key <='D') //a가 1이고 Key값이 A 와 D 사이값이 눌러졌을 경우 작동합니다.
  {
    if(key=='A') // A 가 눌러지면 열림으로 설정 (각도 90)
    {
      setLocked(false);
    }
    else if(key=='B') //B가 눌러지면 닫힘으로 설정(각도 0)
    {
      setLocked(true);
    }
    else if (key=='C') // C가 눌러졌을 경우  비밀번호 변경 [ 비밀번호 변경하기전 한번 깜빡거림으로 비밀번호 변경 준비 확인)
    {
     digitalWrite(redPin,LOW);
     digitalWrite(greenPin,LOW);
     delay(100);
     digitalWrite(redPin,HIGH);
     digitalWrite(greenPin,HIGH);
     position =0;
     a=-1;
     G=false;
     while(!G) //만약 G가 false면 while 문을 동작한다
     {
      
      while(!N) //N 역시 false면 while 문 작동
      {
     Change=keypad.getKey(); // Change 변수애 키값을 받아온다
     if(Change) // 만약 Change 함수에 값이 있다면
     N=true; //N값을 true로 설정하여 N루프문을 빠져나온다
     M=false; // 초기 M값이 계속 바뀌게 되므로 false로 바꿔준다
      }
    if(Change >= 'A' && Change <='D'||Change=='*'||Change=='#') // 숫자가 아닌 다른 값을 누를 경우
    {
    N=false; 
    M=true; 
// N 루프문을 다시 돌고 M 루프문을 빠져 나간다.
    }
    else
    M=false;
// 그렇지 않으면 M 루프문을 돌아준다.


    if(position==0)
     secretCode[position]=Change;
    if(position==1)
    secretCode[position]=Change;
    if(position==2)
    secretCode[position]=Change;
    if(position==3)
    secretCode[position]=Change;

// 누른키 값을 각 자릿수로 변경시켜준다. 숫자가 아닌 경우에는 계속 숫자를 받을때 까지 무한 반복

    while(!M) // 숫자인 값을 눌렀을 경우 position값을 1증가시킨다.
    {
      position++;
      N=false;
      M=true;
    }

     if(position==4) // 만약 position값이 4가 되면
     {
    for(int i=0;i<2;i++) // LED를 2번 깜박여 값이 변경된 것을 확인시켜준다.
    {
     digitalWrite(redPin,LOW);
     digitalWrite(greenPin,LOW);
     delay(100);
     digitalWrite(redPin,HIGH);
     digitalWrite(greenPin,HIGH);
     delay(100);     
    }
    G=true; // 이후 G 루프문을 벗어난다.
   // 비밀번호 변경 후 초기 값으로 세팅
     setLocked(true);
     position=0;
     wrong=0;
     }
     }
    }
    else // D가 눌러졌을 경우 마스터키가 종료 되며 초기값으로 되돌아간다.
    {
    digitalWrite(greenPin,LOW);
      position = 0; 
      wrong = 0; // 입력 초기화
      setLocked(true); // 잠금상태로 세팅
    }
  }
  if(key == '*')
    { // * 버튼을 눌렀을 경우
       b=-1;
      position = 0; // 자리값 초기화
      wrong = 0; // 입력 초기화
      setLocked(true); // 잠금상태로 세팅
      a=-1;// a값 역시 -1로 초기화
    } 
  if(a==-1)
  {
  if((key >= '0' && key <= '9') ){
  // 키패드에서 입력된 값을 조사하여 맞게 입력된 값일 경우(키패드에 있는 버튼이 맞을경우) 비교
    
      if(key == secretCode[position]){ // 해당 자리에 맞는 비밀번호가 입력됬을 경우
      position++; // 다음 자리로 넘어 감
      wrong++;      
   // 틀린 값, 다음 자릿수 역시 같이 1씩 증가 시킨다 . 
      if(wrong==4)// 만약 wrong값이 4가 되면 1 감소시킨다. (Position에 해당하는 코드 값과 키값이 같음을 확인)
      wrong--;      
    }
    
    else if(key != secretCode[position]){ // 해당 자리에 맞지 않는 비밀번호가 입력됬을 경우
      position++; // position 값을 올려준다
      wrong++; // 비밀번호 오류 값을 늘려준다
      if(position == 4) // 오류값이 입력되었기 때문에 다른 값임을 확인 
      position--;
      
    }
    if(b==-1)
    {

    if(position == 4){ // 4자리 비밀번호가 모두 맞았을 경우
      setLocked(false); // 잠금상태를 해제 함
      delay(100);
     b=1;
    }

    if(wrong == 4){ // 비밀번호가 잘못 입력되었을 경우
      setLocked(true);
      blink(); // LED를 깜빡여 준다.
      position=0;
      wrong=0;
      a=-1;
    }
    }
  delay(100);
}
  }
}


void setLocked(int locked){ // 잠금시와 해제시에 맞는 LED를 세팅해 주는 함수
  if(locked) { // 잠금시 Red LED를 켜주고, Green LED를 꺼준다.
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
   int value=90;
  locker.write(value);
  a=-1;
  b=-1;
 }

  else{ // 해제시 Red LED를 꺼주고, Green LED를 켜준다.
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    wrong=0;
  int value=0;
  locker.write(value);
  } 
  pinMode(redPin, OUTPUT);
}

void blink(){ // 비밀번호 오류시 Red LED를 깜빡여 주는 함수. ( 소리도 같이 난다)
  analogWrite(piezo, 120);
  for(int i = 0; i < 8; i++){ // 딜레이 만큼 Red LED를 껐다 켰다 해준다. 총 8회
    for(int j=0;j<8;j++)
        {
         digitalWrite(redPin, HIGH);
         delay(50);
         digitalWrite(redPin,LOW);
        }
        digitalWrite(greenPin,HIGH);
        delay(50);
        digitalWrite(greenPin, LOW);
      }
      
    digitalWrite(redPin,HIGH);
    pinMode(piezo, INPUT);
    position=0;
    wrong=0;
  }

