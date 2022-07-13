//---------------------------------------------
// HC-SR04: Distance Displayed on I2C 1602 LCD 
// using HCSR04_Sensor.h Library
// by: Anas Kuzechie (June, 2022)
//---------------------------------------------
#include <HCSR04_Sensor.h>
#include <LCD_1602_I2C.h>
//-------------------------
HCSR04_Sensor HCSR04(9); /*Trig connected to any digital pin*/
LCD_1602_I2C lcd(0x40);  /*I2C write address: 0x40*/
//============================================================
void setup()
{
  Serial.begin(9600);
  HCSR04.setEchoPin();   /*Echo MUST BE connected to pin D8*/
  lcd.Initialize();      /*initialize I2C 16x2 LCD*/
  delay(1000);
  intro_message();
}
//=============================================================
void loop()
{
  float dist = HCSR04.getDistance(); /*get distance in cm*/
  //-----------------------------------------------------------
  if(dist < 5) object_too_close(); else clr_line2();
  //-----------------------------------------------------------
   lcd.writeChar(0, 0x8A);           /*beginning of 10th line*/
  //-----------------------------------------------------------
  int dist_MSD = int(dist)/10 + 48;
  int dist_LSD = int(dist)%10 + 48;
  int dist_fraction = (dist - int(dist))*10 + 48;
  //-----------------------------------------------------------
  lcd.writeChar(1, dist_MSD);
  lcd.writeChar(1, dist_LSD); lcd.writeChar(1, '.');
  lcd.writeChar(1, dist_fraction);
  //-----------------------------------------------------------
  lcd.writeChar(0, 0x8A);            /*beginning of 10th line*/
}
//=============================================================
void intro_message()
{
  lcd.writeText("----HC-SR04----");
  lcd.writeChar(0, 0xC0);            /*beginning of 2nd line*/
  lcd.writeText("UltrasonicSensor");
  delay(2000);
  lcd.writeChar(0, 0x01);            /*clear LCD*/
  delay(1000);
  lcd.writeChar(0, 0x80);            /*beginning of 1st line*/
  lcd.writeText("distance:     cm");  
}
//=============================================================
void object_too_close()
{
  lcd.writeChar(0, 0xC0);            /*beginning of 2nd line*/
  lcd.writeText("object TOO CLOSE");
}
//=============================================================
void clr_line2()
{
  lcd.writeChar(0, 0xC0);            /*beginning of 2nd line*/
  for(byte i=1; i<=16; i++) lcd.writeChar(1, ' ');
}