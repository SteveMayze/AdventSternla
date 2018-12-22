/*
 * NeoStrip5M.c
 *
 * Created: 22/12/2018 12:23:36
 * Author : Steven
 */ 

#include "stdlib.h"
#include "time.h"
#include <avr/io.h>
#include "neopixel.h"

/*! The setting for the CLKCTRL.MCLKCTRLB register */
#define _MAIN_CLOCK 0x00

#define BASE_HUE ((uint8_t) 0x03)
#define MED_HUE  ((uint8_t) 0x06)
#define HI_HUE   ((uint8_t) 0x0C)

uint8_t buffer[neopixel_buffer_size];



/************************************************************************/
/* The main control loop                                                */
/************************************************************************/
#define MAX_DELAY 10000
#define ANIMATION_COUNT 2


/*!
 * \brief	Lights up a random number of "stars" MAX_STARS and increases their
 * brightness until FF for the given colour is reached and then reduces the
 * intensity.
 */
 #define MAX_STARS 50
 pixel_type star_buffer[MAX_STARS];

void stars() {
	// Fill the buffers with each of their star allotments.

	neopixel_fill(NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);

	// int buf_count = rand() % MAX_BUFFERS;
	uint8_t star_count = rand() % MAX_STARS;
	for(uint8_t star_idx =0; star_idx < MAX_STARS; star_idx++){
		if ( star_idx < star_count+1){
			star_buffer[star_idx].pix = rand() % NEOPIXELS_SIZE;
			star_buffer[star_idx].red = rand() % 0x0A;
			star_buffer[star_idx].green = rand() % 0x0A;
			star_buffer[star_idx].blue = rand() % 0x0A;
		} else {
			star_buffer[star_idx].pix = 0xFF;
		}
	}
	neopixel_show();
	uint8_t gradient = rand() % 100;
	gradient = gradient < 25? 25: gradient;
	for (uint8_t i = 0; i < gradient; i++ ) {
		for( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++){
			if( star_buffer[star_idx].pix < 0xFFFF) {					
				neopixel_incPixelHue(star_buffer[star_idx] );
				neopixel_show();
			}
		}
		delay_ms(gradient);
	}
	delay_ms(150);
	for( uint8_t i = 0; i < gradient+1; i++ ) {
		for( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++){
			if( star_buffer[star_idx].pix < 0xFFFF){					
				neopixel_decrPixelHue(star_buffer[star_idx]);
				neopixel_show();
			}
		}
		delay_ms(gradient);
	}
}


int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.
	// uint8_t strips[NEOPIXELS_SIZE *3]; 

    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;

    PORTA.DIR |= 1 << 1;

 	srand(time(NULL));
	int delay_time;
	neopixel_fill(NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_show();
	while(true){
// 		neopixel_fill(BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
// 		neopixel_show();
		stars();
		delay_time = rand() % MAX_DELAY;
		if( delay_time < 1000 ) {
			delay_time = 1000;
		}
 		delay_ms(delay_time);
	}
	return 0;
}

