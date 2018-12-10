#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

Servo doorservo;

LiquidCrystal_I2C lcd(0x3F,16,2);  

char secretCode[4][5] ={   // 세대와 비밀번호
{'1', '1', '2', '3' ,'4'},
{'2', '2', '3', '4' ,'5'},
{'3', '3', '4', '5' ,'6'},
{'4', '4', '5', '6' ,'7'}
};
char input[4];             // 비밀번호 입력을 받을 행렬
int tru;                   // 세대와 비밀번호 비교 변수
int section=0;             // 단계 구별
int hosu;                  // 세대지정 변수

const byte rows = 4;
const byte cols = 3;
char keys[rows][cols] ={
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}};
byte rowPins[rows] = {5,4,3,2};
byte colPins[cols] = {8,7,6};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

const char trigPin1 = 13;
const char echoPin1 = 12;
const char trigPin2 = 11;
const char echoPin2 = 10;
int pulseWidth1;
int distance1;
int pulseWidth2;
int distance2;

int led = 14;

void setup() 
{
  Serial.begin(9600);  //시리얼 통신 설정
  
  doorservo.attach(9);   //서보모터 설정
  doorservo.write(0);
  
  lcd.init();            //lcd 설정
  lcd.noBacklight();

  pinMode(trigPin1, OUTPUT);  //초음파센서 설정 
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  pinMode(led, OUTPUT);  //led 출력 설정
}

void loop() 
{
  if(section==0)      //section이 0일결우, 초음파 센서함수로 이동한다.
    senser();
  
  if(section==1) //section이 1일결우, 세대입력 함수로 이동한다.
    address();               
  
  if(section==2) //section이 2일결우, 비밀번호 입력 함수로 이동한다.
    password();              
}

//초음파센서 (각 센서에 distance의 값에 따라서 실행이 달라진다.) 
void senser()                               
{
  //lcd 초기화면 설정
  lcd.clear();
  lcd.noBacklight();
  
  digitalWrite(trigPin1, HIGH);             
  delayMicroseconds(10);
  digitalWrite(trigPin1,LOW);
  pulseWidth1 = pulseIn(echoPin1, HIGH);
  distance1 = pulseWidth1 / 58; 

  if(distance1 <= 5 && distance1 >= 0 )     //거리가 0~5cm 일경우, 다음 단계로 넘어가기위해 section변수를 1로 지정.  
  section = 1;

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2,LOW);
  pulseWidth2 = pulseIn(echoPin2, HIGH);
  distance2 = pulseWidth2 / 58; 

  if(distance2 <= 5 && distance2 > 0)        //거리가 0~5cm 일경우, 'OPEN'함수가 실행된다. 
  {
  Open();
  Close();
  section = 0;
  }
}

//세대입력 (세대를 입력하고 저장되있는 함수와 비교 후 다음실행을 판단한다.)
void address()                                
{  
  //lcd 글 표시 및 입력값 표시
  lcd.backlight();                            
  lcd.clear();                      
  lcd.setCursor(0, 0);
  lcd.print("Press your");
  lcd.setCursor(0, 1);
  lcd.print("Address   : ");
  lcd.setCursor(13, 1);
  char key = keypad.waitForKey();
  lcd.write(key);
  delay(1000);
 
  //저장되어있는 secretCode배열의 각 j행1열과 입력한 수 비교
  tru = 0;                                    
  for (int j = 0; j < 4; j++)
  {
    if (secretCode[j][0] == key)              //secretCode[j][1]와 입력한 수가 같다면 
    {                                         //다음 열의 비밀번호를 불러오기위해선 j를 기억
      tru = 1;                                
      hosu = j;                               //j를 기억하기 위해 다른변수를 사용해 저장
    }
    else if (secretCode[j][0] != key)
    {
    }

  }
  
 //tru변수를 통해 다음 실행 결정
  if (tru == 1)                              
  {
    section=2;              
  }
  else if (tru != 1)
  {
    tru = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Not Registered ");
    delay(1500);
      
    section=0; 
  }
}

//비밀번호 입력 (비밀번호를 입력하고 저장되있는 함수와 비교 후 다음실행을 판단한다.)
void password()
{
  lcd.clear();                      
  lcd.setCursor(0, 0);
  lcd.print(" Enter Password ");
  
  //비밀번호 4자리를 입력받음
  for (int i = 0; i < 4; i++)                      
  {
    char key = keypad.waitForKey();
    input[i] = key;
    lcd.setCursor(i + 6, 1);
    lcd.print("*");
  }
  
  //입력받은 비밀번호 input배열과 저장되어있는 secretCode배열을 비교 
  tru = 4;
  for (int j = 0; j < 4; j++)
  {
    if (secretCode[hosu][j+1] == input[j])             
    { }
    else if (secretCode[hosu][j+1] != input[j])        //한자리씩 틀릴때마다 tru함수는 -1씩 차감된다.
    { tru += -1;}
  }

  //tru변수를 통해 다음 실행 결정 
  if (tru == 4)
  {
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("      PASS");
    section=0;                  //초기 단계로 돌아가기 위해 section변수를 0으로 지정.
    Open();
    Close();
  }
  else if (tru != 4)
  {
    delay(500);                            
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("     WRONG");
    delay(500);
    lcd.setCursor(0,1);
    lcd.print(" CHECK PASSWORD! ");
    lcd.noBacklight();
    delay(250);
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
    lcd.backlight();
    delay(2000);
    
    section=0;  
  }
}

//문열림닫힘  
void Open()
{
  delay(500);
  doorservo.write(90);
  lcd.backlight();
  lcd.setCursor(0,1);
  lcd.print(" OPEN THE DOOR!");
  digitalWrite(led,HIGH);

void Close()
{
  doorservo.write(0);
  lcd.setCursor(0,1);
  lcd.print(" CLOSE THE DOOR ");
  
  delay(2000);                    //닫힌후 led와 lcd는 2초동안 켜져있다가 꺼진다.
  digitalWrite(led,LOW);

}
