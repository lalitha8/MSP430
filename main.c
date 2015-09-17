#include <msp430.h> 

/*
 * This application initializes the UART on the MSP430F5529
 * and writes Hello world to it.  Baud rate is set to 115200.
 * main.c
 */
void UART_Initialize() {

    UCA0CTL1 |= UCSWRST;
    UCA0CTL0 = UCMODE_0; // UART
    UCA0CTL0 &= ~UC7BIT ; // 8 bits, no parity, 1 stop bit
    UCA0CTL1 |= UCSSEL_2; // Source 1 MHz

    UCA0BR0 = 9; //115200 baud rate
    UCA0BR1 = 0;

    UCA0MCTL |= UCBRS_0 + UCBRF_0; // Modulation
    P3SEL |= BIT3 + BIT4;
    UCA0CTL1 &= ~UCSWRST;
    UCA0IE |= UCRXIE;
}

void UART_print(unsigned char *character) {
	while (*character != '\0') {
		while (!(UCA0IFG & UCTXIFG));
    	UCA0TXBUF = *character++;
	}
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    UCSCTL0 = 0x00;
	UCSCTL1 = DCORSEL_3;
	UCSCTL2 = FLLN5_L;

	P1OUT |= BIT0;					// Configure the LED to flash periodically
	P1DIR |= BIT0;					// Set P1.0 to output direction

	UART_Initialize();
	for(;;) {
		volatile unsigned int i;	// volatile to prevent optimization
		i = pt;
		i = int_n;
		P1OUT ^= BIT0;				// Toggle P1.0 using exclusive-OR

		i = 10000;					// SW Delay
		do i--;
		while(i != 0);
		UART_print("Hello world\n\r");
	}
	return 0;
}

