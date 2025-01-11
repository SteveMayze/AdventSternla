/*!
 * \brief The main file for the NeoPixel driver for the ATTiny1614
 *
 * \file main.c
 *
 * Created 19/12/2017 14:59:51
 * \author Steve Mayze
 * \version 1.0
 */ 

 /*! The CPU Clock for use by delay.h */
#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "neopixel.h"

/*! The Animation sequence implementation chosen for the build */
#define _MAIN_ANIMATION_5


/*! The setting for the CLKCTRL.MCLKCTRLB register */
#define _MAIN_CLOCK 0x00
// (0x00 << CLKCTRL_PDIV_gp) | ( 0x00 << CLKCTRL_PEN_bp )

/*! The pixel hue to indicate a "low" intensity. */
#define LOW_INTENSITY 0x03
/*! The basic hue for a bright pixel */
#define BASE_HUE 15

/*!
 * \brief a wrapper over the _delay_ms function
 *
 *	This wrapper enables the ms count to be passed in as variable
 *	and not as a integer constant as dictated by the _delay_ms 
 *	function.
 */
void delay_ms(int ms){
	for(int i =0; i < ms; i++){
		_delay_ms(1);
	}
}

/*!
 * \brief	Rolls the pixels in a direction, the number of positions.
 * 
 * rolls the pixels one direction or the other the number of positions
 * with an intermediate animation of delay ms. The neopixel_show 
 * function will be called.

*/
void pixel_chaser(bool direction, int positions, int delay){
	for( int i = 0; i < positions; i++)
	{
		neopixel_shift(direction);
		neopixel_show();
		delay_ms(delay);
	}
}

/*!
 *	\brief	Intialise the buffer with a "pulsed rainbow" type 
 *			sequence.
 *
 *	The "rainbow" is dived over the 60 pixels. A group of 10 
 *	pixels for each colour group. The "pulse"effect is to have
 *	the middle pixel at the highest hue intensity.
 *
 */
void init_rainbow_pulse(uint8_t hue) {
	uint8_t red_color = 0;
	uint8_t green_color = 0;
	uint8_t blue_color = 0;

	int grade = -5;
	int colour = 100;
	int page;
	int grade_factor = hue / 5 ;

	for(int group = 0; group < 6; group++) {
		grade = -5;
		page = group * 10;
		for(int pix = 0; pix < 5; pix++) {
			colour = (hue + (grade * grade_factor));
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
			neopixel_setPixel( page+pix, red_color, green_color, blue_color);
		}
		grade = 0;
		for(int pix = 5; pix < 11; pix++){
			colour = hue + (grade * grade_factor);
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
			neopixel_setPixel(page+pix, red_color, green_color, blue_color);
		}
	}
}

/*!
 * \brief	Initialise the pixels with a "rainbow" series.
 *
 *	The colours are divided over the 60 pixels with six colours allocated
 *	to each group of 10 pixels.
 */
void init_rainbow(uint8_t hue){
	uint8_t red_color = 0;
	uint8_t green_color = 0;
	uint8_t blue_color = 0;

	for (int i = 0; i < neopixel_pixels; i++)
	{
		if ( i <= 9) {
			red_color = hue;
			green_color = NEO_ALL_OFF;
			blue_color = hue;
		}
		if ( i >= 10 && i <= 19) {
			red_color = hue;
			green_color = NEO_ALL_OFF;
			blue_color = NEO_ALL_OFF;
		}
		if ( i >= 20 && i <= 29) {
			red_color = hue;
			green_color = hue;
			blue_color = NEO_ALL_OFF;
		}
		if ( i >= 30 && i <= 39) {
			red_color = NEO_ALL_OFF;
			green_color = hue;
			blue_color = NEO_ALL_OFF;
		}
		if ( i >= 40 && i <= 49) {
			red_color = NEO_ALL_OFF;
			green_color = hue;
			blue_color = hue;
		}
		if ( i >= 50 ) {
			red_color = NEO_ALL_OFF;
			green_color = NEO_ALL_OFF;
			blue_color = hue;
		}
		neopixel_setPixel(i, red_color, green_color, blue_color);
	}
}

