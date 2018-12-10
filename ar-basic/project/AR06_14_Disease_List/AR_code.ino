#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

 

// 적외선 리모컨 라이브러리를 불러온다.

 

#include <IRremote.h>


// 적외선 수신부가 연결될 핀을 설정한다.

 

int irPin = 11;


int sw = 3;


IRrecv irrecv(irPin);


// 수신된 신호의 결과를 results 변수로 설정한다.


decode_results results;
decode_results results2;

long one  = 0xFFA25D;
long two = 0xFF629D;
long three  = 0xFFE21D;
long four = 0xFF22DD;
long five  = 0xFF02FD;
long six = 0xFFC23D;
long seven  = 0xFFE01F;
long eight = 0xFFA857;
long nine = 0xFF906F;
long zero = 0xFF9867;
long okay = 0xFF38C7;

void setup()


{
  lcd.init();
  lcd.backlight();
  lcd.print("Click a button!");
  // 시리얼 통신을 설정한다.
  Serial.begin(9600);
  // 적외선 리모컨 수신을 시작한다.

  irrecv.enableIRIn();



  // 13번 핀에 연결된 LED를 리모컨 수신시 점멸시킨다.

  irrecv.blink13(true);
 

  pinMode(sw,INPUT_PULLUP);

}


void loop()

{

   if (digitalRead(sw) == LOW) {

    delay(300);
    
Serial.println("");
Serial.print("진료가 끝났습니다.");

  }

  // 수신된 코드가 있을 때 실행한다.



  if (irrecv.decode(&results)){



    // 0xFFFFFFFF 값을 제외하고 출력한다.


    if(results.value != 0xFFFFFFFF){


      // 수신된 코드가 on1과 같을 때


        if(results.value == one){


      Serial.println("");


        lcd.clear();

        lcd.setCursor(0,0);

        lcd.print("List of disease");


         Serial.println("이비인후과 잦은질병목록");

         Serial.println(" ");

          Serial.println("알맞은 질병의 번호를 누르세요.");



        Serial.println("");

         Serial.println("1.독감");

         Serial.println("2.감기");

         Serial.println("3.편도선염");

           Serial.println("------------------------------------------------------------");


           delay(100);

           irrecv.resume();

           while(!irrecv.decode(&results2));  
      
           if (irrecv.decode(&results2)){

            if(results2.value != 0xFFFFFFFF){
 
                if(results2.value == one){

                  lcd.setCursor(0,1);

                  lcd.print("influenza ");

                    Serial.println("");

                    Serial.println("독감(influenza)입니다.");

                    Serial.println("독감은 갑자기 시작되는 경우가 대부분이며 고열과 오한을 동반합니다." );

                    Serial.println("-복용약-:타미플루");

                    Serial.println("타미플루:항바이러스제로 성분명은 oseltamivir(오셀타미비르),");

                    Serial.println("이 성분은 항바이러스제로 독감의 치료 및 예방에 사용합니다");

 

                }


               else if(results2.value == two){

                lcd.setCursor(0,1);

                  lcd.print("inf cold");

                      Serial.println("");

                      Serial.println("유행성감기(inf cold)입니다");

                     Serial.println("주로 나타나는 것은 기침, 두통, 미열, 콧물, 가래입니다.");

                    Serial.println("-복용약-");

                    Serial.println("*염화 라이소자임:염증성 부종의 완화");

                    Serial.println("*카르보 시스테인:점막 정상화 작용");

                    Serial.println("*염산 브롬헥신:기관지염 완화");

                    Serial.println("*슈도에페드린:감기,두통 완화 ");

 

             }

else if(results2.value == three){  

                                     

                    lcd.setCursor(0,1);

                  lcd.print("tonsillitis.");


                      Serial.println("");

                     Serial.println("급성 편도염(tonsillitis)입니다.");

 

                     Serial.println("증상은 인두통, 연하통, 전신권태 및 고열이 가장 흔하며 이러한 증상들은 갑작스런 고열,두통,오한으로 시작됩니다.");

                    Serial.println("복용약");

                    Serial.println("* 이부프로펜:적인 비스테로이드성 항염증진통제");

                    Serial.println("* 페니실린:항생제 효과가 있습니다. ");

                  Serial.println("* 아세틸살리실산:해열제의 효과가있습니다.");

 

               }


           }

 

           }

      }

 

      // 수신된 코드가 off1과 같을 때


      if(results.value == two){

 

        lcd.clear();

 

        lcd.print(results.value, HEX);

 

        Serial.println("");       

 

      }

 
      // 수신된 코드가 on2와 같을 때


      if(results.value == three){

 

        lcd.clear();

 

        lcd.print(results.value, HEX);

 

      }

 

      // 수신된 코드가 off2와 같을 때


      if(results.value == four){

 

        lcd.clear();

 

        lcd.print(results.value, HEX);

 

      }


      // 수신된 코드가 on3와 같을 때



      if(results.value == five){

 

        lcd.clear();

 

        lcd.print(results.value, HEX);

 

      }


      // 수신된 코드가 off3와 같을 때


      if(results.value == six){

 

        lcd.clear();

 

        lcd.print(results.value, HEX);

 

      }


    // 수신된 코드가 on4와 같을 때


      if(results.value == seven){

 

        lcd.clear();

 

        lcd.print(results.value, HEX);

 
      }



    // 수신된 코드가 off4와 같을 때


      if(results.value == eight){

 

        lcd.clear();

 

        lcd.print(results.value, HEX); 

 

      }

 
if(results.value == zero){

 
      }
 
    }

 


    // 다음 수신을 위해서 준비한다.

 

    irrecv.resume();

 

  }


  if (irrecv.decode(&results)){

 
    // 0xFFFFFFFF 값을 제외하고 출력한다.

 
    if(results.value != 0xFFFFFFFF){

 
      // 수신된 코드가 on1과 같을 때



        lcd.clear();

        lcd.print(results.value, HEX);

      }

 
  }

 

}

 
