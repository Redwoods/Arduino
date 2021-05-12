boolean DigitOn = LOW;
boolean DigitOff = HIGH;
boolean SegOn=HIGH;
boolean SegOff=LOW;
int DigitPins[] = {10,11,12,13};
int SegmentPins[] = {2,3,4,5,6,7,8,9};

int BLANK[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int N0[]    = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
int N1[]    = {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW};
int N2[]    = {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW};
int N3[]    = {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW};
int N4[]    = {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW};
int N5[]    = {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW};
int N6[]    = {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
int N7[]    = {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW};
int N8[]    = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
int N9[]    = {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, LOW};
int NP[]    = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH};
int* lights[4];
char incoming[9] = {};  
 
void setup() {
  Serial.begin(9600);
 
  for (byte digit=0;digit<4;digit++) {
    pinMode(DigitPins[digit], OUTPUT);
  }
  for (byte seg=0;seg<8;seg++) {
    pinMode(SegmentPins[seg], OUTPUT);
  }
  lights[0] = N1;
  lights[1] = N2;
  lights[2] = N3;
  lights[3] = N4;
}
void loop() {
  if (Serial.available() > 0) {
    int i = 0;
    memset(incoming, 0, sizeof(incoming));
    while (Serial.available() > 0 && i < sizeof(incoming) - 1) {
      incoming[i] = Serial.read();
      i++;
      delay(3);
    }
    Serial.println(incoming);  
    int counter = -1;
    for (int tmp = 0; tmp < 9; tmp++) {
      counter++;
      switch(incoming[tmp]){
        case '0': 
            lights[counter] = N0; 
          break;
        case '1': 
            lights[counter] = N1; 
          break;
        case '2': 
            lights[counter] = N2; 
          break;
        case '3': 
            lights[counter] = N3; 
          break;
        case '4': 
            lights[counter] = N4;           
          break;
        case '5': 
            lights[counter] = N5; 
          break;
        case '6': 
            lights[counter] = N6; 
          break;
        case '7': 
            lights[counter] = N7; 
          break;
        case '8': 
            lights[counter] = N8; 
          break;
        case '9': 
            lights[counter] = N9; 
          break;
        case '.': 
            lights[counter] = NP; 
          break;
          
        case 1 ... 43: counter--; break;
        case 47: counter--; break;
        case 91 ... 96: counter--; break;
        case 123 ... 127: counter--; Serial.println("above 122"); break; 
 
        default: lights[counter] = BLANK;
      }
    }
    for (int y = 0; y < 4; y++) {
      Serial.print(y);
      Serial.print(": ");
      for (int z = 0; z < 8; z++) {
        Serial.print(lights[y][z]);
      }
      Serial.println("");
    }
  }
  for (byte seg=0;seg<8;seg++) {
    digitalWrite(SegmentPins[seg],SegOn);
    for (byte digit=0;digit<4;digit++){
      if (lights[digit][seg]==1) {
        digitalWrite(DigitPins[digit],DigitOn);
      }
    }
    for (byte digit=0;digit<4;digit++){
      digitalWrite(DigitPins[digit],DigitOff);
    }
    digitalWrite(SegmentPins[seg],SegOff);
  }
}
