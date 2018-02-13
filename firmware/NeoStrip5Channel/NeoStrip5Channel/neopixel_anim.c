/*
 * neopixel_anim.c
 *
 * Created: 13/02/2018 09:20:58
 *  Author: Steven
 */ 

 #include <stdlib.h>
 #include "neopixel.h"
 



/*!
 * \brief	Rolls the pixels in a direction, the number of positions.
 * 
 * rolls the pixels one direction or the other the number of positions
 * with an intermediate animation of delay ms. The neopixel_show 
 * function will be called.

*/
void neopixel_anim_pixel_chaser(bool direction, int positions, int delay){
	for( int i = 0; i < positions; i++)
	{
		neopixel_shift(direction);
		neopixel_show();
		delay_ms(delay);
	}
}

/*!
 *	\brief	Intialise the buffer with a "pulsed rainbow" type 
 *			sequence.
 *
 *	The "rainbow" is dived over the 60 pixels. A group of 10 
 *	pixels for each colour group. The "pulse"effect is to have
 *	the middle pixel at the highest hue intensity.
 *
 */
void neopixel_anim_init_rainbow_pulse(uint8_t hue) {
	uint8_t red_color = 0;
	uint8_t green_color = 0;
	uint8_t blue_color = 0;

	int grade = -5;
	int colour = 100;
	int page;
	int grade_factor = hue / 5 ;

	for(int group = 0; group < 6; group++) {
		grade = -5;
		page = group * 10;
		for(int pix = 0; pix < 5; pix++) {
			colour = (hue + (grade * grade_factor));
			grade++;
			switch( group ) {
				case 0:
					red_color = colour;
					green_color = NEO_ALL_OFF;
					blue_color = colour;
					break;
				case 1:
					red_color = colour;
					green_color = NEO_ALL_OFF;
					blue_color = NEO_ALL_OFF;
					break;
				case 2:
					red_color = colour;
					green_color = colour;
					blue_color = NEO_ALL_OFF;
					break;
				case 3:
					red_color = NEO_ALL_OFF;
					green_color = colour;
					blue_color = NEO_ALL_OFF;
					break;
				case 4:
					red_color = NEO_ALL_OFF;
					green_color = colour;
					blue_color = colour;
					break;
				case 5:
					red_color = NEO_ALL_OFF;
					green_color = NEO_ALL_OFF;
					blue_color = colour;
					break;
				default:
					break;
			}
			neopixel_setPixel( page+pix, red_color, green_color, blue_color);
		}
		grade = 0;
		for(int pix = 5; pix < 11; pix++){
			colour = hue + (grade * grade_factor);
			grade--;
			switch( group ){
				case 0:
					red_color = colour;
					green_color = NEO_ALL_OFF;
					blue_color = colour;
					break;
				case 1:
					red_color = colour;
					green_color = NEO_ALL_OFF;
					blue_color = NEO_ALL_OFF;
					break;
				case 2:
					red_color = colour;
					green_color = colour;
					blue_color = NEO_ALL_OFF;
					break;
				case 3:
					red_color = NEO_ALL_OFF;
					green_color = colour;
					blue_color = NEO_ALL_OFF;
					break;
				case 4:
					red_color = NEO_ALL_OFF;
					green_color = colour;
					blue_color = colour;
					break;
				case 5:
					red_color = NEO_ALL_OFF;
					green_color = NEO_ALL_OFF;
					blue_color = colour;
					break;
				default:
					break;
			}
			neopixel_setPixel(page+pix, red_color, green_color, blue_color);
		}
	}
}

/*!
 * \brief	Initialise the pixels with a "rainbow" series.
 *
 *	The colours are divided over the 60 pixels with six colours allocated
 *	to each group of 10 pixels.
 */
void neopixel_anim_init_rainbow(uint8_t hue){
	uint8_t red_color = 0;
	uint8_t green_color = 0;
	uint8_t blue_color = 0;

	for (int i = 0; i < neopixel_pixels; i++)
	{
		if ( i <= 9) {
			red_color = hue;
			green_color = NEO_ALL_OFF;
			blue_color = hue;
		}
		if ( i >= 10 && i <= 19) {
			red_color = hue;
			green_color = NEO_ALL_OFF;
			blue_color = NEO_ALL_OFF;
		}
		if ( i >= 20 && i <= 29) {
			red_color = hue;
			green_color = hue;
			blue_color = NEO_ALL_OFF;
		}
		if ( i >= 30 && i <= 39) {
			red_color = NEO_ALL_OFF;
			green_color = hue;
			blue_color = NEO_ALL_OFF;
		}
		if ( i >= 40 && i <= 49) {
			red_color = NEO_ALL_OFF;
			green_color = hue;
			blue_color = hue;
		}
		if ( i >= 50 ) {
			red_color = NEO_ALL_OFF;
			green_color = NEO_ALL_OFF;
			blue_color = hue;
		}
		neopixel_setPixel(i, red_color, green_color, blue_color);
	}
}

