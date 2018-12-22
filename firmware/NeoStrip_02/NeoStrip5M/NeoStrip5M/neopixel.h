
#ifndef INCLUDE_NEOPIXEL_H
#define INCLUDE_NEOPIXEL_H
#include <stdbool.h>


typedef struct {
	uint16_t pix;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} pixel_type;


#define NEOPIXEL_NEOPIN 1

/*! The output port pin for driving the NeoPixel strip */
#define NeoPin (1 << 1)
/*! The number of NeoPixels */
#define NEOPIXELS_SIZE 150

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

void delay_ms(int ms);

void neopixel_init();

/*!
 * \brief	Sets a pixel with the RGB code
 */
void neopixel_setPixel(uint8_t strip[], uint8_t pixel, uint8_t red, uint8_t green, uint8_t blue);

/*!
 * \brief	Shifts the pixels one pixel in the indicated direction
 */
void neopixel_shift(uint8_t strip[],  bool direction );

/*!
 * \brief	Initialises the buffer with the given colour 
 */
void neopixel_fill(uint8_t strip[], uint8_t red, uint8_t green, uint8_t blue);

/*!
 * \brief	Increases the pixel hue to a maximum of 0xFF based on the values contained in the pixel struct.
 */
void neopixel_incPixelHue(uint8_t strip[], pixel_type pixel);

/*!
 * \brief	Decreases the pixel hue to zero based on the values contained in the pixel struct.
 */
void neopixel_decrPixelHue(uint8_t strip[], pixel_type pixel);

/*!
 * \brief Pushes the buffer out to the pixel strip.
 */
void neopixel_show(uint8_t strip[]);

#endif 

