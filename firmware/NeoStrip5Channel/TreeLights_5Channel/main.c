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


#define _NEO_RAIN
// #define _NEO_RAIN_MAIN

#define _NEOPIXEL_ANIM_CHANNEL
#define _NEOPIXEL_ANIM_CHANNEL_MAIN

#define BASE_HUE ((uint8_t) 0x03)
#define MED_HUE  ((uint8_t) 0x06)
#define HI_HUE   ((uint8_t) 0x0C)
#define MAX_BUFFERS 5
#define MAX_STARS 5
#define NEO_ANIM_CYCLES 100 // NEO_HUE_ADJ * 5
#define NEO_ANIM_MAX_GRADIENT 100

uint8_t buffer[MAX_BUFFERS][neopixel_buffer_size];

#ifdef _NEO_BASIC_ANIMS
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

#endif


#ifdef _NEO_RAIN
/*!
 * \brief	Creates an effect of a droplet getting heavy and then falling.
 */
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
#endif

 #ifdef _NEOPIXEL_ANIM_CHANNEL

/*!
 * \brief Pixel/Star status bits
 */
typedef union {
	struct {
		unsigned char active:1;
		unsigned char ramp_up:1;
		unsigned char not_used:6;
	} status_bits;
	unsigned char status;
} state_t;

 /*!
  * \brief The neopixel_anim_start_t structure defines the life and behavior of a "star". 
  * The pixel information maps the actual pixel and its colour information. The stars 
  * holds the status bits for whether the star is active and if it is in ramp_up mode 
  * i.e. increasing in intensity.
  */
 typedef struct {
	/*! The pixel being referenced. This contains the actual LED reference and the colour information. */
	pixel_type pixel;
	state_t state;
 } neopixel_anim_star_t;


 neopixel_anim_star_t star_buffer[MAX_BUFFERS][MAX_STARS];

  void neo_anim_clear(uint8_t buff) {
	  for ( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
		  star_buffer[buff][star_idx].state.status_bits.active = false;
		  star_buffer[buff][star_idx].pixel.red = 0x00;
		  star_buffer[buff][star_idx].pixel.green = 0x00;
		  star_buffer[buff][star_idx].pixel.blue = 0x00;
		  // neopixel_setPixel(buffer[buff], star_buffer[buff][star_idx].pixel.pix, 0x00, 0x00, 0x00);
	  }
  }

 bool neo_anim_any_active(uint8_t buff_idx) {
	for( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
		if ( star_buffer[buff_idx][star_idx].state.status_bits.active ) {
			return true;
		}
	}
	return false;
 }

 bool star_buffer_contians( uint8_t buff, uint8_t pix ){
	for( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
		if( star_buffer[buff][star_idx].state.status_bits.active && star_buffer[buff][star_idx].pixel.pix == pix ){
			return true;
		}
	}
	return false;
 }

 uint8_t get_next_pixel_from_star_buffer(uint8_t buff) {
	 uint8_t next_pix = rand() % NEOPIXELS_SIZE;
	 while ( star_buffer_contians( buff, next_pix )) {
		 next_pix = rand() % NEOPIXELS_SIZE;
	 }
	 return next_pix;
 }

 uint8_t rand_colour() {
	 uint8_t colour = 0x00;
	 while( colour == 0x00 ){
		 colour = rand() % NEO_HUE_ADJ;
	 }
	 return colour;
 }


 /*!
 * \brief	Lights up a random number of "stars" MAX_STARS and increases their
 * brightness until FF for the given colour is reached and then reduces the
 * intensity.
 */
 void neo_anim_stars(uint8_t strip[], uint8_t buff_idx) {
	uint8_t channel = 0b00000001 << buff_idx;
// 	uint8_t toss;
	for ( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
		if (star_buffer[buff_idx][star_idx].state.status_bits.active != true) {
			star_buffer[buff_idx][star_idx].pixel.pix = get_next_pixel_from_star_buffer(buff_idx);
			star_buffer[buff_idx][star_idx].state.status_bits.active = true;
			star_buffer[buff_idx][star_idx].state.status_bits.ramp_up = true;
			star_buffer[buff_idx][star_idx].pixel.red = rand() % NEO_HUE_ADJ;
			star_buffer[buff_idx][star_idx].pixel.green = rand() % NEO_HUE_ADJ;
			star_buffer[buff_idx][star_idx].pixel.blue = rand() % NEO_HUE_ADJ;
			// If they are all 0x00, then force at least one colour to a value.
			if ( star_buffer[buff_idx][star_idx].pixel.red == 0x00 && star_buffer[buff_idx][star_idx].pixel.green == 0x00 && star_buffer[buff_idx][star_idx].pixel.blue == 0x00) {
				star_buffer[buff_idx][star_idx].state.status_bits.active = false;

// 				toss = rand() % 3;
// 				switch( toss ){
// 					case 0:
// 					star_buffer[buff_idx][star_idx].pixel.red = rand_colour();
// 					break;
// 					case 1:
// 					star_buffer[buff_idx][star_idx].pixel.green = rand_colour();
// 					break;
// 					case 2:
// 					star_buffer[buff_idx][star_idx].pixel.blue = rand_colour();
// 					break;
// 				}
			}
		}
	}
	neopixel_setchannel(channel);
	neopixel_show(strip);
	bool limit_reached = false;
	for( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++){
		if ( star_buffer[buff_idx][star_idx].state.status_bits.active ) {
			if( star_buffer[buff_idx][star_idx].state.status_bits.ramp_up ) {
				limit_reached = neopixel_incPixelHue_with_limit(strip, star_buffer[buff_idx][star_idx].pixel );
				star_buffer[buff_idx][star_idx].state.status_bits.ramp_up ^= limit_reached;
			} else {
				limit_reached = neopixel_decrPixelHue_with_limit(strip, star_buffer[buff_idx][star_idx].pixel );
				if ( limit_reached ){
					star_buffer[buff_idx][star_idx].state.status_bits.active = false;
					star_buffer[buff_idx][star_idx].pixel.red = 0x00;
					star_buffer[buff_idx][star_idx].pixel.green = 0x00;
					star_buffer[buff_idx][star_idx].pixel.blue = 0x00;
					neopixel_setPixel(strip, star_buffer[buff_idx][star_idx].pixel.pix, 0x00, 0x00, 0x00);
				}
			}
			neopixel_setchannel(channel);
			neopixel_show(strip);
		}
	}
 }

 
 void neo_pixel_rampdown(uint8_t strip[], uint8_t buff_idx) {
 	uint8_t channel = 0b00000001 << buff_idx;
	for ( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
		bool limit_reached = neopixel_decrPixelHue_with_limit(strip, star_buffer[buff_idx][star_idx].pixel );
		if ( limit_reached ){
			star_buffer[buff_idx][star_idx].state.status_bits.active = false;
			star_buffer[buff_idx][star_idx].pixel.red = 0x00;
			star_buffer[buff_idx][star_idx].pixel.green = 0x00;
			star_buffer[buff_idx][star_idx].pixel.blue = 0x00;
			neopixel_setPixel(strip, star_buffer[buff_idx][star_idx].pixel.pix, 0x00, 0x00, 0x00);
		}
		neopixel_setchannel(channel);
		neopixel_show(strip);
	}
 }

 

