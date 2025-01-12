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
#include "neopixel_anim.h"

/*! The setting for the CLKCTRL.MCLKCTRLB register */
#define _MAIN_CLOCK 0x00

// #define __COMET_ONLY

// The buffer is the actual physical buffer memory that will be written out
// to the NEO Pixel strip. This could be viewed like a video buffer.



/************************************************************************/
/* The main control loop                                                */
/************************************************************************/
#define MAX_DELAY 10000
#define ANIMATION_COUNT 2

#ifdef __WITH_COMET
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

 	srand(time(NULL));
	// int delay_time;
	neopixel_fill(buffer, NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_show(buffer);
	bool ramp_down = false;
	bool still_active = true;
	int anim_cycles = 0;
	while(true) {
		uint8_t cycle = 0;
		neo_anim_clear();
		anim_cycles = rand() % NEO_ANIM_CYCLES;
		while (still_active) {
			still_active = neo_anim_stars(ramp_down);
			cycle++;
			if( cycle > anim_cycles ){
				ramp_down = true;
			}
		}
		delay_ms(3000);
		commet();
		delay_ms(3000);
		ramp_down = false;
		still_active = true;
	}
	return 0;
}

#elif defined(__COMET_ONLY)

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

	srand(time(NULL));
	// int delay_time;
	neopixel_fill(buffer, NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_show(buffer);
	while(true) {
		commet();
		delay_ms(3000);
	}
	return 0;
}


#else 

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

	srand(time(NULL));
	// int delay_time;
	neopixel_fill(buffer, NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_show(buffer);
	while(true) {
		neo_anim_stars(false);
	}
	return 0;
}

#endif