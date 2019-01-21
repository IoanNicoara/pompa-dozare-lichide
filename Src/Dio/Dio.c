/**
 * Project:    
 * \file:      Dio.c
 * \author:    Nicoara Ioan
 * \brief:     Implementation file for the DIO driver.
 * \ingroup:   
 *
 * Copyright (c) Nicoara Ioan
 */



/*----------------------------------------------------------------------------*/
/*                                Include files                               */
/*----------------------------------------------------------------------------*/

#include "Dio.h"


/*----------------------------------------------------------------------------*/
/*                     Module local defines and constants                     */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Module local types                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Global data at RAM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Global data at ROM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                            Global data at EEPROM                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                              Local data at RAM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                              Local data at ROM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                            Local data at EEPROM                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                       Declaration of local functions                       */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/

void DIO_vInit(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();	//enable clock for GPIOA
	__HAL_RCC_GPIOB_CLK_ENABLE();	//enable clock for GPIOB

}

/**
 * \brief      This is main function from DIO module.
 * \param      -
 * \return     -
 * \pre        -
 * \post       -
 */
void DIO_vMain(void)
{

}


/**
 * \brief      Write a single DIO channel in PORTA
 * \param      pin : represents no of pin from PORTA
 * 			   state : represents logic state of the pin: STD_HIGH or STD_LOW
 * \return     -
 * \pre        -
 * \post       -
 */
void DIO_vSetDigitalPin_A(Dio_PinNo pin, Dio_LevelType state)
{
	if((pin < 0u) || (pin > NO_OF_PINS))
		{
			return;
		}
		else
		{
			GPIOA->MODER |= ((0x00000000u | (1 << (pin*2u)))) ; // 00: input mode  01: output mode  10: AF  11: analog mode
			GPIOA->OTYPER = 0x0000u;	// 0: output push-pull	1:output open-drain
	    	GPIOA->OSPEEDR |= ((0x00000000u | (1 << (pin*2u))));	// x0: low speed	01: mediu speed 	11: high speed
			GPIOA->PUPDR |= ((0x00000000u | (1 << (pin*2u)))) ;	// 00: no pull up/down 	01: pull-up 	10: pull-down

			if(state == STD_HIGH)
			{
				GPIOA->BSRR |= ((0x00000000u) | (1u << pin));	// set "1" - STD_HIGH
			}
			else if(state == STD_LOW)
			{
				GPIOA->BRR |= ((0x0000u) | (1u << pin));		// set "0" - STD_LOW
			}
		}
}

/**
 * \brief      Write a single DIO channel in PORTB
 * \param      pin : represents no of pin from PORTB
 * 			   state : represents logic state of the pin: STD_HIGH or STD_LOW
 * \return     -
 * \pre        -
 * \post       -
 */
void DIO_vSetDigitalPin_B(Dio_PinNo pin, Dio_LevelType state)
{
	if((pin < 0u) || (pin > NO_OF_PINS))
	{
		return;
	}
	else
	{

		GPIOB->MODER |= ((0x00000000u | (1u << (pin*2u)))) ;
		GPIOB->OTYPER = 0x0000u;
    	GPIOB->OSPEEDR |= ((0x00000000u | (1u << (pin*2u)))) ;
		GPIOB->PUPDR |= ((0x00000000u | (1u << (pin*2u)))) ;

		if(state == STD_HIGH)
		{
			GPIOB->BSRR |= (0x00000000u | (1u << pin));
		}
		else if(state == STD_LOW)
		{
			GPIOB->BRR |= ((0x0000u) | (1u << pin));
		}
	}
}


/**
 * \brief      Read a single DIO channel from PORTA
 * \param      -
 * \return     State of the pin (STD_HIGH or STD_LOW)
 * \pre        -
 * \post       -
 */
uint8_t DIO_vReadStatePin_A(Dio_PinNo pin)
{
	uint8_t state = 0;
	if((pin < 0u) || (pin > NO_OF_PINS))
		{

		}
	else
	{
		GPIOA->MODER |= ~((0xFFFFFFFFu | (3u << (pin*2u)))); // set pin as input
		GPIOA->PUPDR |= ((0x00000000u | (1u << (pin*2u))));  // pull up
		if((GPIOA->IDR & (1u << (pin))))
		{
			state = 0u;	// change to 1 for invert polarity
		}
		else
		{
			state = 1u;	// change to 0 for invert polarity
		}

	}
	return state;
}


/**
 * \brief      Read a single DIO channel from PORTB
 * \param      -
 * \return     State of the pin (STD_HIGH or STD_LOW)
 * \pre        -
 * \post       -
 */
uint8_t DIO_vReadStatePin_B(Dio_PinNo pin)
{
	uint8_t state = 0;
	if((pin < 0u) || (pin > NO_OF_PINS))
	{
		state = 0u;
	}
	else
	{
		GPIOB->MODER |= ~((0xFFFFFFFFu | (3u << (pin*2u)))) ;
		GPIOB->PUPDR |= ((0x00000000u | (1u << (pin*2u)))) ; //pull up
		if((GPIOB->IDR & (1 << (pin))))
		{
			state = 0u; // change to 1 for invert polarity
		}
		else
		{
			state = 1u;	// change to 0 for invert polarity
		}
	}
	return state;
}


/*----------------------------------------------------------------------------*/
/*                      Implementation of local functions                     */
/*----------------------------------------------------------------------------*/
