//---------------------------------------------------
// HCSR04_Sensor.h - Header File
// Library for Programming HC-SR04 Ultrasonic Sensor
// by: Anas Kuzechie (June, 2022)
//---------------------------------------------------
//header guards
#ifndef HCSR04_Sensor_h
#define HCSR04_Sensor_h
//-----------------------------------------------------------------------
//class definition
class HCSR04_Sensor
{
    public:
        HCSR04_Sensor(byte TrigPin);
        void setEchoPin();
        float getDistance();
    private:
        byte _TrigPin;
};
//----------------------------------------------------------------------
#endif