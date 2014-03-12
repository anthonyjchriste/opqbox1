/*
 * init_clock.c
 *
 *  Created on: Feb 26, 2014
 *      Author: tusk
 */

#include <msp430afe251.h>

#include "setup.h"
void setupClock()
{
	volatile unsigned int i=0;
	BCSCTL1 &= ~XT2OFF;                       // Activate XT2 high freq xtal
	//BCSCTL1 &= ~XTS;						  //High frequency mode

	BCSCTL3 |= XT2S_2+LFXT1S_2;               // 12MHz crystal or resonator
	do
	{
		IFG1 &= ~OFIFG;                         // Clear OSCFault flags
		for (i = 0xFFF; i > 0; i--);            // Time for flag to set
	}
	while (IFG1 & OFIFG);                     // OSCFault flag still set?
	BCSCTL2 |= SELS+SELM_2;                   // MCLK = XT2 HF XTAL (safe)
}

void setupUart()
{
	/////////////init usart as uart mode////////////////
	P1SEL |= BIT3+BIT4;                       // P1.3,1.4 = USART0 TXD/RXD
	U0CTL = CHAR;		// 8-bit, UART
	U0TCTL = SSEL1 + SSEL0;
	ME1 |= UTXE0 + URXE0;	// Module enable

	UBR00=0x68;
	UBR10=0x00;
	UMCTL0=0x04;

	UCTL0 &= ~SWRST;			// Enable usart
	IE1 |= URXIE0;              // Enable USART0 RX interrupt

	P1SEL2 |= BIT0;                           // Set SMCLK at P1.0

	_BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt


}
