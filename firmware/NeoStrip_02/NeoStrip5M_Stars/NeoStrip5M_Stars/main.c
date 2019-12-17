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

#define BASE_HUE ((uint8_t) 0x03)
#define MED_HUE  ((uint8_t) 0x06)
#define HI_HUE   ((uint8_t) 0x0C)

// The buffer is the actual physical buffer memory that will be written out
// to the NEO Pixel strip. This could be viewed like a video buffer.



/************************************************************************/
/* The main control loop                                                */
/************************************************************************/
#define MAX_DELAY 10000
#define ANIMATION_COUNT 2


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
		neo_anim_stars();
	}
	return 0;
}

