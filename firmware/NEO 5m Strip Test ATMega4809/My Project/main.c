


#include <atmel_start.h>
#include "stdlib.h"
#include "time.h"
#include "neopixel.h"
#include "neopixel_anim.h"
#include <stdio.h>
#include "usart_basic_example.h"

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

	atmel_start_init();

    // neopixel_init();

 	srand(time(NULL));
	// int delay_time;
	neopixel_fill(buffer, NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_show(buffer);
	printf("STARTING");
	while(true) {
		neo_anim_stars();
	}
	return 0;
}

