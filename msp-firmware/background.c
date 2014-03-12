#include <msp430afe251.h>
#pragma vector=USART0RX_VECTOR
__interrupt void USART0_RX (void)
{
	while (!(IFG1 & UTXIFG0));                // USART0 TX buffer ready?
	TXBUF0 = RXBUF0;                          // RXBUF0 to TXBUF0
}
