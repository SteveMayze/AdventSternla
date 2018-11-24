/*
 * NeoStrip5Channel_plus.c
 *
 * Created: 13/02/2018 09:46:43
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
#define MAX_BUFFERS 5

uint8_t buffer[MAX_BUFFERS][neopixel_buffer_size];

void barber_pole(bool direction){

	uint8_t c1[] = { 0x04, 0x00, 0x00 };
	uint8_t c2[] = { 0x00, 0x02, 0x00 };

	neopixel_anim_init_bicolor(buffer[0], c1, c2);
	neopixel_anim_init_bicolor(buffer[1], c1, c2);
	neopixel_anim_init_bicolor(buffer[2], c1, c2);
	neopixel_anim_init_bicolor(buffer[3], c1, c2);
	neopixel_anim_init_bicolor(buffer[4], c1, c2);

	for(uint8_t i=0; i<2; i++){
		neopixel_shift(buffer[1], direction);
		neopixel_shift(buffer[2], direction);
		neopixel_shift(buffer[3], direction);
		neopixel_shift(buffer[4], direction);
	}

	for(uint8_t i=0; i<2; i++){
		neopixel_shift(buffer[2], direction);
		neopixel_shift(buffer[3], direction);
		neopixel_shift(buffer[4], direction);
	}

	for(uint8_t i=0; i<2; i++){
		neopixel_shift(buffer[3], direction);
		neopixel_shift(buffer[4], direction);
	}

	for(uint8_t i=0; i<2; i++){
		neopixel_shift(buffer[4], direction);
	}

	for (uint8_t i = 0; i < 240; i++) {

		neopixel_setchannel((uint8_t)0b00000001);
		neopixel_show(buffer[0]);

		neopixel_setchannel((uint8_t)0b00000010);
		neopixel_show(buffer[1]);

		neopixel_setchannel((uint8_t)0b00000100);
		neopixel_show(buffer[2]);

		neopixel_setchannel((uint8_t)0b00001000);
		neopixel_show(buffer[3]);

		neopixel_setchannel((uint8_t)0b00010000);
		neopixel_show(buffer[4]);

		neopixel_shift(buffer[0], direction);
		neopixel_shift(buffer[1], direction);
		neopixel_shift(buffer[2], direction);
		neopixel_shift(buffer[3], direction);
		neopixel_shift(buffer[4], direction);

		delay_ms(50);
	}
}


void chevron(bool direction){

	uint8_t c1[] = { 0x04, 0x04, 0x04 };
	uint8_t c2[] = { 0x03, 0x00, 0x00 };

	neopixel_anim_init_bicolor(buffer[0], c1, c2);
	neopixel_anim_init_bicolor(buffer[1], c1, c2);
	neopixel_anim_init_bicolor(buffer[2], c1, c2);

	for(uint8_t i=0; i<2; i++){
		neopixel_shift(buffer[1], direction);
		neopixel_shift(buffer[2], direction);
	}

	for(uint8_t i=0; i<2; i++){
		neopixel_shift(buffer[2], direction);
	}

	for (uint8_t i = 0; i < 240; i++) {

		neopixel_setchannel((uint8_t)0b00010001);
		neopixel_show(buffer[0]);

		neopixel_setchannel((uint8_t)0b00001010);
		neopixel_show(buffer[1]);

		neopixel_setchannel((uint8_t)0b00000100);
		neopixel_show(buffer[2]);

		neopixel_shift(buffer[0], direction);
		neopixel_shift(buffer[1], direction);
		neopixel_shift(buffer[2], direction);

		delay_ms(50);
	}
}




void colour_shuffle(void){

   	neopixel_fill(buffer[0], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
   	neopixel_fill(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF);
   	neopixel_fill(buffer[2], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE);

	for (int i = 0; i < 15; i++){
		neopixel_setchannel((uint8_t)0b00010101);
		neopixel_show(buffer[0]);
		neopixel_setchannel((uint8_t)0b00001010);
		neopixel_show(buffer[1]);

		delay_ms(500);

		neopixel_setchannel((uint8_t)0b00010101);
		neopixel_show(buffer[1]);
		neopixel_setchannel((uint8_t)0b00001010);
		neopixel_show(buffer[2]);

		delay_ms(500);
		neopixel_setchannel((uint8_t)0b00010101);
		neopixel_show(buffer[2]);
		neopixel_setchannel((uint8_t)0b00001010);
		neopixel_show(buffer[0]);

		delay_ms(500);


	}
}





void worm(void){

   	neopixel_fill(buffer[0], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
   	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00011111);
	neopixel_show(buffer[0]);

	neopixel_setchannel((uint8_t)0b00000001);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);

   	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000010);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, false, 10);

   	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);

   	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00001000);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, false, 10);

   	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00010000);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);

	
	neopixel_setchannel((uint8_t)0b00000001);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, true, 10);

	neopixel_fill(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000010);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, false, 10);

	neopixel_fill(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, true, 10);

	neopixel_fill(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00001000);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, false, 10);

	neopixel_fill(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00010000);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, true, 10);


	neopixel_setchannel((uint8_t)0b00000001);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, true, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000010);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, false, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, true, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00001000);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, false, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00010000);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, true, 10);



	neopixel_setchannel((uint8_t)0b00000001);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE);
	neopixel_setchannel((uint8_t)0b00000010);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, false, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE);
	neopixel_setchannel((uint8_t)0b00001000);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, false, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE);
	neopixel_setchannel((uint8_t)0b00010000);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);


	delay_ms(1000);
}


void worm2(void){

	neopixel_fill(buffer[0], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00011111);
	neopixel_show(buffer[0]);


	neopixel_setchannel((uint8_t)0b00010001);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00001010);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, false, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);



	neopixel_setchannel((uint8_t)0b00010001);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, true, 10);

	neopixel_fill(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00001010);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, false, 10);

	neopixel_fill(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, true, 10);


	neopixel_setchannel((uint8_t)0b00010001);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, true, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00001010);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, false, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, true, 10);



	neopixel_setchannel((uint8_t)0b00010001);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, true, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE);
	neopixel_setchannel((uint8_t)0b00001010);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, false, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, true, 10);
	
	delay_ms(1000);
}




void rain(void){

	neopixel_fill(buffer[0], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00011111);
	neopixel_show(buffer[0]);

	// Pick a channel, any channel
	int channel  = rand();
	channel %= 0b00011111;
	uint8_t channel_mask = channel+1;

	// Set the pixel 0 to White and let the droplet gather some weight
	neopixel_setchannel(channel_mask);
	neopixel_setPixel(buffer[0], 0, HI_HUE, HI_HUE, HI_HUE);
	neopixel_show(buffer[0]);
	delay_ms(1000);
	neopixel_shift(buffer[0], true);
	neopixel_setPixel(buffer[0], 0, MED_HUE, MED_HUE, MED_HUE);
	neopixel_show(buffer[0]);
	delay_ms(750);
	neopixel_shift(buffer[0], true);
	neopixel_setPixel(buffer[0], 0, MED_HUE, MED_HUE, MED_HUE);
	neopixel_show(buffer[0]);
	delay_ms(500);
	neopixel_shift(buffer[0], true);
	neopixel_setPixel(buffer[0], 0, BASE_HUE, BASE_HUE, BASE_HUE);
	neopixel_show(buffer[0]);
	delay_ms(125);
	neopixel_shift(buffer[0], true);

	// Now let the pixels _fall_
	for(int j=0; j < NEOPIXELS_SIZE; j++){
		neopixel_show(buffer[0]);
		neopixel_shift(buffer[0], true);
		delay_ms(15);
		if (j > NEOPIXELS_SIZE - 6 ) {
		 	neopixel_setPixel(buffer[0], 0, NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
		}
	}
}


#define MAX_STARS 10
// uint8_t star_buffer[MAX_BUFFERS][MAX_STARS * 4];

pixel_type star_buffer[MAX_BUFFERS][MAX_STARS]; 

void stars() {
	// Fill the buffers with each of their star allotments.

	// for (int i=0; i < 150; i++) {
		neopixel_fill(buffer[0], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
		neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
		neopixel_fill(buffer[2], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
		neopixel_fill(buffer[3], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
		neopixel_fill(buffer[4], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);

		// int buf_count = rand() % MAX_BUFFERS;
		int star_count = rand() % MAX_STARS;
		for (int buff = 0; buff < MAX_BUFFERS; buff++){
			for(int star_idx =0; star_idx < MAX_STARS; star_idx++){
				if ( star_idx < star_count+1){
					star_buffer[buff][star_idx].pix = rand() % NEOPIXELS_SIZE;
					star_buffer[buff][star_idx].red = rand() % 0x0A;
					star_buffer[buff][star_idx].green = rand() % 0x0A;
					star_buffer[buff][star_idx].blue = rand() % 0x0A;
				} else {
					star_buffer[buff][star_idx].pix = 0xFF;
				}
			}
		}
		neopixel_setchannel(0b00011111);
		neopixel_show(buffer[0]);

		for (int i = 0; i < 50; i++ ) {
			for (int buff =0; buff < MAX_BUFFERS; buff++) {
				uint8_t channel = 0b00000001 << buff;
				neopixel_setchannel(channel);
				for( int star_idx = 0; star_idx < MAX_STARS; star_idx++){
					if( star_buffer[buff][star_idx].pix < 0xFF) {					
						neopixel_incPixelHue(buffer[buff], star_buffer[buff][star_idx] );
						neopixel_show(buffer[buff]);
					}
				}
			}
			delay_ms(50);
		}
		delay_ms(150);
		for( int i = 0; i < 51; i++ ) {
			for (int buff =0; buff< MAX_BUFFERS; buff++) {
				uint8_t channel = 0b00000001 << buff;
				neopixel_setchannel(channel);
				for( int star_idx = 0; star_idx < MAX_STARS; star_idx++){
					if( star_buffer[buff]->pix < 0xFF){					
						neopixel_decrPixelHue(buffer[buff], star_buffer[buff][star_idx]);
						neopixel_show(buffer[buff]);
					}
				}
			}
			delay_ms(50);
		}
	// }
}

void stars1() {
	int star_count = rand() % MAX_STARS;
	// Fill the buffers with each of their star allotments.
	for (int buff = 0; buff < MAX_BUFFERS; buff++){
		neopixel_fill(buffer[buff], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
		for (int star = 0; star < star_count; star++){
			uint8_t pix = rand() % NEOPIXELS_SIZE;
			uint8_t red = rand() % 0x08;
			uint8_t green = rand() % 0x08;
			uint8_t blue = rand() % 0x08;
			neopixel_setPixel(buffer[buff], pix, red,green,blue);
		}
	}

	for (int i=0; i<150; i++) {

		for(int buff = 0; buff < MAX_BUFFERS; buff++){
			for(int pix = 0; pix<NEOPIXELS_SIZE; pix++){
				neopixel_incPixelHue1(buffer[buff], pix, 1);
			}
			uint8_t channel = 0b00000001 << buff;
			neopixel_setchannel(channel);
			neopixel_show(buffer[buff]);
			delay_ms(10);
		}
	}
	delay_ms(250);

	for (int i=0; i<150; i++) {

		for(int buff = 0; buff < MAX_BUFFERS; buff++){
			for(int pix = 0; pix<NEOPIXELS_SIZE; pix++){
				neopixel_decPixelHue1(buffer[buff], pix, 1);
			}
			uint8_t channel = 0b00000001 << buff;
			neopixel_setchannel(channel);
			neopixel_show(buffer[buff]);
			delay_ms(10);
		}
	}
	delay_ms(250);
}


/************************************************************************/
/* The main control loop                                                */
/************************************************************************/
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

	while(true){

// 		barber_pole(true);
// 		delay_ms(1000);
// 		barber_pole(false);
// 		delay_ms(2000);
// 
// 		colour_shuffle();
// 		delay_ms(2000);
// 
// 		worm();
// 		delay_ms(2000);
// 
// 		chevron(true);
// 		delay_ms(1000);
// 		chevron(false);
// 		delay_ms(2000);
// 
// 		worm2();
// 
// 		delay_ms(2000);
// 	
		for ( int i = 0; i < 5;  i++) {
			rain();
			delay_ms(1000);
		}
		for ( int i = 0; i < 5;  i++) {
			stars();
			delay_ms(1000);
		}
	}
	return 0;
}

