#ifndef motorControls_h
#define motorControls_h


#include "ModuleParent.h"
#include "EvivePins.h"



class motorControls : public ModuleParent
{
	
	public:
    motorControls();
	motorControls(uint8_t pwm1, uint8_t dirm1_1, uint8_t dirm1_2);
	motorControls(uint8_t pwm1, uint8_t dirm1_1, uint8_t dirm1_2, uint8_t pwm2, uint8_t dirm2_1, uint8_t dirm2_2);
	//motorControls(uint8_t c);
	
	//void moveMotorClockwise(bool a);
	//void moveMotorAntiClockwise(bool b);
	uint8_t getangle_Servo1();
	uint8_t getangle_Servo2();
	int   getpwm_Motor1();
	int   getpwm_Motor2();
	void runMotor1(int a);
    void runMotor2(int b);

	//void defineServopins(uint8_t a);
	//void defineServopins(uint8_t a,uint8_t b);
	//void stopMotor(bool d);
	public:
	 byte byte1;
     byte byte2;
	 //uint8_t servo_1, servo_2;
	uint8_t angle_servo1=0;
    uint8_t angle_servo2=0;
	int pwm_Motor1;
	int pwm_Motor2;
    byte functionId;

private:	


     void processData();
};


//void runMotor1(int a);
//void runMotor2(int b);


extern motorControls motorControl;

#endif 