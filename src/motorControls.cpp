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
	#if(defined(__AVR_ATmega2560__))
	pwm_1 = MOTOR1_EN;
	pwm_2 = MOTOR2_EN;
    dir1_m1 = MOTOR1_D1;
    dir2_m1 = MOTOR1_D2;	
    dir1_m2 = MOTOR2_D1;
    dir2_m2 = MOTOR2_D2;	
    #endif
	//Serial.println("default");
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

int motorControls::getpwm_Motor1()
{
	return pwm_Motor1;
}

int motorControls::getpwm_Motor2()
{
	return pwm_Motor2;
}

/*void motorControls::moveMotorClockwise(bool a)
{
if(a == 0 )
{
	pinMode(pwm_1,OUTPUT);
	pinMode(dir1_m1,OUTPUT);
	pinMode(dir2_m1,OUTPUT);
	analogWrite(pwm_1,byte2);
	digitalWrite(dir1_m1, 1);
    digitalWrite(dir2_m1, 0);
}
else if (a==1)
{
	pinMode(pwm_2,OUTPUT);
	pinMode(dir1_m2,OUTPUT);
    pinMode(dir2_m2,OUTPUT);
	analogWrite(pwm_2,byte2);
	digitalWrite(dir1_m2, 1);
    digitalWrite(dir2_m2, 0);
}

}

void motorControls::moveMotorAntiClockwise(bool b)
{
 if(b == 0 )
 {
	pinMode(pwm_1,OUTPUT);
	pinMode(dir1_m1,OUTPUT);
	pinMode(dir2_m1,OUTPUT);
	analogWrite(pwm_1,byte2);
	digitalWrite(dir1_m1, 0);
    digitalWrite(dir2_m1, 1);
 }
 else if (b==1)
 {
	pinMode(pwm_2,OUTPUT);
	pinMode(dir1_m2,OUTPUT);
    pinMode(dir2_m2,OUTPUT);
	analogWrite(pwm_2,byte2);
	digitalWrite(dir1_m2, 0);
    digitalWrite(dir2_m2, 1);
 }
}

void motorControls::stopMotor(bool d)
{
 if(d == 0 )
 {
	pinMode(pwm_1,OUTPUT);
	pinMode(dir1_m1,OUTPUT);
	pinMode(dir2_m1,OUTPUT);
	analogWrite(pwm_1,0);
	digitalWrite(dir1_m1, 0);
    digitalWrite(dir2_m1, 0);
 }
 else if (d == 1)
 {
	pinMode(pwm_2,OUTPUT);
	pinMode(dir1_m2,OUTPUT);
    pinMode(dir2_m2,OUTPUT);
	analogWrite(pwm_2,byte2);
	digitalWrite(dir1_m2, 0);
    digitalWrite(dir2_m2, 0);
 }
}*/

void motorControls::processData()
{
	    Serial.println("Controls:processData");
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
			//servo1.detach();
			//servo2.detach();
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
				//moveMotorAntiClockwise(0);
			}
			else if(byte1 == 0xff)
			{
				pwm_Motor1= -byte2;
				//moveMotorClockwise(0);
			}
			else if(byte1 == 0x0f)
			{
				pwm_Motor1= 0;
				//stopMotor(0);
			}
			else if(byte1 == 0x00)
			{
				pwm_Motor1= 0;
				//stopMotor(0);
			}
			
		}
		
		if(functionId == 0x02)
		{
			if(byte1 == 0xf0)
			{
				pwm_Motor2= byte2;
				//moveMotorAntiClockwise(1);
			}
			else if(byte1 == 0xff)
			{
				pwm_Motor2= -byte2;
			   //moveMotorClockwise(1);
			}
			else if(byte1 == 0x0f)
			{
				pwm_Motor2= 0;
				//stopMotor(1);
			}
			else if(byte1 == 0x00)
			{
				pwm_Motor2= 0;
				//stopMotor(1);
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
void motorControls::runMotor1(int a)
{
	pinMode(pwm_1,OUTPUT);
	pinMode(dir1_m1,OUTPUT);
	pinMode(dir2_m1,OUTPUT);
	Serial.println(a);
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



void motorControls::runMotor2(int b)
{
	pinMode(pwm_2,OUTPUT);
	pinMode(dir1_m2,OUTPUT);
	pinMode(dir2_m2,OUTPUT);
	if(b>0)
	{
		analogWrite(pwm_2,b);
		digitalWrite(dir1_m2,HIGH);
		digitalWrite(dir2_m2,LOW);
	}
	else if(b<0)
	{
		b=-b;
		analogWrite(pwm_2,b);
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
//motorControls Control;