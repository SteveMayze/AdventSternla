/*
 * GccApplication1.c
 *
 * Created: 17/12/2017 12:01:15
 * Author : Steven
 */ 

 #define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

    unsigned int count = 0;


int main(void)
{

    // This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = 0x00;

    PORTA.DIR |= 1 << 1;


	
    while (1) 
    {
		VPORTA_OUT |= (1 << 1);
		//PORTA.OUT |= (1 << 1);
		// PORTA.OUTTGL = 1 << 1;
		count++;
	    _delay_ms(10);
		VPORTA_OUT &= ~(1 << 1);
		// PORTA.OUT &= ~(1 << 1);
		_delay_ms(10);
	//	count--;
    }
}

