/*
 DIY-2
*/

// start number
int number = 0;

// 문자열 세가지를 설정한다.
String stringValue[]={"Binary:", "Hexadecimal:"}; // array

void setup() {
  // 9600bps로 시리얼 통신 설정
  Serial.begin(9600);
}

void loop() {

  // 'char Value'를 출력하고 문자열과 숫자를 변수 유형별로 출력한다.
  Serial.print("Number = ");
  Serial.print(number);
  Serial.print(", ");
  Serial.print(stringValue[0]);  // stringValue 중 첫 번째 문자열 출력
  Serial.print(number,BIN); // 2진수 형태로 출력
  Serial.print(", ");
  Serial.print(stringValue[1]);  // stringValue 중 첫 번째 문자열 출력
  Serial.print(number,HEX); // 16진수 형태로 출력
  // 줄바꿈
  Serial.println();
   
  number++;     // number 1 증가
  
  if(number > 15) {
    Serial.print("Mission completed!");
    delay(1000);
    exit(0);
  }
  
  delay(1000);  // 1초동안 지연시킨다.
}

