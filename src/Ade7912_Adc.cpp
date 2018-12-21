/*
 * Adc_Ade7912.cpp is the library with functions to use sensing probes in evive, namely Probe V and Probe I/V
 * evive has 24bit presision sensing ADC: ADE7912
 *
 * Created on: May 27, 2016
 * Author: Dhrupal R Shah
 * Sensing with ADE7912
 * Library based on codes of Art of Circuits
 * Edited by evive team, https://evive.cc Agilo Research
 * or Dhrupal R Shah and Akshat Agarwal
 * Edited on 20170102
 * Contact: support@evive.cc
 * Target Board: evive
 * Copyright (C) 2018, Agilo Research
 *
 * How to use:
 * Read well documented tutorial on how to use evive sensing here: 
 * Function List:
 * 1) ade791x_init() : initialize the ADE7912 IC to communicate over SPI communication with microcontroller ATmega2560
 * 2) long ade791x_read_v1() : returns the voltage sensed between the Probe V and COM (or on the Graph port between the Right Pin and Center Pin (COM))
 * 3) long ade791x_read_vim() : returns the voltage sensed between the Probe I/V and COM (or on the Graph port between the Left Pin and Center Pin (COM))
 * 4) long ade791x_read_im(): NOTE: Put the JP2 Jumper of I or V (Blue) on the I side for sensing current. This function returns the current sensed 
 *		between the Probe I/V and COM (or on the Graph port between the Right Pin and Center Pin (COM))
 *
 * Note: Converting to class-library format was tried, but 1 channel of evive oscillocope functioning was not correct.
 * NOTE: Screen Implementation for mini oscilloscope feature is done in SCREEN_IMPLEMENTATION_H
 */

#include "Ade7912_Adc.h"

/*---------ADE MACROS/VAR//start----------*/

// Include the SPI library:
#include <SPI.h>

#define SPI_ADC_SS 35    // SPI ADC SS for evive
#define ADC_RDY 32      // ADC Ready pin for evive
#define ADC_SPIMaxSpeed 8000000
#define ADC_SPIMode SPI_MODE3
#define ADC_SPIDataOrder MSBFIRST

// Command Definitions
#define ADE791X_READ    0x04
#define ADE791X_WRITE   0x00

// Register Definitions
#define ADE791X_REG_ADC_CRC        0x04    /* CRC value of IWV, V1WV, and V2WV registers. See the ADC Output Values CRC section for details */
#define ADE791X_REG_CTRL_CRC       0x05    /* CRC value of configuration registers. See the CRC of Configuration Registers  for details. */

#define ADE791X_REG_CNT_SNAPSHOT   0x07    /* Snapshot value of the counter used in synchronization operation. */
#define ADE791X_REG_CONFIG         0x08    /* Configuration register. See Table 15 for details */
#define ADE791X_REG_STATUS0        0x09    /* Status register */
#define ADE791X_REG_LOCK           0x0A    /* Memory protection register */
#define ADE791X_REG_SYNC_SNAP      0x0B    /* Synchronization register */
#define ADE791X_REG_COUNTER0       0x0C    /* Contains the least significant eight bits of the internal synchronization counter */
#define ADE791X_REG_COUNTER1       0x0D    /* COUNTER1[3:0] bits contain the most significant four bits of the internal synchronization counter */
#define ADE791X_REG_EMI_CTRL       0x0E    /* EMI control register. */
#define ADE791X_REG_STATUS1        0x0F    /* Status register */

#define ADE791X_REG_TEMPOS         0x18    /* Temperature sensor offset */

/* configuration register constants */
#define CLKOUT_EN                  0x01
#define PWRDWN_EN                  0x04    /* Shuts down the dc-to-dc converter. When PWRDWN_EN = 0, the default value, the */
#define TEMP_EN                    0x08    /* This bit selects the second voltage channel measurement. */
#define ADC_FREQ_8KHZ              0x00    /* These bits select the ADC output frequency to 8khz. */
#define ADC_FREQ_4KHZ              0x10    /* These bits select the ADC output frequency.4khz */
#define ADC_FREQ_2KHZ              0x20    /* These bits select the ADC output frequency.2khz */
#define ADC_FREQ_1KHZ              0x30    /* These bits select the ADC output frequency.1khz */
#define SWRST                      0x40    /* When this bit is set to 1, a software reset is initiated. This bit clears itself to 0 after */
#define BW                         0x80    /* Selects the bandwidth of the digital low-pass filter of the ADC. When BW = 0, the */

