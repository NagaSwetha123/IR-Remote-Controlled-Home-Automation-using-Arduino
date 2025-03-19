#include<LiquidCrystal.h>
#include <IRremote.h>
const int RECV_PIN=14;
IRrecv irrecv(RECV_PIN);
decode_results results;
#include<LiquidCrystal.h>
LiquidCrystal lcd(6,7,8,9,10,11);
#define Fan 3
#define Light 4
#define TV 5
int i=0,j=0,k=0,n=0;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(Fan, OUTPUT);
  pinMode(Light, OUTPUT);
  pinMode(TV, OUTPUT);
  //digitalWrite(13,HIGH);
  lcd.print("Remote Controlled");
  lcd.setCursor(0,1);
  lcd.print("Home Automation");
  delay(2000);
  lcd.clear();
  lcd.print("Circuit Digest");
  lcd.setCursor(0,1);
  delay(1000);
  lcd.print("System Ready...");
  delay(1000);
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Fan   Light  TV ");
  lcd.setCursor(0,1);
  lcd.print("OFF    OFF   OFF");
}
void loop() 
{
  if (irrecv.decode(&results)) 
   {
     Serial.println(results.value,HEX);
     delay(100);
     lcd.setCursor(0,0);
     lcd.print("Fan   Light  TV"); 
     if(results.value==0x1FE00FF)
     {
        i++;
        int x=i%2;
        digitalWrite(Fan, x);
        lcd.setCursor(0,1);
        if(x)
        lcd.print("ON  ");
        else
        lcd.print("OFF ");
       // delay(200);
     }
     else if(results.value==0x1FEF00F)    //  key 1 
     {
        j++;
        int x=j%2;
        digitalWrite(Light, x);
        lcd.setCursor(6,1);
        if(x)
        lcd.print("ON   ");
        else
        lcd.print("OFF  ");
       // delay(200);
     }
     if(results.value==0x1FE9867)
     {
        k++;
        int x=k%2;
        digitalWrite(TV, x);
        lcd.setCursor(13,1);
        if(x)
        lcd.print("ON ");
        else
        lcd.print("OFF");
       // delay(200);
       }
        if(results.value==0x1FE48B7)
       {
        n++;
        int x=n%2;
        digitalWrite(TV, x);
        digitalWrite(Fan,x);
        digitalWrite(Light,x);
        lcd.setCursor(0,1);
        if(x)
        lcd.print("ON     ON    ON ");
        else
        lcd.print("OFF    OFF   OFF");
        //delay(200);
       }
     irrecv.resume(); // Receive the next value
     //delay(100);
   }
}
