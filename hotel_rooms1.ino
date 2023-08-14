#include <LiquidCrystal.h>
LiquidCrystal lcd(5,6,8,10,11,12);

const int MOTOR=9;
const int TMP=0;
const int LED=2;
const int PIR=3;

int tempval=0;
int motionval=0;

float celsius(float tempval) {
  float voltage = 0;
  float celsius = 0;
  voltage=(tempval/1024)*5;
  celsius = (voltage-0.5)*100;
  return celsius;
}

void setup()
{
  pinMode(MOTOR,OUTPUT);
  pinMode(TMP,INPUT);
  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop()
{
  float tempval1=analogRead(TMP);
  float current_temp = celsius(tempval1);
  tempval=analogRead(TMP);
  Serial.println(tempval);
  tempval=map(tempval,0,1023,0,255);
  tempval=constrain(tempval,0,255);
  motionval = digitalRead(PIR);
  if (motionval == HIGH)
  {
    if (tempval1 > 145)
    {
      analogWrite(MOTOR,tempval);
    }
    else
    {
      analogWrite(MOTOR,0);
    }
    digitalWrite(LED, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Welcome to");
    lcd.setCursor(0,1);
    lcd.print("Frank's Hotel");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Room Temp:");
    lcd.setCursor(0,1);
    lcd.print(current_temp);
    delay(3000);
  }
  else
  {
    analogWrite(MOTOR,0);
    digitalWrite(LED, LOW);
    lcd.clear();
  }
  delay(100);
}