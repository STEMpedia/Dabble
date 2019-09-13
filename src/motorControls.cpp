#define FROM_DABBLE_LIBRARY
#include "Dabble.h"
#include "motorControls.h"
/* #include "Servo.h"
Servo servo1;
Servo servo2;
 */

  uint8_t pwm_1,dir1_m1,dir2_m1;
  uint8_t pwm_2,dir1_m2,dir2_m2;
	
motorControls::motorControls() : ModuleParent(CONTROLS_ID)
{
	byte1=0;
	byte2=0;
	#if(defined(__AVR_ATmega2560__))   //default pins of evive
	pwm_1 = MOTOR1_EN;
	pwm_2 = MOTOR2_EN;
    dir1_m1 = MOTOR1_D1;
    dir2_m1 = MOTOR1_D2;	
    dir1_m2 = MOTOR2_D1;
    dir2_m2 = MOTOR2_D2;	
    #endif
}

motorControls::motorControls(uint8_t pwm1, uint8_t dirm1_1, uint8_t dirm1_2) : ModuleParent(CONTROLS_ID)
{
	pwm_1 = pwm1;
    dir1_m1 = dirm1_1;
    dir2_m1 = dirm1_2;	
    /*pinMode(pwm_1,OUTPUT);
	pinMode(dir1_m1,OUTPUT);
	pinMode(dir2_m1,OUTPUT);
	Serial.println("1motor");*/
}

motorControls::motorControls(uint8_t pwm1, uint8_t dirm1_1, uint8_t dirm1_2, uint8_t pwm2, uint8_t dirm2_1, uint8_t dirm2_2) : ModuleParent(CONTROLS_ID)
{
	//Serial.println("TWO motor");
	pwm_1 = pwm1;
	pwm_2 = pwm2;
    dir1_m1 = dirm1_1;
    dir2_m1 = dirm1_2;	
    dir1_m2 = dirm2_1;
    dir2_m2 = dirm2_2;	
   /* pinMode(pwm_1,OUTPUT);
	pinMode(pwm_2,OUTPUT);
	pinMode(dir1_m1,OUTPUT);
	pinMode(dir2_m1,OUTPUT);
	pinMode(dir1_m2,OUTPUT);
    pinMode(dir2_m2,OUTPUT);
    Serial.println("2motor");*/
}

uint8_t motorControls::getangle_Servo1()
{
	return angle_servo1;
}

uint8_t motorControls::getangle_Servo2()
{
	return angle_servo2;
}

uint8_t motorControls::getServo1Angle()
{
	return angle_servo1;
}

uint8_t motorControls::getServo2Angle()
{
	return angle_servo2;
}

/*int motorControls::getpwm_Motor1()
{
	return pwm_Motor1;
}

int motorControls::getpwm_Motor2()
{
	return pwm_Motor2;
}*/

void motorControls::processData()
{
	    #ifdef DEBUG
	    Serial.println("Controls:processData");
		#endif 
		functionId=getDabbleInstance().getFunctionId();
		if(functionId == 0x01 || functionId == 0x02)
		{
			#ifdef DEBUG
			Serial.print("pwm1:");
			Serial.print(pwm_1);
			Serial.print(" dir1m1:");
			Serial.print(dir1_m1);
			Serial.print(" dir2m1:");
			Serial.print(dir2_m1);
			Serial.print(" pwm2:");
			Serial.print(pwm_2);
			Serial.print(" dir1m2:");
			Serial.print(dir1_m2);
			Serial.print(" dir2m2:");
			Serial.println(dir2_m2);
			#endif
			
		byte1=getDabbleInstance().getArgumentData(0)[0]; 
		byte2=getDabbleInstance().getArgumentData(0)[1];
		#ifdef DEBUG
		Serial.print("byte1: ");
		Serial.print(byte1);
		Serial.print("byte2: ");
	    Serial.println(byte2);
		#endif
		if(functionId == 0x01)
		{
			
			if(byte1 == 0xf0)
			{
				pwm_Motor1=byte2;
			}
			else if(byte1 == 0xff)
			{
				pwm_Motor1= -byte2;
			}
			else if(byte1 == 0x0f)
			{
				pwm_Motor1= 0;
			}
			else if(byte1 == 0x00)
			{
				pwm_Motor1= 0;
			}
			
		}
		
		if(functionId == 0x02)
		{
			if(byte1 == 0xf0)
			{
				pwm_Motor2= byte2;
			}
			else if(byte1 == 0xff)
			{
				pwm_Motor2= -byte2;
			}
			else if(byte1 == 0x0f)
			{
				pwm_Motor2= 0;
			}
			else if(byte1 == 0x00)
			{
				pwm_Motor2= 0;
			}
		}
		}
		else if(functionId == 0x03 || functionId == 0x04)
		{
			byte1=getDabbleInstance().getArgumentData(0)[0]; 
			#ifdef DEBUG
			Serial.print("byte1:");
			Serial.println(byte1);
			#endif
			if(functionId == 0x03)
			{
				angle_servo1=byte1;
			}
			else if(functionId == 0x04)
			{
			    angle_servo2=byte1;
			}
		}
		
}

