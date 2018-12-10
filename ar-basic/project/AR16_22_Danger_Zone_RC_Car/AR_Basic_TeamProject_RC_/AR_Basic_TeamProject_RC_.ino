//motor_driver
  const int motorA_front = 8;
  const int motorA_rear = 7;
  const int motorA_speed = 9;

  const int motorB_front = 5;
  const int motorB_rear = 4;
  const int motorB_speed = 6;
//

//ultraSonic
const int pin_echo = 12;
const int pin_trig = 13;
//

//CdS
const int pin_CdS = A0;
//

//Button
const int button1 = 11;
const int button2 = 10;
//

//LED
const int pin_led = 3;
//

//Temp_Humid
  #include <DHT.h>
  #define DHTPIN 2
  #define DHTTYPE DHT11

  DHT dht(DHTPIN, DHTTYPE);
//

void setup() {
  Serial.begin(115200);
  
  //motor_driver
  pinMode(motorA_front, OUTPUT);
  pinMode(motorA_rear, OUTPUT);
  pinMode(motorB_front, OUTPUT);
  pinMode(motorB_rear, OUTPUT);
  //
  
  //ultraSonic
  pinMode(pin_trig, OUTPUT);
  pinMode(pin_echo, INPUT);
  //
  
  //CdS
  //
  
  //Button
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  //
  
  //LED
  pinMode(pin_led, OUTPUT);
  //
  
  //Temp_Humid
  //
}

int CurrentSpeed = 0;
int xValue = 512;
int yValue = 512;
bool zValue = false;

float temperature = 0;
float humidity = 0;

int temp = 0;
int humid = 0;

int bright = 0;
int state = 0;
bool front_state = false;

char buf[80];

void loop() {
  temp_humid();
  button();
  CdS();
  community();
  ultrasonic();
  motor_driver();
}

//Coummunity
void community(){
  String data = "";
  while(Serial.available()){
    char temp = Serial.read();
    data.concat(temp);
  }
  delay(10);
  if(data[0] == 'b'){
    CurrentSpeed = (data.substring(2, 5)).toInt();
    xValue = (data.substring(5, 9)).toInt();
    yValue = (data.substring(9, 13)).toInt();

    if(data[13] == '1') zValue = true;
    else zValue = false;
  }

  String TX;
  sprintf(buf, "a)%3d%3d%1d",temp, humid, state);
  TX = buf;
  
  Serial.println(TX);
  delay(100);
}
//

//motor_driver
void motor_driver(){
  digitalWrite(motorA_front, LOW);
  digitalWrite(motorA_rear, LOW);
  digitalWrite(motorB_front, LOW);
  digitalWrite(motorB_rear, LOW);
  
  analogWrite(motorA_speed, 0);
  analogWrite(motorB_speed, 0);
  
  if(xValue < 100 && front_state){//left
    digitalWrite(motorA_front, LOW);
    digitalWrite(motorA_rear, HIGH);

    digitalWrite(motorB_front, HIGH);
    digitalWrite(motorB_rear, LOW);
  analogWrite(motorA_speed, CurrentSpeed);
  analogWrite(motorB_speed, CurrentSpeed);
  }
  if(xValue > 900 && front_state){//right
    digitalWrite(motorA_front, HIGH);
    digitalWrite(motorA_rear, LOW);

    digitalWrite(motorB_front, LOW);
    digitalWrite(motorB_rear, HIGH);
  analogWrite(motorA_speed, CurrentSpeed);
  analogWrite(motorB_speed, CurrentSpeed);
  }
  if(yValue < 100 && front_state){//front
    digitalWrite(motorA_front, HIGH);
    digitalWrite(motorA_rear, LOW);

    digitalWrite(motorB_front, HIGH);
    digitalWrite(motorB_rear, LOW);  
  analogWrite(motorA_speed, CurrentSpeed);
  analogWrite(motorB_speed, CurrentSpeed);
  }
  if(yValue > 900){//back
    digitalWrite(motorA_front, LOW);
    digitalWrite(motorA_rear, HIGH);

    digitalWrite(motorB_front, LOW);
    digitalWrite(motorB_rear, HIGH);
  analogWrite(motorA_speed, CurrentSpeed);
  analogWrite(motorB_speed, CurrentSpeed);
    }
  
  delay(100);
}
//
  
//ultraSonic
void ultrasonic(){
  float duration, distance;

  digitalWrite(pin_trig, HIGH);
  delay(10);
  digitalWrite(pin_trig, LOW);

  duration = pulseIn(pin_echo, HIGH);
  distance = ((float)(340 * duration) / 10000 ) / 2; //cm

  if(distance < 30)
    front_state = true;
  else
    front_state = false;
}
//
  
//CdS
void CdS(){
  int adcValue;
  int illuminance;

  adcValue = analogRead(pin_CdS);
  illuminance = map(adcValue, 0, 1023, 100, 0);

  if(illuminance < 10)
    digitalWrite(pin_led, HIGH);
  else
    digitalWrite(pin_led, LOW);

    delay(10);
}
//
  
//Button
void button(){
  int swVal1 = digitalRead(button1);
  int swVal2 = digitalRead(button2);
  
  if(swVal1 == LOW)  state = 1;
  if(swVal2 == LOW)  state = 2;

  if(swVal1 == HIGH && swVal2 == HIGH) state = 0;
}
//
  
//Temp_Humid
void temp_humid(){
  humidity = dht.readHumidity();  // 변수 h에 습도 값을 저장 
  temperature = dht.readTemperature();  // 변수 t에 온도 값을 저장
  
  humid = (int)(humidity);
  temp = (int)(temperature);
  delay(100);
}
//
