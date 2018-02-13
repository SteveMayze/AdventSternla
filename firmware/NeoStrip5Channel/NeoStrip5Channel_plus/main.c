/*
 * NeoStrip5Channel_plus.c
 *
 * Created: 13/02/2018 09:46:43
 * Author : Steven
 */ 

#include <avr/io.h>
#include "neopixel.h"
#include "neopixel_anim.h"


/*! The setting for the CLKCTRL.MCLKCTRLB register */
#define _MAIN_CLOCK 0x00

#define BASE_HUE 0x03

uint8_t buffer[3][neopixel_buffer_size];


int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.
	// uint8_t strips[NEOPIXELS_SIZE *3]; 

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;


	neopixel_init();


	// neopixel_anim_init_rainbow(buffer[0], 0x03 );
	// neopixel_anim_init_rainbow(buffer[1], 0x03 );

	uint8_t c1[] = { 0x04, 0x00, 0x00 };
	uint8_t c2[] = { 0x00, 0x02, 0x00 };

	neopixel_anim_init_bicolor(buffer[0], c1, c2);
	// neopixel_anim_init_bicolor(buffer[1], c1, c2);
	neopixel_anim_init_rainbow(buffer[1], BASE_HUE);
	neopixel_anim_init_bicolor(buffer[2], c1, c2);

	for(uint8_t i=0; i<5; i++){
		neopixel_shift(buffer[2], true);
		//neopixel_shift(buffer[2], true);
	}

// 	for(uint8_t i=0; i<5; i++){
// 		neopixel_shift(buffer[2], true);
// 	}

	while(true){

		neopixel_setchannel((uint8_t)0b00000001);
		neopixel_show(buffer[0]);

		neopixel_setchannel((uint8_t)0b00000010);
		neopixel_show(buffer[1]);

		neopixel_setchannel((uint8_t)0b00000100);
		neopixel_show(buffer[2]);

		neopixel_shift(buffer[0], true);
		neopixel_shift(buffer[1], false);
		neopixel_shift(buffer[2], true);

		delay_ms(100);
	}

	return 0;
}

