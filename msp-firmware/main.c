
#include <msp430.h>
#include <msp430afe251.h>
#include "setup.h"

void main(void)
{
	volatile unsigned int i=0;
	WDTCTL = WDTPW + WDTHOLD;            // Stop watchdog timer. This line of code is needed at the beginning of most MSP430 projects.
	setupClock();
	setupUart();
	for (;;)                                   // This empty for-loop will cause the lines of code within to loop infinitely
	{
	}
}