/*Status0 registers (address 0x9*/
#define RESET_ON                  0x00
#define CRC_STAT                  0x01
#define IC_PROT                   0x02

/* lock register constants(address 0xA */
#define LOCKED                    0xCA    /*locks configuration register writing */
#define UNLOCKED                  0x9C    /*unlocks configuration register writing */

SPISettings ADCSetup(ADC_SPIMaxSpeed,ADC_SPIDataOrder,ADC_SPIMode);
/*---------ADE MACROS/VAR//end----------*/

/*---------ADE functions//start-------*/

void initialize_ade791x(void)
{
  pinMode(SPI_ADC_SS, OUTPUT);
  pinMode(ADC_RDY, INPUT);
  // take the SS pin high to de-select the chip:
  digitalWrite(SPI_ADC_SS, HIGH);
  // initialize SPI:
  SPI.begin();
//	delay(1);
//  delayMicroseconds(16);
//	SPI.setClockDivider(SPI_ADC_SS, 64);  // default is 4MHz clock
//  SPI.setBitOrder(MSBFIRST);        // default is MSBFIRST
//  SPI.setDataMode(SPI_MODE3);       // ADE791x chip uses SPI_MODE3
//  ade791x_write(ADE791X_REG_LOCK,UNLOCKED);
//  ade791x_write(ADE791X_REG_CONFIG, ADC_FREQ_4KHZ | TEMP_EN);  // configures adc sampling frequency and enables temperature on V2WV register
}

long readv1(void)
{
	//unsigned long st = micros();
  unsigned char addr = ADE791X_REG_V1WV;
  long value = 0;  // stores value to return
  long tempValue1 = 0, tempValue2 = 0 ;//, tempValue3 = 0;
  unsigned char opcode; // stores opcode

  addr = addr << 3;  // left shift address by 3 bits
  opcode = (addr | ADE791X_READ);     // forms opcode byte
	
	#ifdef __DEBUG__
   Serial.print ("opcode: ");    // for debug only
   Serial.println(opcode, BIN);  // for debug only
  #endif
	
  SPI.beginTransaction(ADCSetup);
  // take the SS pin low to select the chip:
	PORTC &= 0b11111011;
  SPI.transfer(opcode);        // send out opcode
//  value  = SPI.transfer(0xFF) * 0x10000;  // read MS Byte
//  tempValue1=value;
//  value |= SPI.transfer(0xFF) * 0x100;  // read mid Byte
//  tempValue2=value;
//  value |= SPI.transfer(0xFF);  // LS Byte

  tempValue1 = SPI.transfer(0xFF);  // read MS Byte
  tempValue2 = SPI.transfer(0xFF);  // read mid Byte
  value = SPI.transfer(0xFF);  // LS Byte

  // take the SS pin high to de-select the chip:
  PORTC |= 0b00000100;
  SPI.endTransaction();

//  tempValue1  = tempValue1 * 0x10000;
//  tempValue2 = tempValue1 | tempValue2 * 0x100;
//  value = tempValue2 | tempValue3;

//  value = value <<8;        // sign extends value to 32 bit
//  value = value / 0x100;    // converts back value to 24 bit but now sign extended

  value = (((tempValue1 <<16)|(tempValue2 <<8)|value)<<8)/ 0x100;
  value = (value - ADE791X_OFFSET_V1WV)*ADE791X_MUL_V1WV; //ADE791X_MUL_V1WV;

  #ifdef __DEBUG__
		Serial.print (F("V1: "));
		Serial.println (value);
  #endif
        Serial.print (F("V1: "));
		Serial.println (value);
  return value;
  
}

