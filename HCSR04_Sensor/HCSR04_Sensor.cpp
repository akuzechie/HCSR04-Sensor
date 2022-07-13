//---------------------------------------------------
// HCSR04_Sensor.cpp - Source File
// Library for Programming HC-SR04 Ultrasonic Sensor
// by: Anas Kuzechie (June, 2022)
//---------------------------------------------------
#include <Arduino.h>
#include <HCSR04_Sensor.h>
//========================================================================
// Function Prototypes
//========================================================================
extern "C"
{
  /*function prototypes written in assembly (see S file)*/
  void set_EchoPin();         /*set Echo pin for input*/
  void echoPW_rising();       /*Timer 1 capture rising of ECHO pulse*/
  void echoPW_falling();      /*Timer 1 capture falling of ECHO pulse*/
  void timer1_clr_flag();     /*reset Timer 1*/
  void delay_timer0();        /*10us delay via Timer 0*/
  void delay_1s();            /*1s delay*/
}
//========================================================================
// Constructor
//========================================================================
HCSR04_Sensor::HCSR04_Sensor(byte TrigPin)
{
  _TrigPin = TrigPin;
}
//========================================================================
// Public Method
//========================================================================
void HCSR04_Sensor::setEchoPin()
{
  pinMode(_TrigPin, OUTPUT);  /*set Trig pin for output*/
  set_EchoPin();              /*set Echo pin for input*/
}
//========================================================================
float HCSR04_Sensor::getDistance()
{
  float dist;
  do
  {
    digitalWrite(_TrigPin, HIGH);
    delay_timer0();
    digitalWrite(_TrigPin, LOW);/*send 10us high pulse to sensor*/
    //-------------------------------------------------------------------
    echoPW_rising();            /*Timer 1 capture rising of ECHO pulse*/
    byte c1L = ICR1L;           /*store 1st captured low byte count*/
    byte c1H = ICR1H;           /*store 1st captured high byte count*/
    //-------------------------------------------------------------------
    timer1_clr_flag();          /*clear Timer 1 to detect falling edge*/
    //-------------------------------------------------------------------
    echoPW_falling();           /*Timer 1 capture falling of ECHO pulse*/
    byte c2L = ICR1L;           /*store 2nd captured low byte count*/
    byte c2H = ICR1H;           /*store 2nd captured high byte count*/
    //-------------------------------------------------------------------
    timer1_clr_flag();          /*clear Timer 1 for next rising edge*/
    //-------------------------------------------------------------------
    unsigned int c1 = (c1H<<8) | c1L; /*generate 16-bit of 1st count*/
    unsigned int c2 = (c2H<<8) | c2L; /*generate 16-bit of 2nd count*/
    //-------------------------------------------------------------------
    dist = (float((c2-c1))/2.0)*2.19;   /*compute distance in cm*/
  }
  while(dist < 0 || dist > 99); /*ignore distance if value out of range*/
  delay_1s();
  return dist;
}