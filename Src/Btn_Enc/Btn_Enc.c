/**
 * Project:
 * \file:      Dio.c
 * \author:    Nicoara Ioan
 * \brief:     Implementation file for the Button and Rotative Encoder driver.
 * \ingroup:
 *
 * Copyright (c) Nicoara Ioan
 */


/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "Btn_Enc.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define CHECKED_STATE	0x01u
/*----------------------------------------------------------------------------*/
/*                              Local data types                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Global data at RAM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Global data at ROM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Local data at RAM                              */
/*----------------------------------------------------------------------------*/
/*for BtnEnc_uButton*/

uint8_t current_state = 0x00u;
uint8_t count = 0x00u;
uint8_t cnt = 0x00u;
uint8_t state_level = 0x00u;

/*for BtnEnc_uEncoder*/
uint8_t presentState = 0x00u;
uint8_t previousState = 0x00u;

/*----------------------------------------------------------------------------*/
/*                             Local data at ROM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                       Declaration of local functions                       */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/

/**
 * \brief      This is init function from Btn_Enc module.
 * \param      -
 * \return     -
 * \pre        -
 * \post       -
 */
void BtnEnc_vInit(void)
{

}

/**
 * \brief      This is main function from Btn_Enc module.
 * \param      -
 * \return     -
 * \pre        -
 * \post       -
 */
void BtnEnc_vMain(void)
{

}

/**
 * \brief      This is Encoder function from Btn_Enc module.
 * \param      - GPIOxPinA - is the PORT no. for PinA (pGPIOA or pGPIOB)
 * \param      - GPIOxPinB - is the PORT no. for PinA (pGPIOA or pGPIOB)
 * \param      - PinA - represents Out A from CLK Pin
 * \param      - PinB - represents Out B from DT Pin
 * \param      - cnt - represents input value
 * \return     - cnt - represents output value
 * \pre        -
 * \post       -
 * \example	   - BtnEnc_uEncoder(pGPIOB, pGPIOA, 14, 0, x);
 * 								(GPIOB, GPIOA, Pin14 from GPIOB, Pin0 from GPIOA, input value)
 */
uint16_t BtnEnc_uEncoder(uint8_t GPIOxPinA, uint8_t GPIOPinB, uint8_t PinA, uint8_t PinB, uint16_t cnt)
{
	if((GPIOxPinA == STD_HIGH) && (GPIOPinB == STD_HIGH))
	{
		PinA = DIO_vReadStatePin_B(PinA);
		PinB = DIO_vReadStatePin_B(PinB);
	}
	else if((GPIOxPinA == STD_HIGH) && (GPIOPinB == STD_LOW))
	{
		PinA = DIO_vReadStatePin_B(PinA);
		PinB = DIO_vReadStatePin_A(PinB);
	}
	else if((GPIOxPinA == STD_LOW) && (GPIOPinB == STD_HIGH))
	{
		PinA = DIO_vReadStatePin_A(PinA);
		PinB = DIO_vReadStatePin_B(PinB);
	}
	else if((GPIOxPinA == STD_LOW) && (GPIOPinB == STD_LOW))
	{
		PinA = DIO_vReadStatePin_A(PinA);
		PinB = DIO_vReadStatePin_A(PinB);
	}
	else
	{
		return 0;
	}


	presentState = PinA;
	if (presentState != previousState)
	{
		if (PinB != presentState)
		{
			cnt++;
		}
		else if((PinB == presentState))
		{
			cnt--;
		}
	}
	previousState = presentState;
	return cnt;
}

/**
 * \brief      This is Button/Switch function from Btn_Enc module.
 * \param      - GPIOx - is the PORT no. (pGPIOA or pGPIOB)
 * \param      - Sw_Pin - is the input Pin
 * \param      - delayCnt - is the length of the moment the button is pressed
 * \return     - level - represents LOW or HIGH level
 * \pre        -
 * \post       -
 */
uint16_t BtnEnc_uButton(uint8_t pGPIOx, uint8_t Sw_Pin, uint8_t delayCnt)
{

	if(STD_LOW == pGPIOx)
	{
		current_state = DIO_vReadStatePin_A(Sw_Pin);	//sets PORTA => GPIOA
	}
	else if(STD_HIGH == pGPIOx)
	{
		current_state = DIO_vReadStatePin_B(Sw_Pin);	//sets PORTB => GPIOB
	}
	else
	{
		return 0;
	}


	if(current_state == CHECKED_STATE)
	{
		count++;
	}
	else if(count > delayCnt)
	{
		state_level = STD_HIGH;
		count = 0u;
	}
	else
	{
		state_level = STD_LOW;
		count = 0u;
	}

	return state_level;
}
/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/