long readvim(void)
{
  unsigned char addr = ADE791X_REG_IWV;
  long value = 0;  // stores value to return
  long tempValue1 = 0, tempValue2 = 0; // , tempValue3 = 0;
  unsigned char opcode; // stores opcode

  addr = addr << 3;  // left shift address by 3 bits
  opcode = (addr | ADE791X_READ);     // forms opcode byte
	
  #ifdef __DEBUG__
		Serial.print ("opcode: ");    // for debug only
		Serial.println(opcode, BIN);  // for debug only
  #endif
  SPI.beginTransaction(ADCSetup);
  // take the SS pin low to select the chip:
 	PORTC &= 0b11111011;
  SPI.transfer(opcode);        // send out opcode
//  value  = SPI.transfer(0xFF) * 0x10000;  // read MS Byte
////  tempValue1=value;
//  value |= SPI.transfer(0xFF) * 0x100;  // read mid Byte
////  tempValue2=value;
//  value |= SPI.transfer(0xFF);  // LS Byte

  tempValue1 = SPI.transfer(0xFF);  // read MS Byte
  tempValue2 = SPI.transfer(0xFF);  // read mid Byte
  value = SPI.transfer(0xFF);  // LS Byte

  // take the SS pin high to de-select the chip:
	PORTC |= 0b00000100;
  SPI.endTransaction();

//  tempValue1  = tempValue1 * 0x10000;
//  tempValue2 = tempValue1 | tempValue2 * 0x100;
//  value = tempValue2 | tempValue3;
//
//	value = value <<8;        // sign extends value to 32 bit
//  value = value / 0x100;    // converts back value to 24 bit but now sign extended

  	value = (((tempValue1 <<16)|(tempValue2 <<8)|value)<<8)/ 0x100;
	value = (value - ADE791X_OFFSET_VIMWV)*ADE791X_MUL_VIMWV; //ADE791X_MUL_V1WV;

  #ifdef __DEBUG__
		Serial.print ("VIM: ");
		Serial.println (value);
  #endif
        Serial.print ("VIM: ");
		Serial.println (value);  
  return value;
}

long readim(void)
{
  unsigned char addr = ADE791X_REG_IWV;
  long value = 0;  // stores value to return
  long tempValue1 = 0, tempValue2 = 0; // , tempValue3 = 0;
  unsigned char opcode; // stores opcode

  addr = addr << 3;  // left shift address by 3 bits
  opcode = (addr | ADE791X_READ);     // forms opcode byte
	#ifdef __DEBUG__
		Serial.print (F("opcode: "));    // for debug only
		Serial.println(opcode, BIN);  // for debug only
	#endif
  SPI.beginTransaction(ADCSetup);
  // take the SS pin low to select the chip:
  	PORTC &= 0b11111011;
  SPI.transfer(opcode);        // send out opcode
//  value  = SPI.transfer(0xFF) * 0x10000;  // read MS Byte
////  tempValue1=value;
//  value |= SPI.transfer(0xFF) * 0x100;  // read mid Byte
////  tempValue2=value;
//  value |= SPI.transfer(0xFF);  // LS Byte

  tempValue1 = SPI.transfer(0xFF);  // read MS Byte
  tempValue2 = SPI.transfer(0xFF);  // read mid Byte
  value = SPI.transfer(0xFF);  // LS Byte

  // take the SS pin high to de-select the chip:
	PORTC |= 0b00000100;
  SPI.endTransaction();

//  tempValue1  = tempValue1 * 0x10000;
//  tempValue2 = tempValue1 | tempValue2 * 0x100;
//  value = tempValue2 | tempValue3;
//
//	value = value <<8;        // sign extends value to 32 bit
//  value = value / 0x100;    // converts back value to 24 bit but now sign extended
  	value = (((tempValue1 <<16)|(tempValue2 <<8)|value)<<8)/ 0x100;
	value = (value - ADE791X_OFFSET_IWV)*ADE791X_MUL_IWV; //ADE791X_MUL_IWV;
	#ifdef __DEBUG__
		Serial.print (F("IM: "));
		Serial.println (value);
	#endif
  return value;
}
/*--------ADE functions//end------------*/
