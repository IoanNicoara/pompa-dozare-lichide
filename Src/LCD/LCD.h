#ifndef LCD_H_
#define LCD_H_
/**
 * \file       LCD.h
 * \author     Nicoara Ioan
 * \brief      This header provides functions declaration for the LCD 16x2 module
 * \ingroup    GrpName
 *

/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/
#include <machine/_default_types.h>
#include "Dio.h"
/*----------------------------------------------------------------------------*/
/*                             Defines and macros                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                                 Data types                                 */
/*----------------------------------------------------------------------------*/
typedef __uint8_t LCD_characterType;
/*----------------------------------------------------------------------------*/
/*                 External declaration of global RAM-Variables               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                 External declaration of global ROM-Variables               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                  External declaration of global functions                  */
/*----------------------------------------------------------------------------*/
/**
 * \brief     This function initializes the LCD module
 * \param     None
 * \return    None 
 * \pre       -
 * \post      -
 */
 
void LCD_vInit(void);

/**
 * \brief     Cyclic function that is called one of the OS tasks
 * \param     None
 * \return    None 
 * \pre       -
 * \post      -
 */
void LCD_vMainFunction(void);

/**
 * \brief     This function sends a string to the display;
 * \param     StringToBeSent - Is  a pointer to an array representing the string that needs to be sent;
 * \param     startingPoint - Represents the index where the first char of StringToBeSent will be put into the LCD's array;
 * \param     length - Represents the number of characters of StringToBeSent;
 * \return    None 
 * \pre       -
 * \post      -
 */

void LCD_vWriteString(LCD_characterType * StringToBeSent, __uint8_t startingPoint, __uint8_t length);

#endif
