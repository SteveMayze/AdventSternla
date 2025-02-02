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
 bool neo_anim_stars(bool finish_up) {
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

				// If they are all 0x00, then force at least one colour to a value.
				if ( star_buffer[star_idx].pixel.red == 0x00 && star_buffer[star_idx].pixel.green == 0x00 && star_buffer[star_idx].pixel.blue == 0x00) {
					star_buffer[star_idx].state.status_bits.active = false;
				}
			}
		}
		// neopixel_show(buffer);
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
			// neopixel_show(buffer);
		}
	}
	neopixel_show(buffer);
	uint8_t gradient = rand() % NEO_ANIM_MAX_GRADIENT;
	gradient = gradient < NEO_ANIM_MIN_GRADIENT? NEO_ANIM_MIN_GRADIENT: gradient;
	delay_ms(gradient);
	return neo_anim_any_active();
 }


 #endif


 void commet(void){

	 neopixel_fill(buffer, NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	 neopixel_show(buffer);

	 // Set the pixel 0 to White and let the droplet gather some weight
	 // neopixel_setchannel(channel_mask);
	 uint8_t hue = HI_HUE;
	 uint8_t hue_decr = HI_HUE / COMMET_SIZE;
	 for (uint8_t i = 0; i < COMMET_SIZE; i++){
		 neopixel_setPixel(buffer, 0, hue, hue, hue);
		 neopixel_show(buffer);
		 delay_ms(15);
		 neopixel_shift(buffer, true);
		 hue = hue - hue_decr;
	 }

	 // Now let the pixels _fall_
	 for(int j=0; j < NEOPIXELS_SIZE; j++){
		 neopixel_show(buffer);
		 neopixel_shift(buffer, true);
		 delay_ms(15);
		 if (j > NEOPIXELS_SIZE - COMMET_SIZE*2 ) {
			 neopixel_setPixel(buffer, 0, NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
		 }
	 }
 }

