#include <Keypad.h>
#include <Servo.h>

int tru = 0;
int count = 0;
const int input = A5;
const int red = 13;
const int green = 12;
const int white = A1;
int buzerPin = 10;
int servoPin = 11;
char PW[6] = {'9','6','0','4','2','2'};
const byte ROWS = 4;
const byte COLS = 4;
byte rowPins[ROWS] = {6,7,8,9};
byte colPins[COLS] = {5,4,3,2};
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

Servo myservo;
Keypad keypad = Keypad( makeKeymap(keys),rowPins,colPins,ROWS,COLS);

void setup() {
  Serial.begin(9600);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(white,OUTPUT);
  pinMode(buzerPin, OUTPUT);
  pinMode(input,INPUT_PULLUP);
  myservo.attach(servoPin,600,2400);
  myservo.write(0);
}

void loop() {
  char key = keypad.getKey();
  if (key){
    Serial.print(key);
    if(key==PW[count]){
      count++;
      tru++;
    }else if(key!=PW[count]){
      count++;
    }
    if(key=='#')
      re();
    if(key=='C'){
    digitalWrite(white,LOW);
    tru=0;
    count=0;
    }
    if(count==6){
      if(tru==6)
       Su();
      else 
       Fa();
      tru=0;
      count=0;
    }    
    if(key=='B'){
    In();
    tru=0;
    count=0;
    }else if(key=='D'){
    Fa();
    tru=0;
    count=0;
    }  
  }
  int X = digitalRead(input);
  if(X==LOW){
  myservo.write(0);
  delay(100);
  tone(buzerPin,frequency('C'),3000);
  digitalWrite(red,HIGH);
  delay(5000);
  digitalWrite(red,LOW);
  }
}

void Su()
{
  myservo.write(90);
  delay(100);
  tone(buzerPin,frequency('g'),200);
  delay(150);
  tone(buzerPin,frequency('b'),100);
  delay(200);
  tone(buzerPin,frequency('C'),100);
  digitalWrite(green,HIGH);
  digitalWrite(white,HIGH);
  delay(2000);
  digitalWrite(green,LOW);
}
void In()
{
  myservo.write(90);
  delay(100);
  tone(buzerPin,frequency('g'),200);
  delay(150);
  tone(buzerPin,frequency('b'),100);
  delay(200);
  tone(buzerPin,frequency('C'),100);
  digitalWrite(green,HIGH);
  delay(2000);
  digitalWrite(green,LOW);
}
void Fa()
{
  myservo.write(0);
  delay(100);
  tone(buzerPin,frequency('c'),200);
  digitalWrite(red,HIGH);
  delay(500);
  digitalWrite(red,LOW);
  delay(100);
  tone(buzerPin,frequency('c'),200);
  digitalWrite(red,HIGH);
  delay(500);
  digitalWrite(red,LOW);
  delay(100);
  tone(buzerPin,frequency('c'),200);
  digitalWrite(red,HIGH);
  delay(500);
  digitalWrite(red,LOW);
}
void re()
{
  tru=0;
  count=0;
  myservo.write(0);
  tone(buzerPin,frequency('c'),200);
  digitalWrite(red,HIGH);
  delay(500);
  digitalWrite(red,LOW);
}
int frequency(char note){
  int i;
  int notes = 8;
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};  
  for (i = 0; i < notes; i++){
    if (names[i] == note){
      return(frequencies[i]);
    };
  };
  return(0);
}
