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

#ifndef ADC_ADE7912_H_
#define ADC_ADE7912_H_

//#include "evive.h"

#ifndef ADE7911X_REG_IWV
#define ADE791X_REG_IWV            0x00    /* Instantaneous value of Current I. */
#define ADE791X_REG_V1WV           0x01    /* Instantaneous value of Voltage V1 */
#define ADE791X_REG_V2WV           0x02    /* Instantaneous value of Voltage V2 */
//For V1WV 5,320,000 reading = 34.5V  (Multiplier = 0.006485) mV
#define ADE791X_MUL_V1WV           0.006485
//For V2WV 5,320,000Num reading = 6.3315V (Multiplier = 0.0011901) mV
#define ADE791X_MUL_VIMWV          0.0011901
//For IWV 5,320,000 reading = 3.15A (Multiplier = 0.0005921) mA
#define ADE791X_MUL_IWV            0.0005921
#define ADE791X_OFFSET_V1WV          363378      //387161;   //Adjust
#define ADE791X_OFFSET_VIMWV         369226                  //Adjust  
#define ADE791X_OFFSET_IWV           355000			//369226;   //Adjust
#endif

void initialize_ade791x(void);
long readv1(void);
long readvim(void);
long readim(void);

#endif /* ADC_ADE7912_H_ */