#endif

#ifdef NEO_ANIM_BASIC_STARS
#define MAX_STARS 10
// uint8_t star_buffer[MAX_BUFFERS][MAX_STARS * 4];

pixel_type star_buffer[MAX_BUFFERS][MAX_STARS]; 

/*!
 * \brief	Lights up a random number of "stars" MAX_STARS and increases their
 * brightness until FF for the given colour is reached and then reduces the
 * intensity.
 */
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
#endif

#ifdef _NEOPIXEL_ANIM_CHANNEL_MAIN
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
	uint16_t cycle = 0;
	uint16_t cycle_limit = rand() % 1000;
	cycle_limit = (cycle_limit < 100? 100: cycle_limit);
	while(true){

		if ( cycle > cycle_limit ) {
// 			for( uint8_t buff_idx = 0; buff_idx < MAX_BUFFERS; buff_idx++){
// 				// neo_anim_clear( buff_idx );
// 				neo_pixel_rampdown(buffer[buff_idx], buff_idx);
// 			}
			cycle = 0;
			cycle_limit = rand() % 1000;
			cycle_limit = ( cycle_limit < 100? 100: cycle_limit);

			delay_ms(1000);
			rain();
			delay_ms(1000);
		}

		for ( int buff_idx = 0; buff_idx < MAX_BUFFERS;  buff_idx++) {
			neo_anim_stars(buffer[buff_idx], buff_idx);
		}
		//delay_ms(1000);
		uint8_t gradient = rand() % NEO_ANIM_MAX_GRADIENT;
		gradient = gradient < 2? 2: gradient;
		delay_ms(gradient);
		cycle++;

	}
	return 0;
}

#endif

#ifdef _NEO_RAIN_MAIN
int main(void)
{
	while( true ) {
		rain();
		delay_ms(3000);
	}
	return 0;
}
#endif
