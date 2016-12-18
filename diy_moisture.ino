
#include <LCD5110_Graph.h> 
LCD5110 lcd(8,9,10,11,12);

extern unsigned char BigNumbers[];
extern uint8_t ui[];

int moisture1=A0;
int moisture2=A1;
int moisture3=A2;
int a=2;
int b=3;
int c=4;
int relay=5;
String percentString ="0";
int stringLength = 0;
int percent = 0;

void setup() {
Serial.begin(9600);
pinMode(relay,OUTPUT);
pinMode(moisture1,INPUT);
pinMode(moisture2,INPUT);
pinMode(moisture3,INPUT);
pinMode(a,OUTPUT);
pinMode(b,OUTPUT);
pinMode(c,OUTPUT);
lcd.InitLCD();
lcd.setFont(BigNumbers);
delay(1000);
}

void loop() {
lcd.clrScr();
lcd.drawBitmap(0, 0, ui, 84, 48);
digitalWrite(a,HIGH);
digitalWrite(b,HIGH);
digitalWrite(c,HIGH);
int pok1=analogRead(moisture1);
int pok2=analogRead(moisture2);
int pok3=analogRead(moisture3);
int avg=((pok1+pok2+pok3)/3);
if(percent>60) digitalWrite(relay,HIGH);
if(percent<40) digitalWrite(relay,LOW);
percent = convertToPercent(avg);
percentString = String(percent);
stringLength = percentString.length();
displayPercent(stringLength);
lcd.update();
Serial.println(avg);
delay(300); 
}

int convertToPercent(int value)
{
  int percentValue = 0;
  percentValue = map(value, 1020 ,350 , 0, 100);
  if(percentValue>100)
    percentValue = 100;
  return percentValue;
}

void displayPercent(int length)
{
  switch(length)
  {
    case 1:  lcd.print(percentString,38,19); break;
    case 2:  lcd.print(percentString,24,19); break;
    case 3:  lcd.print(percentString,10,19); break;
    default:  lcd.print(percentString,0,19); break;
  }
}
