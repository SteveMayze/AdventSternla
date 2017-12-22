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


#define BIT_TEST(byte, bitCount) (((byte >> bitCount) & 0x01) << bitCount)

    unsigned int count = 0;

uint8_t NeoGreen [NeoNum];
uint8_t NeoBlue [NeoNum];
uint8_t NeoRed [NeoNum];

void NeoBit (uint8_t neobit)
{
	if (neobit > 0)
	{ 
	   PORTA.OUTSET = NeoPin; 
	   _delay_loop_1(4);
	   PORTA.OUTCLR = NeoPin; 
    } // delay_cycles (3); // Bit '1'
	else
	{ 
	    PORTA.OUTSET = NeoPin; 
	   _delay_loop_1(3);
		PORTA.OUTCLR = NeoPin; 
		// _delay_us(1);
		} // delay_cycles (6); // Bit '0'
}

void NeoInit (void)
{
	uint8_t NeoPixel;
	for (NeoPixel = 0; NeoPixel < NeoNum; NeoPixel++)
	{
		if (NeoPixel < 10)
		{ 
		   NeoGreen[NeoPixel] = 0; 
		   NeoBlue[NeoPixel] = 0; 
		   NeoRed[NeoPixel] = 0xFF; 
		} else if ((NeoPixel >= 10) & (NeoPixel < 20)) { 
		   NeoGreen[NeoPixel] = 0; 
		   NeoBlue[NeoPixel] = 0xFF; 
		   NeoRed[NeoPixel] = 0; 
		} else if ((NeoPixel >= 20) & (NeoPixel < 30)) { 
		   NeoGreen[NeoPixel] = 0; 
		   NeoBlue[NeoPixel] = 0xFF; 
		   NeoRed[NeoPixel] = 0xFF; 
		} else if ((NeoPixel >= 30) & (NeoPixel < 40)) { 
		   NeoGreen[NeoPixel] = 0xFF; 
		   NeoBlue[NeoPixel] = 0; 
		   NeoRed[NeoPixel] = 0; 
		} else if ((NeoPixel >= 40) & (NeoPixel < 50)) { 
		   NeoGreen[NeoPixel] = 0xFF; 
		   NeoBlue[NeoPixel] = 0; 
		   NeoRed[NeoPixel] = 0xFF; 
		} else if ((NeoPixel >= 50) & (NeoPixel < NeoNum)) { 
		   NeoGreen[NeoPixel] = 0xFF; 
		   NeoBlue[NeoPixel] = 0xFF; 
		   NeoRed[NeoPixel] = 0; 
		}
	}
}


void NeoInit_all_on (void)
{
	uint8_t NeoPixel;
	for (NeoPixel = 0; NeoPixel < NeoNum; NeoPixel++)
	{
		NeoGreen[NeoPixel] = 0xFF; NeoBlue[NeoPixel] = 0xFF; NeoRed[NeoPixel] = 0xFF;
	}
}

void NeoInit_all_off (void)
{
	uint8_t NeoPixel;
	for (NeoPixel = 0; NeoPixel < NeoNum; NeoPixel++)
	{
		NeoGreen[NeoPixel] = 0x00; NeoBlue[NeoPixel] = 0x00; NeoRed[NeoPixel] = 0x00;
	}
}


void NeoDraw (void)
{
	uint8_t NeoPixel;
	uint8_t BitCount;
	for (NeoPixel = 0; NeoPixel < NeoNum; NeoPixel++)
	{
	    uint8_t byte;
		byte = NeoGreen[NeoPixel];
		for (BitCount = 7; BitCount >= 0; BitCount--){
		   // NeoBit(BIT_TEST(NeoGreen[NeoPixel], BitCount));
		   NeoBit( (byte & 1<<BitCount) );

		}
		byte = NeoRed[NeoPixel];
		for (BitCount = 7; BitCount >= 0; BitCount--) {
		   // NeoBit(BIT_TEST(NeoRed[NeoPixel], BitCount));
		   NeoBit( (byte & 1<<BitCount) );
		}
		byte = NeoBlue[NeoPixel];
		for (BitCount = 7; BitCount >= 0; BitCount--) {
		   // NeoBit(BIT_TEST(NeoBlue[NeoPixel], BitCount));
		   NeoBit( (byte & 1<<BitCount) );
		}
	}
	 PORTA.OUTCLR = NeoPin;
	  _delay_us(100);
}

void NeoRotate (void)
{
	uint8_t NeoPixel;
	for (NeoPixel = 0; NeoPixel < NeoNum - 1; NeoPixel++)
	{
		NeoGreen[NeoPixel] = NeoGreen[NeoPixel + 1];
		NeoBlue[NeoPixel] = NeoBlue[NeoPixel + 1];
		NeoRed[NeoPixel] = NeoRed[NeoPixel + 1];
	}
	NeoGreen[NeoNum - 1] = NeoGreen[0];
	NeoBlue[NeoNum - 1] = NeoBlue[0];
	NeoRed[NeoNum - 1] = NeoRed[0];
}




int main(void)
{

    // This register is protected and can not be changed until the CPP register in the CPU
    // is written with the signature of 0xD8 ... I think I need to insert some assembly code here
    // This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
    // This needs to be checked for the electrical characteristics is such that the full 5V is required.

    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.MCLKCTRLB = 0x00;

    PORTA.DIR |= 1 << 1;


	NeoInit_all_off ();
	while(1)
	{
		NeoDraw ();
		NeoRotate ();
		_delay_ms (100);
	}
	return 0;
}



