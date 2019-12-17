/*
 * neopixel_anim.h
 *
 * Created: 22/12/2018 15:46:02
 *  Author: Steven
 */ 


#ifndef NEOPIXEL_ANIM_H_
#define NEOPIXEL_ANIM_H_

#define _NEOPIXEL_ANIM_NEW

#define MAX_STARS 50
#define NEO_ANIM_CYCLES NEO_HUE_ADJ * 100
#define NEO_ANIM_MAX_GRADIENT 10
#define NEO_ANIM_MIN_GRADIENT 2

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


volatile neopixel_anim_star_t star_buffer[MAX_STARS];

volatile uint8_t buffer[neopixel_buffer_size];

void neo_anim_stars();

#endif /* NEOPIXEL_ANIM_H_ */