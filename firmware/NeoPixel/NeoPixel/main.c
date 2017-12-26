/*
 * NewPixel.c
 *
 * Created: 19/12/2017 14:59:51
 * Author : Steven
 */ 

#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "neopixel.h"

// _MAIN_ALL_OFF
// _MAIN_ALL_ON
// _MAIN_TEST_1
#define _MAIN_TEST_4
#define _MAIN_CLOCK 0x00
// (0x00 << CLKCTRL_PDIV_gp) | ( 0x00 << CLKCTRL_PEN_bp )

#define LOW_INTENSITY 0x03



#ifdef _MAIN_TEST_4

int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	PORTA.DIR |= 1 << 1;

	uint8_t red_color = 0;
	uint8_t green_color = 0;
	uint8_t blue_color = 0;

	for (int i = 0; i < neopixel_pixels; i++)
	{
		if ( i <= 9) {
			red_color = LOW_INTENSITY;
			green_color = NEO_ALL_OFF;
			blue_color = LOW_INTENSITY;
		}
		if ( i >= 10 && i <= 19) {
			red_color = LOW_INTENSITY;
			green_color = NEO_ALL_OFF;
			blue_color = NEO_ALL_OFF;
		}
		if ( i >= 20 && i <= 29) {
			red_color = LOW_INTENSITY;
			green_color = LOW_INTENSITY;
			blue_color = NEO_ALL_OFF;
		}
		if ( i >= 30 && i <= 39) {
			red_color = NEO_ALL_OFF;
			green_color = LOW_INTENSITY;
			blue_color = NEO_ALL_OFF;
		}
		if ( i >= 40 && i <= 49) {
			red_color = NEO_ALL_OFF;
			green_color = LOW_INTENSITY;
			blue_color = LOW_INTENSITY;
		}
		if ( i >= 50 ) {
			red_color = NEO_ALL_OFF;
			green_color = NEO_ALL_OFF;
			blue_color = LOW_INTENSITY;
		}
		neopixel_setPixel(i, red_color, green_color, blue_color);
	}
	while(true)
	{
		neopixel_shift();
		neopixel_show();
		_delay_ms(50);
	}
	
	return 0;
}

#endif


#ifdef _MAIN_TEST_3

int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	PORTA.DIR |= 1 << 1;

	uint8_t red_color = 0;
	uint8_t green_color = 0;
	uint8_t blue_color = 0;

	for (int i = 0; i < neopixel_pixels; i++)
	{
		if ( i <= 19) {
			red_color = 0x1f;
			green_color = NEO_ALL_OFF;
			blue_color = NEO_ALL_OFF;
		}
		if ( i >= 20 && i <= 39) {
			red_color = NEO_ALL_OFF;
			green_color = 0x1f;
			blue_color = NEO_ALL_OFF;
		}
		if ( i >= 40 ) {
			red_color = NEO_ALL_OFF;
			green_color = NEO_ALL_OFF;
			blue_color = 0x1f;
		}
		neopixel_setPixel(i, red_color, green_color, blue_color);
	}
	while(true)
	{
		neopixel_shift();
		neopixel_show();
		_delay_ms(25);
	}
	
	return 0;
}

#endif



#ifdef _MAIN_TEST_2

int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	PORTA.DIR |= 1 << 1;

	uint8_t red_color = 0;
	uint8_t green_color = 0;
	uint8_t blue_color = 0;

	while(true)
	{
		for (int i = 0; i < neopixel_pixels; i++)
		{
			neopixel_setPixel(i, red_color, green_color, blue_color);
		}
		if( green_color == 0 && blue_color == 0 ) {
			red_color++;
		}
		if( red_color == 0 && blue_color == 0 ) {
			green_color++;
		}
		if( green_color == 0  && red_color == 0 ){
			blue_color++;
		}
		neopixel_show();
	}
	
	return 0;
}

#endif

#ifdef _MAIN_TEST_1

int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	PORTA.DIR |= 1 << 1;

	while(1)
	{
		for (int i = 0; i < neopixel_pixels; i++)
		{
			neopixel_setPixel(i, NEO_ALL_ON, NEO_ALL_ON, NEO_ALL_ON);
		}
		neopixel_show();
		_delay_ms(1000);
		for (int i = 0; i < neopixel_pixels; i++)
		{
			neopixel_setPixel(i, NEO_ALL_ON, NEO_ALL_OFF, NEO_ALL_OFF);
		}
		neopixel_show();
		_delay_ms(1000);
		for (int i = 0; i < neopixel_pixels; i++)
		{
			neopixel_setPixel(i, NEO_ALL_OFF, NEO_ALL_ON, NEO_ALL_OFF);
		}
		neopixel_show();
		_delay_ms(1000);
		for (int i = 0; i < neopixel_pixels; i++)
		{
			neopixel_setPixel(i, NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_ON);
		}
		neopixel_show();
		_delay_ms(1000);
		for (int i = 0; i < neopixel_pixels; i++)
		{
			neopixel_setPixel(i, NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
		}
		neopixel_show();
		_delay_ms(1000);
	}
	
	return 0;
}

#endif




#ifdef _MAIN_ALL_OFF // ALL OFF

int main(void)
{

    // This register is protected and can not be changed until the CPP register in the CPU
    // is written with the signature of 0xD8 ... I think I need to insert some assembly code here
    // This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
    // This needs to be checked for the electrical characteristics is such that the full 5V is required.

    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

    PORTA.DIR |= 1 << 1;
    for (int i = 0; i < neopixel_pixels; i++)
    {
	    neopixel_setPixel(i, NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
    }

	while(1)
	{
		neopixel_show();
	}

	return 0;
}

#endif


#ifdef _MAIN_ALL_ON // ALL ON

int main(void)
{

    // This register is protected and can not be changed until the CPP register in the CPU
    // is written with the signature of 0xD8 ... I think I need to insert some assembly code here
    // This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
    // This needs to be checked for the electrical characteristics is such that the full 5V is required.

    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

    PORTA.DIR |= 1 << 1;
    for (int i = 0; i < neopixel_pixels; i++)
    {
	    neopixel_setPixel(i, NEO_ALL_ON, NEO_ALL_ON, NEO_ALL_ON);
    }

	while(1)
	{
		neopixel_show();
	}

	return 0;
}

#endif



