/**
 * Project:    
 * \file:      Dio.h
 * \author:    Nicoara Ioan
 * \brief:     Header file for the DIO driver.
 * \ingroup:   
 *
 */


/*----------- Headerswitch ON (for prevention of nested includes) ------------*/

#ifndef _DIO_H
#define _DIO_H

/*----------------------------------------------------------------------------*/
/*                                Include files                               */
/*----------------------------------------------------------------------------*/

#include "stm32f302x8.h"

/*----------------------------------------------------------------------------*/
/*                            Defines and constants                           */
/*----------------------------------------------------------------------------*/

#define NO_OF_PINS	(15u)
#define STD_HIGH	(1u)
#define STD_LOW		(0u)

/*----------------------------------------------------------------------------*/
/*                                 Data types                                 */
/*----------------------------------------------------------------------------*/

typedef uint8_t Dio_LevelType;	//STD_HIGH or STD_LOW
typedef uint8_t Dio_PinNo; 	//represents no of pin from port


/*----------------------------------------------------------------------------*/
/*                External declaration of global RAM-Variables                */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                External declaration of global ROM-Variables                */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*               External declaration of global EEPROM-Variables              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                  External declaration of global functions                  */
/*----------------------------------------------------------------------------*/

void DIO_vInit(void);
void DIO_vMain(void);
void DIO_vSetDigitalPin_A(Dio_PinNo pin, Dio_LevelType state);
void DIO_vSetDigitalPin_B(Dio_PinNo pin, Dio_LevelType state);
uint8_t DIO_vReadStatePin_A(Dio_PinNo pin);
uint8_t DIO_vReadStatePin_B(Dio_PinNo pin);

/*----------------------------- Headerswitch OFF -----------------------------*/
#endif /* _DIO_H */
