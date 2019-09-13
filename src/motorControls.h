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
	uint8_t getangle_Servo1();
	uint8_t getangle_Servo2();

	uint8_t getServo1Angle();
	uint8_t getServo2Angle();
	//int   getpwm_Motor1();
	//int   getpwm_Motor2();
	void runMotor1();
    void runMotor2();
	
	//Pictobox
	void runMotor1(uint8_t direction1,uint8_t direction2,uint8_t pwm);
    void runMotor2(uint8_t direction1,uint8_t direction2,uint8_t pwm);
	
	//void defineServopins(uint8_t a);
	//void defineServopins(uint8_t a,uint8_t b);
	//void stopMotor(bool d);
	public:
	 byte byte1;
     byte byte2;
	 //uint8_t servo_1, servo_2;
	uint8_t angle_servo1=0;
    uint8_t angle_servo2=0;
	int pwm_Motor1=0;
	int pwm_Motor2=0;
    byte functionId;

private:	


     void processData();
};


//void runMotor1(int a);
//void runMotor2(int b);


extern motorControls motorControl;

#endif 