/*!
 *	\brief	Fills the pixel strip with a colour
 *
 *	The colour is filled based on the direction and with an animation delay.
 *	The neopixel_show will be called.
 */
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

/*!
 * \brief The wipe function that will wipe in a "rainbow"
 *
 */
void rainbow_wipe(uint8_t hue, bool direction, int delay){

	uint8_t pixel = ( direction )? neopixel_pixels - 1: 0;
	uint8_t red, green, blue;
	for(int i = 0; i < neopixel_pixels; i++){
		if( direction ) {
			if ( i <= 9) {
				red = hue;
				green = NEO_ALL_OFF;
				blue = hue;
			}
			if ( i >= 10 && i <= 19) {
				red = hue;
				green = NEO_ALL_OFF;
				blue = NEO_ALL_OFF;
			}
			if ( i >= 20 && i <= 29) {
				red = hue;
				green = hue;
				blue = NEO_ALL_OFF;
			}
			if ( i >= 30 && i <= 39) {
				red = NEO_ALL_OFF;
				green = hue;
				blue = NEO_ALL_OFF;
			}
			if ( i >= 40 && i <= 49) {
				red = NEO_ALL_OFF;
				green = hue;
				blue = hue;
			}
			if ( i >= 50 ) {
				red = NEO_ALL_OFF;
				green = NEO_ALL_OFF;
				blue = hue;
			}

			neopixel_setPixel(pixel, red, green, blue);
			neopixel_show();
			neopixel_shift(direction);
		} else {
			if ( i <= 9) {
				red = hue;
				green = NEO_ALL_OFF;
				blue = hue;
			}
			if ( i >= 10 && i <= 19) {
				red = hue;
				green = NEO_ALL_OFF;
				blue = NEO_ALL_OFF;
			}
			if ( i >= 20 && i <= 29) {
				red = hue;
				green = hue;
				blue = NEO_ALL_OFF;
			}
			if ( i >= 30 && i <= 39) {
				red = NEO_ALL_OFF;
				green = hue;
				blue = NEO_ALL_OFF;
			}
			if ( i >= 40 && i <= 49) {
				red = NEO_ALL_OFF;
				green = hue;
				blue = hue;
			}
			if ( i >= 50 ) {
				red = NEO_ALL_OFF;
				green = NEO_ALL_OFF;
				blue = hue;
			}

			neopixel_setPixel(0, red, green, blue);
			neopixel_setPixel(neopixel_pixels - 1, red, green, blue);
			neopixel_show();
			neopixel_shift(direction);
		}
		delay_ms(delay);

	}
}


#ifdef _MAIN_INIT_TEST


int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	PORTA.DIR |= 1 << 1;

	// int delay, positions;
	// positions = 60;
	// delay = 50;
	init_rainbow_pulse( BASE_HUE );

	while(true){
		init_rainbow_pulse( BASE_HUE );
	}

	
	return 0;
}


#endif

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
	init_rainbow_pulse( BASE_HUE );

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

/*!
 * \brief The main function for the animation and driver
 */
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
	positions = neopixel_pixels * 4;
	bool filltype = true;
	while( true ) {
		delay = 10;
        wipe(LOW_INTENSITY, 0x00, 0x00, true, delay);
		_delay_ms(100);
        wipe(LOW_INTENSITY, LOW_INTENSITY, 0x00, false, delay);
		_delay_ms(100);
        wipe(0x00, LOW_INTENSITY, 0x00, true, delay);
		_delay_ms(100);
        wipe(0x00, LOW_INTENSITY, LOW_INTENSITY, false, delay);
		_delay_ms(100);
        wipe(0x00, 0x00, LOW_INTENSITY, true, delay);
		_delay_ms(100);
        wipe(LOW_INTENSITY, 0x00, LOW_INTENSITY, false, delay);
		_delay_ms(100);

		delay = 50;
		if ( filltype ) {
			// init_rainbow( LOW_INTENSITY );
			rainbow_wipe( LOW_INTENSITY, true, delay);
			filltype = false;
		} else {
			init_rainbow_pulse( BASE_HUE );
			filltype = true;
		}
		delay = 100;
		pixel_chaser(true, positions, delay);
		_delay_ms(500);
		pixel_chaser(false, positions, delay);
		_delay_ms(500);

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



