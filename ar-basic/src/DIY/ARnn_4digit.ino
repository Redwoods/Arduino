/*
 예제 4.5.1 응용
 4-digit FND로 
 ‘XXX1’, ‘XX2X’, ‘X3XX’, ‘4XXX’ 의 표시가 1초 간격으로 반복
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

// 표시할 숫자 변수
int count = 1;  
int fnd_index = 13;  // FND4 -> 숫자 1부터 시작

void setup()
{
  // 2~9번 핀을 a b c d e f g dot 의 순서로 사용한다.
  // 10~13번 핀을 Digit 1~4 의 순서로 사용한다.
  for(int i = 2; i <= 13; ++i){  
    pinMode(i,OUTPUT);// 2~13번핀을 출력으로 설정한다.
  };
  
  // 4 digit와 연결된 10~13번핀에 모두 HIGH 신호를 줘서 소등시킨다
  for(int i=10; i<=13; ++i){	
    digitalWrite(i, HIGH);  // LOW);   
  };
  
}

void loop()
{
  // count 변수값을 FND에 출력한다.
  // 우측 FND에 1을 출력
  digitalWrite(fnd_index, LOW);
  fndDisplay(count);  
  delay(1000);
  // 출력 후 FND 소등
  digitalWrite(fnd_index, HIGH);
  
  if(count >= 4){
    count = 1;
    fnd_index = 13;
  }
  else {
    count++;
    fnd_index--;
  }
   
  delay(100);
} 

// LED 켜는 루틴
void fndDisplay(int displayValue){  
  // bitValue 변수를 선언한다.
  boolean bitValue;

  // 2~9번핀에 모두 LOW 신호를 줘서 소등시킨다.
  for(int i=2; i<=9; ++i){	
    digitalWrite(i, LOW);
  };

  for(int i=0; i<=7; ++i){
  // number 상수의 하나의 비트값을 읽는다.
    bitValue = bitRead(number[displayValue],i);
  // 앞서 읽은 비트값을 2~9번핀에 출력시킨다.
    digitalWrite(i+2, bitValue);	        
  };
}

