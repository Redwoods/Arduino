/*
 예제 4.3
 LED 밝기 조절
*/

const int RedLed    =  3;	  //를 3번핀에 연결
const int GreenLed  =  5;	  //LED B를 5번핀에 연결
const int BlueLed   =  6;	  //LED B를 5번핀에 연결

void setup()
{
  ledOutput(255, 0, 0);
  delay(2000);
  ledOutput(0, 255, 0);
  delay(2000);
  ledOutput(0, 0, 255);
  delay(2000);
}

void loop()
{
//  for(int i=0;i<=255;++i){
//    ledOutput(255,i,0);
//    delay(10);
//  }
//  for(int i=0;i<=255;++i){
//    ledOutput(255,0,i);
//    delay(10);
//  }
//  for(int i=0;i<=255;++i){
//    ledOutput(i,0, 255);
//    delay(10);
//  }
//  for(int i=0;i<=255;++i){
//    ledOutput(i, 255, 255);
//    delay(10);
//  }
//  for(int i=0;i<=255;++i){
//    ledOutput(255, i, 255);
//    delay(10);
//  }
  for(int i=0;i<=255;++i){
    ledOutput(255, 255, 0);
    delay(10);
  }
} 

void ledOutput(int Red, int Green, int Blue){
  analogWrite(RedLed,Red);
  analogWrite(GreenLed,Green);
  analogWrite(BlueLed,Blue); 
}

