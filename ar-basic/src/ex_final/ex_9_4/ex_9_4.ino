/*
예제 9.4
RFID
*/

// SPI 라이브러리를 불러온다.
#include <SPI.h>
// MFRC522 라이브러리를 불러온다
#include <MFRC522.h>

// SS 핀을 10번 핀으로 설정한다.
#define SS_PIN 10    //Arduino Uno, Data
// Reset 핀을 9번 핀으로 설정한다.
#define RST_PIN 9

// mfrc522란 이름의 RFID 판독기를 설정한다.
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  // 시리얼 통신을 설정한다.	
  Serial.begin(9600);
  // SPI 통신을 시작한다.
  SPI.begin();
  // 앞서 설정한  mrfc522란 이름의 RFID 판독기를 시작한다.
  mfrc522.PCD_Init();        // Init MFRC522 card
  Serial.println("Please touch your card");
  Serial.println(" ");
}

void loop() {       
  // 새로운 카드를 기다린다.
  if (!mfrc522.PICC_IsNewCardPresent())  return;
  // 카드를 읽는다.
  if (!mfrc522.PICC_ReadCardSerial())  return;
  // 'Card UID: '메세지를 출력한다.
  Serial.print("Card UID:");

  // 판독기에 입력된 UID의 바이트수 만큼 읽어낸다.
  // UID는 카드의 종류에 따라 최대 8바이트를 갖는다.
  for (byte i = 0; i < mfrc522.uid.size; i++) {
  // UID를 시리얼 통신으로 출력한다.
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  } 

  // 시리얼 통신으로 'PICC type: '메세지를 출력한다.
  Serial.print("   PICC type: ");
  // picType 변수에 picc type을 저장한다. 
  byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  // 시리얼 통신으로 picc type을 출력한다.
  Serial.println(mfrc522.PICC_GetTypeName(piccType));
  // 줄바꿈
  Serial.println(" ");

  // mfrc522 판독기를 초기화 한다
  mfrc522.PICC_HaltA(); // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
}
