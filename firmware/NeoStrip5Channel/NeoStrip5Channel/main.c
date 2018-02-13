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
#include "neopixel_anim.h"

/*! The Animation sequence implementation chosen for the build */
#define _MAIN_ANIMATION_7


/*! The setting for the CLKCTRL.MCLKCTRLB register */
#define _MAIN_CLOCK 0x00

/*! The pixel hue to indicate a "low" intensity. */
#define LOW_INTENSITY 0x03
/*! The basic hue for a bright pixel */
#define BASE_HUE 15


#ifdef _MAIN_INIT_TEST


int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	neopixel_init();

	// int delay, positions;
	// positions = 60;
	// delay = 50;
	neopixel_anim_init_rainbow_pulse( BASE_HUE );

	while(true){
		neopixel_anim_init_rainbow_pulse( BASE_HUE );
	}

	return 0;
}
#endif




#ifdef _MAIN_ANIMATION_10


int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;


	neopixel_init();


	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;

	neopixel_fill(red, green, blue);
	neopixel_setchannel( 0x00 );
	neopixel_show();

	neopixel_setchannel( 0x1F );
	neopixel_show();

	int rdelay = 250;
	#define HUE 0x10
	int channel = 1;
	int hue = HUE;
	while(true){

	   hue = rand() % HUE;

		neopixel_anim_init_random(hue);
		neopixel_setchannel(channel);
		neopixel_show();
		channel++;
		if (channel > 0b00000100){
		   channel = 1;
		}
		//_delay_ms(delay);

	}

	
	return 0;
}
#endif


#ifdef _MAIN_ANIMATION_9


int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	neopixel_init();

	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;

	neopixel_fill(red, green, blue);
	neopixel_setchannel( 0x00 );
	neopixel_show();

	neopixel_setchannel( 0x1F );
	neopixel_show();

	int delay = 20;
	#define GOING_GREEN 0
	#define GOING_RED 1
	#define  GOING_BLUE 2
	#define HUE 0x80

	uint8_t mode = 0;

	red = 0x00;
	blue = 0x00;
	green = 0x00;
	neopixel_fill(red, green, blue);
	neopixel_show();

	mode = GOING_GREEN;

	while(true){

		// GRB
		for(int i = 0; i < 200; i++){
			neopixel_anim_init_random(HUE/2);
			neopixel_show();
			_delay_ms(delay);
		}

		// GRB
        red = 0x00;
        blue = 0x00;
        green = 0x00;
        neopixel_fill(red, green, blue);
        neopixel_show();
		for ( int i = 0; i < HUE *3; i++){
		if ( GOING_GREEN == mode && green < HUE  ) {
			green++;
			if( blue > 1 ) blue--;
			if( green > HUE-1 ){
				blue = 0;
				mode = GOING_RED;
			}
			
			} else {
				if ( GOING_RED == mode && red < HUE ){
					red++;
					if (green > 1)
					green--;
					if( red > HUE-1 ){
						green = 0;
						mode = GOING_BLUE;
					}
					} else {
					if ( GOING_BLUE == mode && blue < HUE ){
						blue++;
						if (red > 1 ) red--;
						if ( blue > HUE-1 ){
							red = 0;
							mode = GOING_GREEN;
						}
					}
				}
			}
			neopixel_fill(red, green, blue);
			neopixel_show();
			_delay_ms(delay);
		}
	}

	return 0;
}
#endif



#ifdef _MAIN_ANIMATION_8


int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	neopixel_init();

	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;

	neopixel_fill(red, green, blue);
	neopixel_setchannel( 0x00 );
	neopixel_show();

	neopixel_setchannel( 0x1F );
	neopixel_show();

	int delay = 250;
	#define HUE 0x10

	while(true){
		// GRB
		neopixel_anim_init_random(HUE);
		neopixel_show();
		_delay_ms(delay);

	}

	
	return 0;
}
#endif



#ifdef _MAIN_ANIMATION_7


