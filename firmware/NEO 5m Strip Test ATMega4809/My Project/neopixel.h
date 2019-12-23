
#ifndef INCLUDE_NEOPIXEL_H
#define INCLUDE_NEOPIXEL_H
#include <stdbool.h>

 #define NEO_LENGTH_LONG

typedef struct {
	/*! The pixel number along the strip. This identifies the individual LED */
	uint16_t pix;
	/*! The red colour value */
	uint8_t red;
	/*! The green colour value */
	uint8_t green;
	/*! The blue colour value */
	uint8_t blue;
} pixel_type;


#define NEOPIXEL_NEOPIN 1

/*! The output port pin for driving the NeoPixel strip */
#define NeoPin (1 << 1)
/*! The number of NeoPixels */


#ifdef NEO_LENGTH_LONG
#define NEOPIXELS_SIZE 150
#endif

#ifdef NEO_LENGTH_SHORT
#define NEOPIXELS_SIZE 60
#endif

/*! The NeoPixel buffer size */
#define neopixel_buffer_size NEOPIXELS_SIZE * 3
/*! The location of the first pixel */
#define FIRST_PIXEL 0
/*! The location of the last pixel */
#define LAST_PIXEL ((NEOPIXELS_SIZE-1) *3)

/*! The relative location of the RED colour data */
#define NEO_RED 1
/*! The relative location of the GREEN colour data */
#define NEO_GREEN 0
/*! The relative location of the BLUE colour data */
#define NEO_BLUE 2


/*! The highest intensity for a pixel colour i.e. ON*/
#define NEO_ALL_ON 0xFF
/*! The lowest intensity for a pixel colour i.e OFF */
#define NEO_ALL_OFF 0x00

#define NEO_HUE_ADJ 0x08
#define NEO_HUE_MAX_LIMIT 0xFF - NEO_HUE_ADJ
#define NEO_HUE_MIN_LIMIT NEO_HUE_ADJ

void delay_ms(int ms);

void neopixel_init();

/*!
 * \brief	Sets a pixel with the RGB code
 */
void neopixel_setPixel(volatile uint8_t strip[], uint8_t pixel, uint8_t red, uint8_t green, uint8_t blue);

/*!
 * \brief	Shifts the pixels one pixel in the indicated direction
 */
void neopixel_shift(volatile uint8_t strip[],  bool direction );

/*!
 * \brief	Initialises the buffer with the given colour 
 */
void neopixel_fill(volatile uint8_t strip[], uint8_t red, uint8_t green, uint8_t blue);

/*!
 * \brief	Increases the pixel hue to a maximum of 0xFF based on the values contained in the pixel struct.
 */
void neopixel_incPixelHue(volatile uint8_t strip[], pixel_type pixel);

/*!
 * \brief	Increases the pixel hue to a maximum of 0xFF based on the values contained in the pixel struct.
 */
bool neopixel_incPixelHue_with_limit(volatile uint8_t strip[], pixel_type pixel);

/*!
 * \brief	Decreases the pixel hue to zero based on the values contained in the pixel struct.
 */
void neopixel_decrPixelHue(volatile uint8_t strip[], pixel_type pixel);

/*!
 * \brief	Decreases the pixel hue to zero based on the values contained in the pixel struct.
 */
bool neopixel_decrPixelHue_with_limit(volatile uint8_t strip[], pixel_type pixel);

/*!
 * \brief Pushes the buffer out to the pixel strip.
 */
void neopixel_show(volatile uint8_t strip[]);

#endif 

