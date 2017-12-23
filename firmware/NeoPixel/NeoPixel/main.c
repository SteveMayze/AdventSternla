/*
 * NewPixel.c
 *
 * Created: 19/12/2017 14:59:51
 * Author : Steven
 */ 

#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "neopixel.h"



int main(void)
{

    // This register is protected and can not be changed until the CPP register in the CPU
    // is written with the signature of 0xD8 ... I think I need to insert some assembly code here
    // This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
    // This needs to be checked for the electrical characteristics is such that the full 5V is required.

    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.MCLKCTRLB = 0x02;

    PORTA.DIR |= 1 << 1;
/*
        for (int i = 0; i < neopixel_pixels; i++)
        {
	        neopixel_setPixel(i, 0xFF, 0xFF, 0xFF);
        }
*/
	while(1)
	{
        for (int i = 0; i < neopixel_pixels; i++)
        {
	        neopixel_setPixel(i, 0xFF, 0x00, 0x00);
        }
		neopixel_show();
		_delay_ms(1000);
		for (int i = 0; i < neopixel_pixels; i++)
		{
			neopixel_setPixel(i, 0x00, 0xFF, 0x00);
		}
		neopixel_show();
		_delay_ms(1000);
		for (int i = 0; i < neopixel_pixels; i++)
		{
			neopixel_setPixel(i, 0x00, 0x00, 0xFF);
		}
		neopixel_show();
		_delay_ms(1000);
	}

	return 0;
}



