/**
 * \file       LCD.c
 * \author     Nicoara Ioan
 * \brief      In this file is described functionality of the LCD 16X02
 * \ingroup    GrpName
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "LCD.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/

/* Represents the number of characters on the entire display */
#define LCD_NUMBER_OF_CHARACTERS 		(32u)
#define LCD_CHARS_PER_LINE				(16u)
#define LCD_delay_37us() 				HAL_Delay(2);
#define LCD_delay_1600us() 				HAL_Delay(60);
#define LCD_delay_20ms() 				HAL_Delay(20);
#define LSB_MASK 						(0x01u)
#define NIBBLE_SIZE						(4u)


/*----------------------------------------------------------------------------*/
/*                              Local data types                              */
/*----------------------------------------------------------------------------*/
typedef enum
{
	instruction = 0u,
	data		= 1u,
} LCD_RegisterSelectType;

/*----------------------------------------------------------------------------*/
/*                             Global data at RAM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Global data at ROM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Local data at RAM                              */
/*----------------------------------------------------------------------------*/

static LCD_characterType LCD_CharactersOnScreen[' '];
static __uint8_t indexCharacter;

/*----------------------------------------------------------------------------*/
/*                             Local data at ROM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                       Declaration of local functions                       */
/*----------------------------------------------------------------------------*/
/**


/**
 * \brief     This function is used to send the command to the LCD;
 * \param     type - represents the state of the RS pin (LOW: instruction/HIGH: data);
 * \param     cmd - represents the command to be sent;
 * \return    None
 * \pre       -
 * \post      -
 */
void LCD_vSendCmd(LCD_RegisterSelectType type, __uint8_t cmd);

/**
 * \brief     This function is used to send 4 bits at a time to the LCD;
 * \param     cmd - represents the command to be sent;
 * \return    None
 * \pre       -
 * \post      -
 */
void LCD_vSendNibble(__uint8_t cmd);

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/

void LCD_vInit(void)
{
	__uint8_t ucCharIndex;
	indexCharacter = 0u;
	for(ucCharIndex = 0u; ucCharIndex < LCD_NUMBER_OF_CHARACTERS; ucCharIndex++)
	{
		LCD_CharactersOnScreen[ucCharIndex] = ' ';
	}

	/*Set delay for 20ms*/
	HAL_Delay(20);
	/*Set DDRAM adress to 00H*/
	LCD_vSendCmd(instruction, 0x03u);
	HAL_Delay(5);
	/*Config: 4b mode, 2 rows, 5x8*/
	LCD_vSendCmd(instruction, 0x02u);
	/*Config: 4b mode, 2 rows, 5x8*/
	LCD_vSendCmd(instruction, 0x02u);
	/*Config: display ON, cursor OFF, cursor position OFF*/
	LCD_vSendCmd(instruction, 0x0Cu);
	/*Set cursor move direction and specifies display shift*/
	/*Config: I/D(increment/decrement): HIGH; S(Shift Left/Right): LOW */
	LCD_vSendCmd(instruction, 0x06u);
}



/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/

void LCD_vMainFunction(void)
{
    __uint8_t location = 0u;
	static __uint8_t flag = 1u;

	if(flag == 1u)
	{
		/*Sets the starting position for the first line*/
		location = indexCharacter | 0x80;
		LCD_vSendCmd(instruction,location);
		flag=0;
	}
	else if(flag == 2u)
	{
		/*Sets the starting position for the second line*/
		location = (indexCharacter + 0x30) | 0x80;
		LCD_vSendCmd(instruction,location);
		flag = 0u;
	}
	else
	{
		LCD_vSendCmd(data,LCD_CharactersOnScreen[indexCharacter]);
		if(indexCharacter < LCD_NUMBER_OF_CHARACTERS)
		{
			indexCharacter = indexCharacter + 1;
			if(indexCharacter == LCD_NUMBER_OF_CHARACTERS)
			{
				flag = 1u;
				indexCharacter = 0u;
			}
			else if(indexCharacter == LCD_CHARS_PER_LINE)
			{
				flag = 2u;
			}
			else
			{

			}
		}
	}
}

void LCD_vWriteString(LCD_characterType * StringToBeSent, __uint8_t startingPoint, __uint8_t length)
{
	__uint8_t ucCharIndex;

	if((LCD_NUMBER_OF_CHARACTERS + 1u) > (startingPoint + length))
	{
		for(ucCharIndex = 0u; ucCharIndex < length; ucCharIndex++)
		{
			LCD_CharactersOnScreen[ucCharIndex + startingPoint] = StringToBeSent[ucCharIndex];
		}
	}
	else
	{

	}
}



void LCD_vSendCmd(LCD_RegisterSelectType type, __uint8_t cmd)
{
	if(type == instruction)
	{
		DIO_vSetDigitalPin_A(2, STD_LOW); 				// RS pin	->PA2
	}
	else if(type == data)
	{
		DIO_vSetDigitalPin_A(2,STD_HIGH);				// RS pin	->PA2
	}
	else
	{

	}
	LCD_vSendNibble(cmd >> NIBBLE_SIZE);
	LCD_vSendNibble(cmd & 0x0F);
}

void LCD_vSendNibble(__uint8_t cmd)
{
	DIO_vSetDigitalPin_A(3, STD_HIGH);					// EN pin	->PA3
	/*Sets the pin value for each LSB */
	DIO_vSetDigitalPin_A(4, (cmd & LSB_MASK));			// D4 pin	->PA4
	DIO_vSetDigitalPin_A(5, ((cmd >> 1) & LSB_MASK));	// D5 pin	->PA5
	DIO_vSetDigitalPin_A(6, ((cmd >> 2) & LSB_MASK));	// D6 pin	->PA6
	DIO_vSetDigitalPin_A(7, ((cmd >> 3) & LSB_MASK));	// D7 pin	->PA7
	DIO_vSetDigitalPin_A(3, STD_LOW);					// EN pin	->PA3
}
