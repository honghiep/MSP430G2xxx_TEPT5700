/******************************************************************************
 *
 * WWW.PAYITFORWARD.EDU.VN
 *
 ******************************************************************************/

/******************************************************************************
 *
 * C7 TRAINING
 *
 ******************************************************************************/

/******************************************************************************
 *
 *  Module         : VOLTAGE MESURE
 *  Description    : This file describes API functions that support for
 *    				 ADC module on MSP430G2553
 *
 *  Tool           : CCS 5.1
 *  Chip           : MSP430G2553
 *  History        : 04-11-2012
 *  Version        : 1.1
 *
 *  Author         : NHH
 *  Notes          : To apply these functions, you must include the header file lcd.h and
 *                   source file lcd.c to your project.
 *
 *
******************************************************************************/

/*****************************************************************************
 * Pin Description
******************************************************************************
*
*		                     MSP430G2x53
*                         -----------------
*                     /|\|              XIN|-
*                      | |                 |
*                      --|RST          XOUT|-
*                        |                 |
* Analog signal input >--|P1.1/A1          |--> ||
*                        |                 |-->	|| Out to LCD
*                        |				   |--> || Described in LCD.c
*                        |				   |--> ||
*                        |				   |
*
******************************************************************************/

/*****************************************************************************
 * IMPORT
******************************************************************************/
#include <msp430g2553.h>

/*****************************************************************************
 * DECLARATIONS
******************************************************************************/

#define Vref 3.3	//Define Vcc voltage when select Vref = VCC

unsigned int adc_result;
float volt, Ic, Vi;

/*****************************************************************************
* 						SUBROUTINES
******************************************************************************/

//*****************************************************************************
// Initialization for ADC10 module
//*****************************************************************************
void ADC10_Init(void)
{
	ADC10CTL0 = SREF_0 + ADC10SHT_1 + ADC10ON;
	/*
	 * Vref = VCC
	 * ADC sample and hold time = 8 ADC clocks
	 * Turn on ADC10
	 * Enable ADC10 Interrupt
	 */
	ADC10CTL1 = INCH_0 + ADC10DIV_1 + ADC10SSEL_3;
	/*
	 * Select Input chanel 0
	 * ADC10DF = 0: The 10-bit conversion results are right justified
	 * ADC10 Clock divider: 2
	 * ADC10 clock source select: SMCLK
	 */
	ADC10AE0 |= BIT0;	//Enable analog input on A0 chanel
}

/*****************************************************************************
* 						MAIN PROGRAM
******************************************************************************/
void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;	//Stop Watchdog Timer
	ADC10_Init();				//Initialize ADC10

	while (1)
	{
		ADC10CTL0 |= ENC + ADC10SC;	//Enable ADC10, Start sample - conversion
		while (ADC10CTL1 & ADC10BUSY);
		adc_result = ADC10MEM;
		volt = adc_result * Vref / 1023;
		Vi = volt / 5.7;
		Ic = Vi / 10000;
		_delay_cycles(500000);
	}
}
/*****************************************************************************
* 						END OF MAIN.C
******************************************************************************/
