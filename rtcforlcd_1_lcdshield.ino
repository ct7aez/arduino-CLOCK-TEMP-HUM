// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>
#include "SparkFunHTU21D.h"


RTC_DS1307 rtc;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Create an instance of the object
HTU21D myHumidity;
int resol = 0;

void setup () {
  Serial.begin(57600);
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.print("RTCClk by CT7AEZ");
  lcd.setCursor(0, 1);
  lcd.print("HTU21D****DS1307");
  lcd.noCursor();  
  delay(3000);  
  lcd.clear();


  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));



  }


  myHumidity.begin();

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW); 



}

void loop () {

  DateTime now = rtc.now();
  int dds = now.dayOfWeek(); //Day of the week 0-Dom;1-Seg;2-Ter;3-Qua;4-Qui;5-Sex;6-Sab)

  float humd = myHumidity.readHumidity();
  float temp = myHumidity.readTemperature();

  if (Serial.available() > 0) {

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.print('-');
    //Serial.print(now.dayOfWeek(), DEC);
    Serial.print(dds);  
    Serial.println();

    Serial.print(" Temperatura:");
    Serial.print(temp, resol);
    Serial.print("C");
    Serial.print(" Humidade:");
    Serial.print(humd, resol);
    Serial.print("%");
    Serial.println();

  }

  lcd.setCursor(1,0);
  lcd.print(now.year(), DEC);
  lcd.print('-');

  if (now.month() < 10) {
    lcd.print("0");

  }

  lcd.print(now.month(), DEC);
  lcd.print('-');

  if (now.day() < 10) {
    lcd.print("0");

  }

  lcd.print(now.day(), DEC);


  lcd.setCursor(12,0);


  //these are in PT_pt, "Dom" is Sunday
  switch(dds) {

  case 0:
    lcd.print("Dom");
    break;

  case 1:
    lcd.print("Seg");
    break;

  case 2:
    lcd.print("Ter");
    break;

  case 3:
    lcd.print("Qua");
    break;

  case 4:
    lcd.print("Qui");
    break;

  case 5:
    lcd.print("Sex");
    break;

  case 6:
    lcd.print("Sab");
    break;

  }


  //lcd.print(' ');

  lcd.setCursor(0,1);

  if (now.hour() < 10) {
    lcd.print("0");

  }    

  lcd.print(now.hour(), DEC);
  lcd.print(':');

  if (now.minute() < 10) {
    lcd.print("0");

  }

  lcd.print(now.minute(), DEC);
  lcd.print(':');

  if (now.second() < 10) {
    lcd.print("0");
  }    

  lcd.print(now.second(), DEC);

  lcd.print(' ');

  lcd.print(temp, resol);
  lcd.print("C");

  lcd.print(' ');

  lcd.print(humd, resol);
  lcd.print("%");


  delay(1000);

}


