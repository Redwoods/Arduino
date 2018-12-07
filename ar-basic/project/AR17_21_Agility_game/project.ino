#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//LED pins
int Led1 = 2;
int Led2 = 3;
int Led3 = 4;
int Led4 = 5;
int Led5 = 6;
//Button pin
int Btn = 8;

boolean btn_prv = LOW; //to check button change
int Light_ptr = 0; //pointer of lightning led
int led_delay = 1000; //delay time to turn on next LED
long lastTime = millis();//to check time change
int score = 0;

void newGame(){
    score = 0;
    Light_ptr = 0;
    led_delay = 1000;
    
    lcd.clear();
    lcd.print("NewGame Score:0");
}

void move(int ptr){
    digitalWrite(Led1, LOW);
    digitalWrite(Led2, LOW);
    digitalWrite(Led3, LOW);
    digitalWrite(Led4, LOW);
    digitalWrite(Led5, LOW);
    if(ptr == 1) ptr = Led1;
    else if(ptr == 2) ptr = Led2;
    else if(ptr == 3) ptr = Led3;
    else if(ptr == 4) ptr = Led4;
    else if(ptr == 5) ptr = Led5;
    else return;
    digitalWrite(ptr, HIGH);

}

void setup(){

    lcd.init();
    lcd.backlight();
  // 메세지를 표시한다.
    lcd.print("Arduino Project");
    lcd.setCursor(0,1);
    lcd.print("AR17    AR21");
  // 3초동안 메세지를 표시한다.
    delay(3000);
    
    newGame();


    pinMode(Led1, OUTPUT);
    pinMode(Led2, OUTPUT);
    pinMode(Led3, OUTPUT);
    pinMode(Led4, OUTPUT);
    pinMode(Led5, OUTPUT);
    pinMode(Btn, OUTPUT);


}

void loop(){

    //sequential flashing
    if(millis() - lastTime >= led_delay){
        lastTime = millis();
        Light_ptr++;
        if(Light_ptr >= 6) Light_ptr = 1;
        move(Light_ptr);
    }
    
    //case of button is pushed
    btn_prv = digitalRead(Btn);
    if(digitalRead(Btn) == HIGH && btn_prv == LOW){
        if(Light_ptr == 3){//case succeed
            
            //blink
            move(0);//turn off
            delay(50);
            move(3);//turn on 3rd

            //make faster (decrease delay)
            if(led_delay > 700)         led_delay -= 100;
            else if(led_delay > 500)    led_delay -= 50;
            else if(led_delay > 300)    led_delay -= 25;
            else if(led_delay > 10)     led_delay -= 10;
            else if(led_delay > 1)      led_delay -= 1;

            //set score
            score = 1000-led_delay;
            
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Game Score : ");
            lcd.setCursor(0,1);
            lcd.print(score);
        }
        else{//case failed

            //print result via consol
            lcd.clear();
            lcd.print("GAME OVER");
            delay(3000);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Final Score : ");
            lcd.setCursor(0,1);
            lcd.print(score);
     

            //blinking
            for(int x=0; x<10; x++){
                if(x%2 ==0) move(0);
                else move(Light_ptr);
                delay(200);
            }

            //show score value via LED
            if(score != 0){
                move(1);
                delay(500);
            }
            if(score > 200){
                digitalWrite(Led2, HIGH);
                delay(500);
            }
            if(score > 400){
                digitalWrite(Led3, HIGH);
                delay(500);
            }
            if(score > 750){
                digitalWrite(Led4, HIGH);
                delay(500);
            }
            if(score > 900){
                digitalWrite(Led5, HIGH);
                delay(500);
            }
            delay(3000);
            newGame();
        }
    }
}
