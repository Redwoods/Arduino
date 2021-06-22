#include <SoftwareSerial.h>
SoftwareSerial AR1923BT(2, 3); //BlueTooth(Rx, Tx)

void setup() {
  Serial.begin(9600);
  Serial.println("Enter AT Commands: ");
  AR1923BT.begin(9600);
}

void loop() {
  if (AR1923BT.available())
    Serial.write(AR1923BT.read());

  if (Serial.available())
    AR1923BT.write(Serial.read());
}
