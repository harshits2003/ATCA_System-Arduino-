#include <Wire.h>
#include<EEPROM.h>
#include <RTClib.h> 
#include <LiquidCrystal.h>
int rs = 12, e = 13, d4 = 4, d5 = 5, d6=6, d7=7; 
LiquidCrystal lcd(rs, e, d4,d5,d6,d7); 
RTC_DS1307 RTC;
int tmp,Inc,hor,mIn,add=11; 
int set=8;  
int cge=9;   
int mod=10; 
int off=0;
#define buz 11 
int Hor,Min,Sec; 
///////////////////////////////////////Function to adjust the time//////////////////////////////////
void time()                             
{
    int tmp=1,mins=0,hors=0,secs=0;
    while(tmp==1)
    {
     off=0;
     if(digitalRead(cge)==0)
     {
      Hor++;
      if(Hor==24)
      {
       Hor=0;
      }
     }
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Set Alarm Time ");

    lcd.setCursor(0,1);
    if(Hor<=9){
      lcd.print("0");
      lcd.print(Hor);
      lcd.print(":");
      lcd.print(Min);
      lcd.print(":");
      lcd.print(Sec);
    }
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("  ");
    lcd.print(":");
    lcd.print(Min);
    lcd.print(":");
    lcd.print(Sec);
    delay(200);
    if(digitalRead(set)==0)
    {
      hor=Hor;
      EEPROM.write(add++,hor);
     tmp=2;
     while(digitalRead(set)==0);
    }
    }
    
    while(tmp==2)
    {
     if(digitalRead(cge)==0)
     {
      Min++;
      if(Min==60)
      {Min=0;}
     }
    lcd.setCursor(0,1);
    lcd.print(Hor);
    lcd.print(":");
    if(Min<=9){
      lcd.print("0");
      lcd.print(Min);
      lcd.print(":");
      lcd.print(Sec);
      lcd.print("  ");
    }
    delay(200);
    lcd.setCursor(0,1);
    lcd.print(Hor);
    lcd.print(":");
    lcd.print("  ");
    lcd.print(":");
    lcd.print(Sec);
    lcd.print("  ");
    delay(200);
      if(digitalRead(set)==0)
      {
       mIn=Min;
       EEPROM.write(add++, mIn);
       tmp=0;
       while(digitalRead(set)==0);
      }
    }
    off=1;
    delay(10);
}
///////////////////////////////////////////function to sound the buzzer//////////////////////////////////
void Buz()
{
  if(digitalRead(set)==0)
  off=0;
  if(off==1)
  {
   digitalWrite(buz,HIGH);
   delay(300);
  
   digitalWrite(buz, LOW);
   delay(300);
  }
}
//////////////////////////////////////////function to compare the alarm time with current RTC time//////////////////
void TimeCheck()
{
  int tem[17];
  for(int i=11;i<17;i++)
  {
    tem[i]=EEPROM.read(i);
  }
  if(Hor == tem[11] && Min == tem[12] && off==1) 
  {
   add=11;
   Buz();
   Buz();
   lcd.clear();
   lcd.print("alarm.........");
   lcd.setCursor(0,1);
   lcd.print(".........alarm");
   Buz();
   Buz();
    }
}
////////////////////////////////////////////////////////////setup///////////////////////////
void setup()
{
 Serial.begin(9600);

 Wire.begin();
 RTC.begin();
 lcd.begin(16,2);
 pinMode(cge, INPUT);
 pinMode(set, INPUT);
 pinMode(mod, INPUT);
 pinMode(buz, OUTPUT);
 digitalWrite(set, HIGH);
 digitalWrite(mod, HIGH);
 digitalWrite(cge, HIGH);
 
  lcd.setCursor(0,0);
  lcd.print("ATCA System");
  lcd.setCursor(0,1);
  lcd.print("ECE-B  ");
  delay(2000);
    
 if(!RTC.isrunning())
 {
 RTC.adjust(DateTime(__DATE__,__TIME__));
 }
}
////////////////////////////////////////////////////////////loop/////////////////////////////////////
void loop()
{
    
  delay(1000);
   DateTime now = RTC.now();
   if(digitalRead(mod) == 0)      
   { 
    current();
    time();
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  Alarm On");
    delay(2000);
   }
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Time:");
 lcd.setCursor(6,0);
 Hor=now.hour(),DEC; 
 if(Hor<=9)
 {
  lcd.print("0");
  lcd.print(Hor=now.hour(),DEC);
 }
 else
 lcd.print(Hor=now.hour(),DEC);
 lcd.print(":");
 Min=now.minute(),DEC;
 if(Min<=9)
 {
 lcd.print("0");
 lcd.print(Min=now.minute(),DEC);
 }
 else
 lcd.print(Min=now.minute(),DEC);
 
 lcd.print(":");
 Sec=now.second(),DEC;
 if(Sec<=9)
 {
  lcd.print("0");
  lcd.print(Sec=now.second(),DEC);
 }
 else
 lcd.print(Sec=now.second(),DEC);
 lcd.setCursor(0,1);
 lcd.print("Date: ");
 lcd.print(now.day(),DEC);
 lcd.print("/");
 lcd.print(now.month(),DEC);
 lcd.print("/");
 lcd.print(now.year(),DEC);
 TimeCheck();
 delay(200);
}
///////////////////////////////////////////////////////function to get current RTC time//////////////////////////////
void current()
{
  lcd.setCursor(0,1);
  lcd.print(Hor);
  lcd.print(":");
  lcd.print(Min);
  lcd.print(":");
  lcd.print(Sec);
}
