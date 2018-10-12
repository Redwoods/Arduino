/*
 예제 4.5.2
 4-digit FND에 1초마다 증가하는 0~9999 숫자 표시하기 
*/

// 0~9까지 LED 표시를 위한 상수
const byte number[10] = { 
  //dot  gfedcba
  B00111111,	//0
  B00000110,	//1
  B01011011,	//2
  B01001111,	//3
  B01100110,	//4
  B01101101,	//5
  B01111101,	//6
  B00000111,	//7
  B01111111,	//8
  B01101111,	//9
};

// 4개의 digit에 연결된 핀 설정
const byte digitNumber[4] = {13, 12, 11, 10};

// 표시할 숫자 변수
int count = 0;  

// 각 자릿수를 저장하기 위한 변수
int value[4];

// 4개의 digit에 각각 다른 숫자를 표시하기 위해 사용하는 변수
int digitSelect=1;

// 시간을 측정하는데 사용되는 변수
long sampleTime;
int count5ms;

void setup()
{
  // 2~9번 핀을 a b c d e f g dot 의 순서로 사용한다.
  // 10~13번 핀을 Digit 1~4 의 순서로 사용한다.
  for(int i = 2; i <= 13; ++i){  
    pinMode(i,OUTPUT);// 2~13번핀을 출력으로 설정한다.
  };
  
  // 4 digit와 연결된 10~13번핀에 모두 HIGH 신호를 
  // 줘서 소등시킨다.  
  for(int i=10; i<=13; ++i){	
    digitalWrite(i, HIGH);   
  };
}

void loop()
{
  // 현재 시간을 저장한다.
  sampleTime = millis();  
  
  // count 변수값을 FND에 출력한다.
  fndDisplay(digitSelect, value[digitSelect-1]);
  ++digitSelect;
  if(digitSelect >= 5)  digitSelect = 1;
  
  // count 변수값이 0~9999의 범위를 갖도록한다.  
  if(count >= 9999)  count = 0;  
  else{
    // 앞서 저장한 시간에서 현재까지의 시간이 5ms일 경우에 
    // 다음 명령어를 실행한다.
    while(millis()-sampleTime < 5);

    ++count5ms;
    if(count5ms > 200){  // 
      // 5ms * 100 = 1s 가 되었을 때 count를 하나 올려준다
      ++count; 
  
      // 변수를 각 자릿수로 나눈다
      value[3] = count / 1000;
      value[2] = (count - (value[3]*1000)) / 100;
      value[1] = (count - (value[3]*1000) - (value[2]*100) ) / 10;
      value[0] = count - (value[3]*1000) - (value[2]*100) - (value[1]*10);

      count5ms = 0;
    };
  }
} 

// LED 켜는 루틴
void fndDisplay(int digit, int displayValue){  
  // bitValue 변수를 선언한다.
  boolean bitValue;

  // 4 digit와 연결된 10~13번핀에 모두 HIGH 신호를 줘서 소등시킨다.  
  for(int i=1; i<=4; ++i){	
    digitalWrite(digitNumber[i-1], HIGH);   
  };

  // FND에 원하는 숫자를 표시한다.  
  for(int i=0; i<=7; ++i){
  // number 상수의 하나의 비트값을 읽는다.
    bitValue = bitRead(number[displayValue],i);
  // 앞서 읽은 비트값을 2~9번핀에 출력시킨다.
    digitalWrite(i+2, bitValue);	        
  };

  // 4 digit중 표시를 원하는 digit만 켠다  
  for(int i=1; i<=4; ++i){	
    // 표시하기 원하는 자릿수는 LOW신호를 주어 켜고 나머진 OFF시킨다.
    if(digit == i)  digitalWrite(digitNumber[i-1], LOW);
    else    digitalWrite(digitNumber[i-1], HIGH);   
  };
}

