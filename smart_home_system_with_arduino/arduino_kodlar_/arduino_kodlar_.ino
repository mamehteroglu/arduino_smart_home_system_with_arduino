//-------------------------------------------SICAKLIK SENSÖRÜ------------------------------------------------
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
#define LM35Pin A1
//-------------------------------------------YANGIN ALARMI---------------------------------------------------
#define yanginpin A0
#define zil 18
//-------------------------------------------HAREKET SENSÖRÜ-------------------------------------------------
int lamba = 19;
int pin = 17;
int deger = 0;
int harekets = LOW;
//-------------------------------------------KEYPAD----------------------------------------------------------
#include <Keypad.h>
const byte satir=4;
  const byte sutun=3;
    int redled = 39;
      int greenled = 37;
        char* sifre = "1234";
          char sifregirilen[5];
            int say = 0;
              char tuslar[satir][sutun] = {
                {'1','2','3'},
                {'4','5','6'},
                {'7','8','9'},
                {'*','0','#'}
              };
                byte satirpin[satir] = {53,51,49,47};
                  byte sutunpin[sutun] = {45,43,44};
                    Keypad klavye = Keypad(makeKeymap(tuslar),satirpin,sutunpin,satir,sutun);















void setup() {
//-------------------------------------------SICAKLIK SENSÖRÜ------------------------------------------------
pinMode(LM35Pin,INPUT);
lcd.begin(16,2);
//-------------------------------------------YANGIN ALARMI---------------------------------------------------
pinMode(yanginpin,INPUT_PULLUP);
  pinMode(zil, OUTPUT);
//-------------------------------------------HAREKET SENSÖRÜ-------------------------------------------------
  pinMode(lamba,OUTPUT);
    pinMode(pin,INPUT);
      Serial.begin(9600);
//-------------------------------------------KEYPAD----------------------------------------------------------
  Serial.begin(9600);
    pinMode(redled,OUTPUT);
      pinMode(greenled,OUTPUT);

}















void loop() {
//-------------------------------------------SICAKLIK SENSÖRÜ------------------------------------------------
float okuma = analogRead(LM35Pin);
    float derece = okuma*(5.0/1023.0)*100;
      lcd.setCursor(0,0);
        lcd.print("Sicaklik:");
          lcd.setCursor(9,0);
            lcd.print(derece);
              lcd.print("C");

      if(derece>30.0){
      digitalWrite(LM35Pin,HIGH);
        lcd.setCursor(0, 1);
          lcd.print("SICAKLIK ARTTI");
      }else if(derece<20.0){
        digitalWrite(LM35Pin,HIGH);
           lcd.setCursor(0, 1);
              lcd.print("SICAKLIK DUSTU");
      }else{
        lcd.setCursor(0,0);
          lcd.print("Sicaklik:");
            lcd.setCursor(9,0);
              lcd.print(derece);
                lcd.setCursor(0, 1);
                  lcd.print("              ");
      }
//-------------------------------------------YANGIN ALARMI---------------------------------------------------
int yangin = digitalRead(yanginpin);
  if(yangin==HIGH){
    digitalWrite(zil,HIGH);
  }else{
    digitalWrite(zil,LOW);
  }
//-------------------------------------------HAREKET SENSÖRÜ-------------------------------------------------
  deger = digitalRead(pin);
    if(deger == HIGH) {
      digitalWrite(lamba,HIGH);
        if(harekets == LOW){
          harekets = HIGH;
        }
      
    }else{
      digitalWrite(lamba,LOW);
        if(harekets == HIGH){
          harekets = LOW;
        }
    }
//-------------------------------------------KEYPAD----------------------------------------------------------
  char basilantus = klavye.getKey();
    if(basilantus != NO_KEY){
      Serial.print(basilantus);
       sifregirilen[say] = basilantus;
       say++;
        if(basilantus == '#'){
          Serial.println();
          say = 0; 
        }
    }
 digitalWrite(redled,LOW);
 digitalWrite(greenled,LOW);
  if(say==4){
    if(strcmp(sifre, sifregirilen)==0){
      digitalWrite(greenled,HIGH);
      digitalWrite(redled,LOW);
      
    }else{

      digitalWrite(redled,HIGH);
      digitalWrite(greenled,LOW);
    }
  }

}
