 /**
 * \file       7_Seg.c
 * \author     Nicoara Ioan
 * \brief      In this file is described functionality of the 7 Segents Digits
 * \ingroup    GrpName
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "7_Seg.h"

/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/

/* Represents a mask with 0x01 */
#define MASK 0x01u


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

/*----------------------------------------------------------------------------*/
/*                             Local data at ROM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                       Declaration of local functions                       */
/*----------------------------------------------------------------------------*/
/**


/**
 * \brief     This function is used to send bits;
 * \param     cmd - represents the command to be sent;
 * \return    None
 * \pre       -
 * \post      -
 */
void vPortDisplay(__uint8_t cmd);

/**
 * \brief     This function is used to send the bits;
 * \param     chr - represents the command to be sent (the number);
 * \return    None
 * \pre       -
 * \post      -
 */



/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/

void vSEG7_vInit(void)
{

}



/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/

void vSEG7_vMainFunction(void)
{

}

void vPortDisplay(__uint8_t cmd)
{
	DIO_vSetDigitalPin_A(11, (cmd & MASK));//A
	DIO_vSetDigitalPin_A(12, ((cmd>>1) & MASK));//B
	DIO_vSetDigitalPin_B(5, ((cmd>>2) & MASK));//C
	DIO_vSetDigitalPin_B(6, ((cmd>>3) & MASK));//D
	DIO_vSetDigitalPin_B(7, ((cmd>>4) & MASK));//E
	DIO_vSetDigitalPin_B(8, ((cmd>>5) & MASK));//F
	DIO_vSetDigitalPin_B(9, ((cmd>>6) & MASK));//G

}


void vSendDisplay(__uint8_t chr)
{
	uint8_t number[10] ={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};// numbers from 0 to 9
	uint8_t seg_1,seg_0 = 0;

	seg_1 = chr / 10;
	DIO_vSetDigitalPin_A(10, STD_HIGH); //seg_0 ON
	DIO_vSetDigitalPin_A(9, STD_LOW); //seg_1 OFF
	vPortDisplay(number[seg_1]);
	HAL_Delay(8);

	seg_0 = chr % 10;
	DIO_vSetDigitalPin_A(10, STD_LOW); //seg_0 OFF
	DIO_vSetDigitalPin_A(9, STD_HIGH); //seg_1 ON
	vPortDisplay(number[seg_0]);
	HAL_Delay(8);
}
