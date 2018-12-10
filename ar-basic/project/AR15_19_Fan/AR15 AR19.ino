void setup(){
  pinMode(3,OUTPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  Serial.begin(9600);
}
 
void loop(){
  if(digitalRead(5)==HIGH){
    analogWrite(3,255);
  }
  if(digitalRead(6)==HIGH){
    analogWrite(3,155);
  }
 if(digitalRead(7)==HIGH){
    analogWrite(3,0);
  }
  Serial.print(digitalRead(5));
  Serial.print(digitalRead(6));
  Serial.print(digitalRead(7));
  delay(100);
}
