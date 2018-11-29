/*
 예제 9.2
 온습도 센서를 이용한 온습도 측정
*/

// DHT 라이브러리를 추가한다
#include "DHT.h"

#define DHTPIN 2  // DHT11이 연결된 핀을 설정한다
#define DHTTYPE DHT11   // 연결된 센서의 종류를 설정한다. DHT 11

// DHT 이란 이름으로 센서 이름을 설정한다
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  // 시리얼 통신을 설정하고 초기 메세지를 출력한다
  Serial.begin(9600);
  Serial.println("EX 9.2 DHT11 Test ");
  Serial.println("");
  dht.begin();  // DHT11 센서를 시작한다.
}

void loop()
{

  unsigned char t = dht.readTemperature();  // 온도를 읽는다.
  unsigned char h = dht.readHumidity();     // 습도를 읽는다.

      // 온도 출력
      Serial.print("Temperture is ");
      Serial.print(t);
      Serial.println(" C");

      //습도 출력
      Serial.print("Humisity is ");
      Serial.print(h);
      Serial.println(" %");
      Serial.println(" ");
      
  // 온습도를 다시 측정하기 위해 2초 쉰다
  delay(2000);
}