void motorControls::runMotor1()
{
	pinMode(pwm_1,OUTPUT);
	pinMode(dir1_m1,OUTPUT);
	pinMode(dir2_m1,OUTPUT);
	int a = pwm_Motor1;
	if(a>0)
	{
		analogWrite(pwm_1,a);
		digitalWrite(dir1_m1,HIGH);
		digitalWrite(dir2_m1,LOW);
	}
	else if(a<0)
	{
		a=-a;
		analogWrite(pwm_1,a);
		digitalWrite(dir1_m1,LOW);
		digitalWrite(dir2_m1,HIGH);
	}
	else
	{
		analogWrite(pwm_1,0);
		digitalWrite(dir1_m1,LOW);
		digitalWrite(dir2_m1,LOW);
	}
}



void motorControls::runMotor2()
{
	pinMode(pwm_2,OUTPUT);
	pinMode(dir1_m2,OUTPUT);
	pinMode(dir2_m2,OUTPUT);
	int a = pwm_Motor2;
	if(a>0)
	{
		analogWrite(pwm_2,a);
		digitalWrite(dir1_m2,HIGH);
		digitalWrite(dir2_m2,LOW);
	}
	else if(a<0)
	{
		a=-a;
		analogWrite(pwm_2,a);
		digitalWrite(dir1_m2,LOW);
		digitalWrite(dir2_m2,HIGH);
	}
	else
	{
		analogWrite(pwm_2,0);
		digitalWrite(dir1_m2,LOW);
		digitalWrite(dir2_m2,LOW);
	}
}

void motorControls::runMotor1(uint8_t direction1,uint8_t direction2,uint8_t pwmPin)
{
	pinMode(pwmPin,OUTPUT);
	pinMode(direction1,OUTPUT);
	pinMode(direction2,OUTPUT);
	int a = pwm_Motor1;
	if(a>0)
	{
		analogWrite(pwmPin,a);
		digitalWrite(direction1,HIGH);
		digitalWrite(direction2,LOW);
	}
	else if(a<0)
	{
		a=-a;
		analogWrite(pwmPin,a);
		digitalWrite(direction1,LOW);
		digitalWrite(direction2,HIGH);
	}
	else
	{
		analogWrite(pwmPin,0);
		digitalWrite(direction1,LOW);
		digitalWrite(direction2,LOW);
	}
}

void motorControls::runMotor2(uint8_t direction1,uint8_t direction2,uint8_t pwmPin)
{
	pinMode(pwmPin,OUTPUT);
	pinMode(direction1,OUTPUT);
	pinMode(direction2,OUTPUT);
	int a = pwm_Motor2;
	if(a>0)
	{
		analogWrite(pwmPin,a);
		digitalWrite(direction1,HIGH);
		digitalWrite(direction2,LOW);
	}
	else if(a<0)
	{
		a=-a;
		analogWrite(pwmPin,a);
		digitalWrite(direction1,LOW);
		digitalWrite(direction2,HIGH);
	}
	else
	{
		analogWrite(pwmPin,0);
		digitalWrite(direction1,LOW);
		digitalWrite(direction2,LOW);
	}
}
//motorControls Control; 
