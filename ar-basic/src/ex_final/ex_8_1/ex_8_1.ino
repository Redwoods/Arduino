/*
 예제 8.1
 적외선 리모컨 코드 읽기
*/

// 적외선 리모컨 라이브러리를 불러온다.
#include <IRremote.h>

// 적외선 수신부가 연결될 핀을 설정한다.
int irPin = 11;

// 적외선 수신부가 연결된 핀을 리모컨 수신 핀으로 설정한다.
IRrecv irrecv(irPin);

// 수신된 신호의 결과를 results 변수로 설정한다.
decode_results results;

void setup()
{
  // 시리얼 통신을 설정한다.
  Serial.begin(9600);

  // 적외선 리모컨 수신을 시작한다.
  irrecv.enableIRIn();

  // 13번 핀에 연결된 LED를 리모컨 수신시 점멸시킨다.
  irrecv.blink13(true);

}

void loop()
{
  // 수신된 코드가 있을 때 실행한다.
  if (irrecv.decode(&results)){
    // 0xFFFFFFFF 값을 제외하고 출력한다.
    if(results.value != 0xFFFFFFFF){
      // 수신된 값을 16진수 형태로 출력한다.
      Serial.print("Received Code is ");
      Serial.println(results.value,HEX);
    };
    // 다음 수신을 위해서 준비한다.
    irrecv.resume();
  }
}
