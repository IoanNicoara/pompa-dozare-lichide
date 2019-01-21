

/**
 * \file       Btn_Enc.h
 * \author     Nicoara Ioan
 * \brief      This is file header for Button and Rotative Encoder
 */



/*----------- Headerswitch ON (for prevention of nested includes) ------------*/
#ifndef BTN_ENC_H_
#define BTN_ENC_H_
/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include <machine/_default_types.h>
#include "Dio.h"
/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Defines and macros                             */
/*----------------------------------------------------------------------------*/
#define pGPIOA		0u
#define pGPIOB		1u
#define GPIOx_pinA  0u
#define GPIOx_pinB  1u

/*----------------------------------------------------------------------------*/
/*                                 Data types                                 */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                 External declaration of global RAM-Variables               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                 External declaration of global ROM-Variables               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                  External declaration of global functions                  */
/*----------------------------------------------------------------------------*/
void BtnEnc_vInit(void);
void BtnEnc_vMain(void);
uint16_t BtnEnc_uEncoder(uint8_t GPIOxPinA, uint8_t GPIOxPinB, uint8_t PinA, uint8_t PinB, uint16_t cnt);
uint16_t BtnEnc_uButton(uint8_t pGPIOx, uint8_t Sw_Pin, uint8_t delayCnt);


/*----------------------------- Headerswitch OFF -----------------------------*/
#endif /* BTN_ENC_H_ */
