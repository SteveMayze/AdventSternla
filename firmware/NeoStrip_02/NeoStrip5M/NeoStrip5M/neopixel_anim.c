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
 
 #define MAX_STARS 25
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
			 star_buffer[star_idx].red = rand() % 0x0A;
			 star_buffer[star_idx].green = rand() % 0x0A;
			 star_buffer[star_idx].blue = rand() % 0x0A;
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