int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

	neopixel_init();

	int delay;
	delay = 50;

	#define GOING_GREEN 0
	#define GOING_RED 1
    #define  GOING_BLUE 2
	#define UPPER_LIMIT 0x80

	uint8_t mode = 0;
    uint8_t red, blue, green;
	red = 0x00;
	blue = 0x00;
	green = 0x00;
	neopixel_fill(red, green, blue);
	neopixel_show();

	mode = GOING_GREEN;
	while(true){

	    // GRB
		if ( GOING_GREEN == mode && green < UPPER_LIMIT  ) {
		   green++;
		   if( blue > 1 ) blue--;
		   if( green > UPPER_LIMIT-1 ){
		      blue = 0;
		      mode = GOING_RED;
		   }
		   
		} else {
		   if ( GOING_RED == mode && red < UPPER_LIMIT ){
		      red++;
			  if (green > 1)
			     green--;
			  if( red > UPPER_LIMIT-1 ){
			     green = 0;
			     mode = GOING_BLUE;
			  }
		   } else {
		      if ( GOING_BLUE == mode && blue < UPPER_LIMIT ){
			     blue++;
				 if (red > 1 ) red--;
				 if ( blue > UPPER_LIMIT-1 ){
				    red = 0;
				    mode = GOING_GREEN;
				 }
			  }
		   }
		}
    	neopixel_fill(red, green, blue);
		neopixel_show();

		_delay_ms(delay);

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
	neopixel_anim_init_rainbow_pulse( BASE_HUE );

	while(true){

		neopixel_anim_pixel_chaser(true, positions, delay);
		_delay_ms(500);
		neopixel_anim_pixel_chaser(false, positions, delay);
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

	neopixel_init();

	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;

	neopixel_fill(red, green, blue);
	neopixel_setchannel( 0x00 );
	neopixel_show();

	neopixel_setchannel( 0x1F );
	neopixel_show();

	int delay, positions;
	positions = neopixel_pixels * 4;
	bool filltype = true;
	while( true ) {
		delay = 10;
        neopixel_anim_wipe(LOW_INTENSITY, 0x00, 0x00, true, delay);
		_delay_ms(100);
        neopixel_anim_wipe(LOW_INTENSITY, LOW_INTENSITY, 0x00, false, delay);
		_delay_ms(100);
        neopixel_anim_wipe(0x00, LOW_INTENSITY, 0x00, true, delay);
		_delay_ms(100);
        neopixel_anim_wipe(0x00, LOW_INTENSITY, LOW_INTENSITY, false, delay);
		_delay_ms(100);
        neopixel_anim_wipe(0x00, 0x00, LOW_INTENSITY, true, delay);
		_delay_ms(100);
        neopixel_anim_wipe(LOW_INTENSITY, 0x00, LOW_INTENSITY, false, delay);
		_delay_ms(100);

		delay = 50;
		if ( filltype ) {
			// init_rainbow( LOW_INTENSITY );
			neopixel_anim_rainbow_wipe( LOW_INTENSITY, true, delay);
			filltype = false;
		} else {
			neopixel_anim_init_rainbow_pulse( BASE_HUE );
			filltype = true;
		}
		delay = 100;
		neopixel_anim_pixel_chaser(true, positions, delay);
		_delay_ms(500);
		neopixel_anim_pixel_chaser(false, positions, delay);
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
	neopixel_anim_init_rainbow();
	//int tick = 1;
	bool down = true;
	while(true){
		neopixel_anim_pixel_chaser(true, positions, delay);
		_delay_ms(500);
		neopixel_anim_pixel_chaser(false, positions, delay);
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

	neopixel_init();

	int delay, positions;
	positions = 120;
	delay = 100;
	neopixel_anim_init_rainbow();
	//int tick = 1;
	bool down = true;
	while(true){
     	neopixel_anim_pixel_chaser(true, positions, delay);
		_delay_ms(500);
		neopixel_anim_pixel_chaser(false, positions, delay);
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

	neopixel_init();

	int delay, positions;
	positions = 240;
	delay = 100;
	neopixel_anim_init_rainbow();

	while(true){

		neopixel_anim_pixel_chaser(true, positions, delay);
		_delay_ms(500);
		neopixel_anim_pixel_chaser(false, positions, delay);
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

	neopixel_init();

	uint8_t red_color = 0;
	uint8_t green_color = 0;
	uint8_t blue_color = 0;

	neopixel_fill(red_color, green_color, blue_color);
	neopixel_setchannel( 0x00 );
	neopixel_show();

	neopixel_setchannel( 0x1F );
	neopixel_show();

    int delay;
	// int positions = 240;
    delay = 50;
    neopixel_anim_init_rainbow((uint8_t) 0x03 );
	uint8_t channel = 1;
	while(true){

		neopixel_setchannel( channel );
		channel++;
		if(channel > 7) channel = 1;

		neopixel_anim_pixel_chaser(true, 60, delay);

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

	neopixel_init();

	uint8_t red_color = 0;
	uint8_t green_color = 0;
	uint8_t blue_color = 0;

    neopixel_fill(red_color, green_color, blue_color);
    neopixel_setchannel( 0x00 );
    neopixel_show();

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

	neopixel_setchannel( 0xFF );
	while(true)
	{
 		// for(uint8_t channel = 0; channel<0x0F; channel++){
			// neopixel_shift(true);
			// NEOPIXEL_PORT &= (~(1<<NEOPIXEL_LATCH_PIN));
			// neopixel_setchannel( channel );
			// NEOPIXEL_PORT |= (1<<NEOPIXEL_LATCH_PIN);
			neopixel_show();
			_delay_ms(500);
		// }
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

	neopixel_init();

	uint8_t red_color = 0;
	uint8_t green_color = 0;
	uint8_t blue_color = 0;

	neopixel_fill(red_color, green_color, blue_color);
	neopixel_setchannel( 0x00 );
	neopixel_show();

	neopixel_setchannel( (uint8_t)0x0F );

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

	neopixel_init();

	neopixel_setchannel( (uint8_t)0x0F );


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

	neopixel_init();

    for (int i = 0; i < neopixel_pixels; i++)
    {
	    neopixel_setPixel(i, NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
    }

	while(1)
	{
		neopixel_setchannel( 0x1F );

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

	neopixel_init();

	neopixel_setchannel( (uint8_t)0x0F );

    for (int i = 0; i < neopixel_pixels; i++)
    {
	    neopixel_setPixel(i, NEO_ALL_ON, NEO_ALL_ON, NEO_ALL_ON);
    }
   neopixel_show();

	while(1)
	{
	   _delay_ms(5000);
	}

	return 0;
}

#endif



