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


#define _MAIN_ANIMATION_2


#define _MAIN_CLOCK 0x00
// (0x00 << CLKCTRL_PDIV_gp) | ( 0x00 << CLKCTRL_PEN_bp )

#define LOW_INTENSITY 0x03


void delay_ms(int ms){
	for(int i =0; i < ms; i++){
		_delay_ms(1);
	}
}

void pixel_chaser(bool direction, int positions, int delay){
	for( int i = 0; i < positions; i++)
	{
		neopixel_shift(direction);
		neopixel_show();
		delay_ms(delay);
	}
}

void init_rainbow_pulse(void) {
	uint8_t red_color = 0;
	uint8_t green_color = 0;
	uint8_t blue_color = 0;

	int grade = -5;
	int colour = 0x1F;

	for(int group = 0; group < 6; group++) {
		grade = -5;
		for(int pix = 0; pix < 5; pix++) {
			colour = 0x1F + (grade * 10);
			grade++;
			switch( group ) {
				case 0:
					red_color = colour;
					green_color = NEO_ALL_OFF;
					blue_color = colour;
					break;
				case 1:
					red_color = colour;
					green_color = NEO_ALL_OFF;
					blue_color = NEO_ALL_OFF;
					break;
				case 2:
					red_color = colour;
					green_color = colour;
					blue_color = NEO_ALL_OFF;
					break;
				case 3:
					red_color = NEO_ALL_OFF;
					green_color = colour;
					blue_color = NEO_ALL_OFF;
					break;
				case 4:
					red_color = NEO_ALL_OFF;
					green_color = colour;
					blue_color = colour;
					break;
				case 5:
					red_color = NEO_ALL_OFF;
					green_color = NEO_ALL_OFF;
					blue_color = colour;
					break;
				default:
					break;
			}
			neopixel_setPixel((group * 10)+pix, red_color, green_color, blue_color);
		}
		for(int pix = 0; pix < 5; pix++){
			colour = 0x1F + grade * 10;
			grade--;
			switch( group ){
				case 0:
					red_color = colour;
					green_color = NEO_ALL_OFF;
					blue_color = colour;
					break;
				case 1:
					red_color = colour;
					green_color = NEO_ALL_OFF;
					blue_color = NEO_ALL_OFF;
					break;
				case 2:
					red_color = colour;
					green_color = colour;
					blue_color = NEO_ALL_OFF;
					break;
				case 3:
					red_color = NEO_ALL_OFF;
					green_color = colour;
					blue_color = NEO_ALL_OFF;
					break;
				case 4:
					red_color = NEO_ALL_OFF;
					green_color = colour;
					blue_color = colour;
					break;
				case 5:
					red_color = NEO_ALL_OFF;
					green_color = NEO_ALL_OFF;
					blue_color = colour;
					break;
				default:
					break;
			}
			neopixel_setPixel((group * 10)+pix, red_color, green_color, blue_color);
		}
	}
}

void init_rainbow(void){
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
}


void wipe(uint8_t red, uint8_t green, uint8_t blue, bool direction, int delay){

    uint8_t pixel = ( direction )? neopixel_pixels - 1: 0;
	// uint8_t pixel = neopixel_pixels - 1;
	for(int i = 0; i < neopixel_pixels; i++){
	    if( direction ) {
			neopixel_setPixel(pixel, red, green, blue);
			neopixel_show();
			neopixel_shift(direction);
		} else {
			neopixel_setPixel(0, red, green, blue);
			neopixel_setPixel(neopixel_pixels - 1, red, green, blue);
			neopixel_show();
			neopixel_shift(direction);
		}
		delay_ms(delay);

	}
}



#ifdef _MAIN_ANIMATION_6


int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	PORTA.DIR |= 1 << 1;

	int delay, positions;
	positions = 60;
	delay = 50;
	init_rainbow_pulse();

	while(true){

		pixel_chaser(true, positions, delay);
		_delay_ms(500);
		pixel_chaser(false, positions, delay);
		_delay_ms(500);

	}

	
	return 0;
}


#endif


#ifdef _MAIN_ANIMATION_5

int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	PORTA.DIR |= 1 << 1;

	int delay, positions;
	positions = 60;
	delay = 50;
	init_rainbow();
	while( true ) {
		pixel_chaser(true, positions, delay);
		_delay_ms(500);
		pixel_chaser(false, positions, delay);
        wipe(0x00, 0x00, 0x00, false, delay);
	    _delay_ms(500);
		init_rainbow();		
	}
	return 0;
}

#endif


#ifdef _MAIN_ANIMATION_4

int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	PORTA.DIR |= 1 << 1;

	int delay, positions;
	positions = 120;
	delay = 100;
	init_rainbow();
	//int tick = 1;
	bool down = true;
	while(true){
		pixel_chaser(true, positions, delay);
		_delay_ms(500);
		pixel_chaser(false, positions, delay);
		_delay_ms(500);
		//if ( (tick % 1) == 0) {
		if( down ) {
			delay -= 10;
			} else {
			delay += 10;
		}
		if ( delay < 10){
			down = false;
		}
		if (delay > 100 ) {
			down = true;
		}
		//tick = 1;
		//}
		//tick++;

	}

	
	return 0;
}

#endif


#ifdef _MAIN_ANIMATION_3

int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	PORTA.DIR |= 1 << 1;

	int delay, positions;
	positions = 120;
	delay = 100;
	init_rainbow();
	//int tick = 1;
	bool down = true;
	while(true){
     	pixel_chaser(true, positions, delay);
		_delay_ms(500);
		pixel_chaser(false, positions, delay);
		_delay_ms(500);
		//if ( (tick % 1) == 0) {
		    if( down ) {
				delay -= 10;
			} else {
			    delay += 10;
			}
			if ( delay < 10){
			   down = false;
			} 
			if (delay > 100 ) {
			   down = true;
			}
			//tick = 1;	
		//}
		//tick++;

	}

	
	return 0;
}

#endif


#ifdef _MAIN_ANIMATION_2

int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	PORTA.DIR |= 1 << 1;

	int delay, positions;
	positions = 240;
	delay = 100;
	init_rainbow();

	while(true){

		pixel_chaser(true, positions, delay);
		_delay_ms(500);
		pixel_chaser(false, positions, delay);
		_delay_ms(500);

	}

	
	return 0;
}

#endif



#ifdef _MAIN_ANIMATION_1

int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	PORTA.DIR |= 1 << 1;

    int delay, positions;
    positions = 240;
    delay = 50;
    init_rainbow();

	while(true){

		pixel_chaser(true, 60, delay);

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



