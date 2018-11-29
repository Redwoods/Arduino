/*
 예제 2.2
 변수 유형별 Arduino에서 컴퓨터로 전송하기
*/

// 65란 숫자를 유형별 변수에 저장한다.
char   charValue = 65;
int    intValue = 65;
float  floatValue = 65.0;

// 문자열 네가지를 설정한다.
String stringValue[]={"Binary:", "Decimal:", "Hexadecimal:", "ASCII:"}; // array

void setup() {
  // 9600bps로 시리얼 통신 설정
  Serial.begin(9600);
}

void loop() {

  Serial.println("*** Hello Arduino by HPnn***");
  Serial.println();
  
  // 'char Value'를 출력하고 문자열과 숫자를 변수 유형별로 출력한다.
  Serial.println("*** char Value ***");
  Serial.print(stringValue[0]);  // stringValue 중 첫 번째 문자열 출력
  Serial.println(charValue,BIN); // 2진수 형태로 출력
  Serial.print(stringValue[1]);  // stringValue 중 두 번째 문자열 출력
  Serial.println(charValue,DEC); // 10진수 형태로 출력
  Serial.print(stringValue[2]);  // stringValue 중 세 번째 문자열 출력
  Serial.println(charValue,HEX); // 16진수 형태로 출력
  Serial.print(stringValue[3]);  // stringValue 중 네 번째 문자열 출력
  Serial.write(charValue);  // charValue에 해댕하는 ASCII 코드값 출력
  // 줄바꿈
  Serial.println();
  // 줄바꿈
  Serial.println();

  // 'int Value'를 출력하고 문자열과 숫자를 변수 유형별로 출력한다.
  Serial.println("*** int Value ***");
  Serial.print("int Value:");
  Serial.println(intValue);
  Serial.print("char(intValue):");
  Serial.write(intValue);
  Serial.println();
  Serial.println();

  // 'float Value'를 출력하고 문자열과 숫자를 변수 유형별로 출력한다.  
  Serial.println("*** float Value ***");
  Serial.print("float Value:");
  Serial.println(floatValue);
  //Serial.write(floatValue);

  Serial.println();
    
  charValue++;  // charValue 1 증가
  intValue++;   // intValue 1 증가
  floatValue +=0.1;  // floatValue 0.1 증가
  
  delay(10000);  // 10초동안 지연시킨다.
}
