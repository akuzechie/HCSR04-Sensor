//-----------------------------------------------
// HC-SR04: Distance Displayed on Serial Monitor 
// using HCSR04_Sensor.h Library
// by: Anas Kuzechie (June, 2022)
//-----------------------------------------------
#include <HCSR04_Sensor.h>
//-------------------------
HCSR04_Sensor HCSR04(9); /*Trig connected to any digital pin*/
//============================================================
void setup()
{
  Serial.begin(9600);
  HCSR04.setEchoPin();   /*Echo MUST BE connected to pin D8*/
}
//============================================================
void loop()
{
  float d = HCSR04.getDistance(); /*get distance in cm*/
  //--------------------------------------------------------
  Serial.print("d = ");           /*and display on monitor*/
  Serial.print(d); Serial.println(" cm");
}