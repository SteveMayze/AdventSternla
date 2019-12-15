/*
 * neopixel_anim.c
 *
 * Created: 22/12/2018 15:47:12
 *  Author: Steven
 */ 
#include <avr/io.h>
#include "time.h"
#include "neopixel.h"
#include "neopixel_anim.h"
 
#define _NEOPIXEL_ANIM_NEW

#define MAX_STARS 50
#define NEO_ANIM_CYCLES NEO_HUE_ADJ * 100
#define NEO_ANIM_MAX_GRADIENT 10
// #define NEO_ANIM_CYCLES 1

 #ifdef _NEOPIXEL_ANIM_NEW

 /*!
  * The neopixel_anim_start_t structure defines the life and behavior of a "star". 
  */
 typedef struct {
	/*! The pixel being referenced. This contains the actual LED reference and the colour information. */
	pixel_type pixel;
	bool active;
	bool ramp_up;
 } neopixel_anim_star_t;

 neopixel_anim_star_t star_buffer[MAX_STARS];

 void neo_anim_clear(uint8_t strip[]) {
	for ( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
		star_buffer[star_idx].active = false;
		star_buffer[star_idx].pixel.red = 0x00;
		star_buffer[star_idx].pixel.green = 0x00;
		star_buffer[star_idx].pixel.blue = 0x00;
		neopixel_setPixel(strip, star_buffer[star_idx].pixel.pix, 0x00, 0x00, 0x00);
	}
 }

 bool neo_anim_any_active() {
	for( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
		if ( star_buffer[star_idx].active ) {
			return true;
		}
	}
	return false;
 }

 bool buffer_contians( uint8_t pix ){
	bool result = false;
	for( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
		if( star_buffer[star_idx].active && star_buffer[star_idx].pixel.pix == pix ){
			result = true;
			break;
		}
	}
	return result;
 }

 uint8_t get_next_pixel_from_star_buffer() {
	 uint8_t next_pix = rand() % NEOPIXELS_SIZE;
	 while ( buffer_contians( next_pix )) {
		 next_pix = rand() % NEOPIXELS_SIZE;
	 }
	 return next_pix;
 }

uint8_t neo_count_actives() {
	uint8_t actives = 0;
	for ( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
		if ( star_buffer[star_idx].active) {
			actives++;
		}
	}
	return actives;
}

 /*!
 * \brief	Lights up a random number of "stars" MAX_STARS and increases their
 * brightness until FF for the given colour is reached and then reduces the
 * intensity.
 */
 void neo_anim_stars(uint8_t strip[]) {
	// Clear the buffer
	neo_anim_clear( strip );
	uint16_t cycle = 0;
	bool finish_up = false;
	bool all_active = true;
	while ( all_active ) {
	// Iterate through each star definition
		// uint8_t actives = cycle > 0 ? MAX_STARS: cycle ;
		if ( !finish_up ) {
			for ( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
				if (star_buffer[star_idx].active != true) {
					// We have decided to activate this. Enable this and set a base colour.
					star_buffer[star_idx].pixel.pix = get_next_pixel_from_star_buffer();
					star_buffer[star_idx].active = true;
					star_buffer[star_idx].ramp_up = true;
					star_buffer[star_idx].pixel.red = rand() % NEO_HUE_ADJ;
					star_buffer[star_idx].pixel.green = rand() % NEO_HUE_ADJ;
					star_buffer[star_idx].pixel.blue = rand() % NEO_HUE_ADJ;
				}
			}
			neopixel_show(strip);
		} 
		bool limit_reached = false;
		for( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++){
			if ( star_buffer[star_idx].active ) {
				if( star_buffer[star_idx].ramp_up ) {
					limit_reached = neopixel_incPixelHue_with_limit(strip, star_buffer[star_idx].pixel );
					star_buffer[star_idx].ramp_up ^= limit_reached;
				} else {
					limit_reached = neopixel_decrPixelHue_with_limit(strip, star_buffer[star_idx].pixel );
					if ( limit_reached ){
						star_buffer[star_idx].active = false;
						star_buffer[star_idx].pixel.red = 0x00;
						star_buffer[star_idx].pixel.green = 0x00;
						star_buffer[star_idx].pixel.blue = 0x00;
						neopixel_setPixel(strip, star_buffer[star_idx].pixel.pix, 0x00, 0x00, 0x00);
					}
				}
				neopixel_show(strip);
			}
		}
		uint8_t gradient = rand() % NEO_ANIM_MAX_GRADIENT;
		gradient = gradient < 2? 2: gradient;
		delay_ms(gradient);
		cycle++;
		if( cycle > NEO_ANIM_CYCLES ) {
			finish_up = true;
			cycle = 0;
		}
		all_active = neo_anim_any_active();
	}
 }

#endif

 #ifdef _NEOPIXEL_ANIM_BASIC
 pixel_type star_buffer[MAX_STARS];

/*!
 * \brief	Lights up a random number of "stars" MAX_STARS and increases their
 * brightness until FF for the given colour is reached and then reduces the
 * intensity.
 */
 void neo_anim_stars(uint8_t strip[]) {
	 // Fill the buffers with each of their star allotments.

	 neopixel_fill(strip, NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);

	 // int buf_count = rand() % MAX_BUFFERS;
	 uint8_t star_count = rand() % MAX_STARS;
	 for(uint8_t star_idx =0; star_idx < MAX_STARS; star_idx++){
		 if ( star_idx < star_count+1){
			 star_buffer[star_idx].pix = rand() % NEOPIXELS_SIZE;
			 star_buffer[star_idx].red = rand() % NEO_HUE_ADJ;
			 star_buffer[star_idx].green = rand() % NEO_HUE_ADJ;
			 star_buffer[star_idx].blue = rand() % NEO_HUE_ADJ;
			 } else {
			 star_buffer[star_idx].pix = 0xFFFF;
		 }
	 }
	 neopixel_show(strip);
	 uint8_t gradient = rand() % 100;
	 gradient = gradient < 25? 25: gradient;
	 for (uint8_t i = 0; i < 50; i++ ) {
		 for( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++){
			 if( star_buffer[star_idx].pix < 0xFFFF) {
				 neopixel_incPixelHue(strip, star_buffer[star_idx] );
				 neopixel_show(strip);
			 }
		 }
		 delay_ms(gradient);
	 }
	 delay_ms(150);
	 for( uint8_t i = 0; i < 51; i++ ) {
		 for( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++){
			 if( star_buffer[star_idx].pix < 0xFFFF){
				 neopixel_decrPixelHue(strip, star_buffer[star_idx]);
				 neopixel_show(strip);
			 }
		 }
		 delay_ms(gradient);
	 }
 }

 #endif