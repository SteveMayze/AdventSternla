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

 #ifdef _NEOPIXEL_ANIM_NEW

 /*!
  * \brief Clears the star_buffer. This does not affect the actual pixel location,
  *       just the state and the colour
  */
 void neo_anim_clear(void) {
	for ( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
		star_buffer[star_idx].state.status_bits.active = false;
		star_buffer[star_idx].pixel.red = 0x00;
		star_buffer[star_idx].pixel.green = 0x00;
		star_buffer[star_idx].pixel.blue = 0x00;
		neopixel_setPixel(buffer, star_buffer[star_idx].pixel.pix, 0x00, 0x00, 0x00);
	}
 }

 /*!
  * \brief Returns true if any of the stars in the star_buffer are active.
  */
 bool neo_anim_any_active(void) {
	for( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
		if ( star_buffer[star_idx].state.status_bits.active ) {
			return true;
		}
	}
	return false;
 }

 /*!
  * \brief Checks the star_buffer for the existence of the pixel and if it is currently active.
  * an inactive pixel will be deemed as available to be used.
  */
 bool buffer_contians( uint8_t pix ){
	bool result = false;
	for( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
		if( star_buffer[star_idx].state.status_bits.active && star_buffer[star_idx].pixel.pix == pix ){
			result = true;
			break;
		}
	}
	return result;
 }

 /*!
  * Returns the next available pixel number based on the rand() function
  */
 uint8_t get_next_pixel_from_star_buffer() {
	 uint8_t next_pix = rand() % NEOPIXELS_SIZE;
	 while ( buffer_contians( next_pix )) {
		 next_pix = rand() % NEOPIXELS_SIZE;
	 }
	 return next_pix;
 }

/*!
 * \brief Returns the count of active pixels in the star_buffer
 */
uint8_t neo_count_actives(void) {
	uint8_t actives = 0;
	for ( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
		if ( star_buffer[star_idx].state.status_bits.active) {
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
 void neo_anim_stars(void) {
	// Clear the buffer
	neo_anim_clear();
	// uint16_t cycle = 0;
	bool finish_up = false;
	bool all_active = true;
	while ( all_active ) {
	// Iterate through each star definition
		if ( !finish_up ) {
			for ( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++) {
				if (star_buffer[star_idx].state.status_bits.active != true) {
					// We have decided to activate this. Enable this and set a base colour.
					star_buffer[star_idx].pixel.pix = get_next_pixel_from_star_buffer();
					star_buffer[star_idx].state.status_bits.active = true;
					star_buffer[star_idx].state.status_bits.ramp_up = true;
					star_buffer[star_idx].pixel.red = rand() % NEO_HUE_ADJ;
					star_buffer[star_idx].pixel.green = rand() % NEO_HUE_ADJ;
					star_buffer[star_idx].pixel.blue = rand() % NEO_HUE_ADJ;
				}
			}
			neopixel_show(buffer);
		} 
		bool limit_reached = false;
		for( uint8_t star_idx = 0; star_idx < MAX_STARS; star_idx++){
			if ( star_buffer[star_idx].state.status_bits.active ) {
				if( star_buffer[star_idx].state.status_bits.ramp_up ) {
					limit_reached = neopixel_incPixelHue_with_limit(buffer, star_buffer[star_idx].pixel );
					star_buffer[star_idx].state.status_bits.ramp_up ^= limit_reached;
				} else {
					limit_reached = neopixel_decrPixelHue_with_limit(buffer, star_buffer[star_idx].pixel );
					if ( limit_reached ){
						star_buffer[star_idx].state.status_bits.active = false;
						star_buffer[star_idx].pixel.red = 0x00;
						star_buffer[star_idx].pixel.green = 0x00;
						star_buffer[star_idx].pixel.blue = 0x00;
						neopixel_setPixel(buffer, star_buffer[star_idx].pixel.pix, 0x00, 0x00, 0x00);
					}
				}
				neopixel_show(buffer);
			}
		}
		uint8_t gradient = rand() % NEO_ANIM_MAX_GRADIENT;
		gradient = gradient < NEO_ANIM_MIN_GRADIENT? NEO_ANIM_MIN_GRADIENT: gradient;
		delay_ms(gradient);
// 		cycle++;
// 		if( cycle > NEO_ANIM_CYCLES ) {
// 			finish_up = true;
// 			cycle = 0;
// 		}
// 		all_active = neo_anim_any_active();
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