/*!
 * \brief	Initialise the pixels with a "rainbow" series.
 *
 *	The colours are divided over the 60 pixels with six colours allocated
 *	to each group of 10 pixels.
 */
void neopixel_anim_init_random(uint8_t hue){
	uint8_t red_color = 0;
	uint8_t green_color = 0;
	uint8_t blue_color = 0;

	uint8_t colour_bias = 0; 

	for (int i = 0; i < neopixel_pixels; i++)
	{

	   red_color = rand() % hue;
	   blue_color = rand() % hue;
	   green_color = rand() % hue;

	   colour_bias = rand() % 3;
	   switch(colour_bias){
	   case 1:
			red_color = 0;
			break;
	   case 2:
			green_color = 0;
			break;
	   case 3:
			blue_color = 0;
			break;
	   default:
			red_color = 0;
			green_color = 0;
			blue_color = 0;
			break;
	   }
	   neopixel_setPixel(i, red_color, green_color, blue_color);
	}
}


/*!
 *	\brief	Fills the pixel strip with a colour
 *
 *	The colour is filled based on the direction and with an animation delay.
 *	The neopixel_show will be called.
 */
void neopixel_anim_wipe(uint8_t red, uint8_t green, uint8_t blue, bool direction, int delay){

	uint8_t pixel = ( direction )? neopixel_pixels - 1: 0;
	// uint8_t pixel = neopixel_pixels - 1;
	for(int i = 0; i < neopixel_pixels; i++){
		if( direction ) {
			neopixel_setPixel(pixel, red, green, blue);
			neopixel_show();
			neopixel_shift(direction);
			} else {
			neopixel_setPixel(0, red, green, blue);
			neopixel_setPixel(neopixel_pixels - 1, red, green, blue);
			neopixel_show();
			neopixel_shift(direction);
		}
		delay_ms(delay);

	}
}

/*!
 * \brief The wipe function that will wipe in a "rainbow"
 *
 */
void neopixel_anim_rainbow_wipe(uint8_t hue, bool direction, int delay){

	uint8_t pixel = ( direction )? neopixel_pixels - 1: 0;
	uint8_t red, green, blue;
	red = 0;
	green = 0;
	blue = 0;
	for(int i = 0; i < neopixel_pixels; i++){
		if( direction ) {
			if ( i <= 9) {
				red = hue;
				green = NEO_ALL_OFF;
				blue = hue;
			}
			if ( i >= 10 && i <= 19) {
				red = hue;
				green = NEO_ALL_OFF;
				blue = NEO_ALL_OFF;
			}
			if ( i >= 20 && i <= 29) {
				red = hue;
				green = hue;
				blue = NEO_ALL_OFF;
			}
			if ( i >= 30 && i <= 39) {
				red = NEO_ALL_OFF;
				green = hue;
				blue = NEO_ALL_OFF;
			}
			if ( i >= 40 && i <= 49) {
				red = NEO_ALL_OFF;
				green = hue;
				blue = hue;
			}
			if ( i >= 50 ) {
				red = NEO_ALL_OFF;
				green = NEO_ALL_OFF;
				blue = hue;
			}

			neopixel_setPixel(pixel, red, green, blue);
			neopixel_show();
			neopixel_shift(direction);
		} else {
			if ( i <= 9) {
				red = hue;
				green = NEO_ALL_OFF;
				blue = hue;
			}
			if ( i >= 10 && i <= 19) {
				red = hue;
				green = NEO_ALL_OFF;
				blue = NEO_ALL_OFF;
			}
			if ( i >= 20 && i <= 29) {
				red = hue;
				green = hue;
				blue = NEO_ALL_OFF;
			}
			if ( i >= 30 && i <= 39) {
				red = NEO_ALL_OFF;
				green = hue;
				blue = NEO_ALL_OFF;
			}
			if ( i >= 40 && i <= 49) {
				red = NEO_ALL_OFF;
				green = hue;
				blue = hue;
			}
			if ( i >= 50 ) {
				red = NEO_ALL_OFF;
				green = NEO_ALL_OFF;
				blue = hue;
			}

			neopixel_setPixel(0, red, green, blue);
			neopixel_setPixel(neopixel_pixels - 1, red, green, blue);
			neopixel_show();
			neopixel_shift(direction);
		}
		delay_ms(delay);

	}
}

