
#ifndef INCLUDE_NEOPIXEL_H
#define INCLUDE_NEOPIXEL_H


#define NeoPin (1 << 1)
#define neopixel_pixels 60

#define neopixel_buffer_size neopixel_pixels * 3
#define FIRST_PIXEL 0
#define LAST_PIXEL ((neopixel_pixels-1) *3)

#define NEO_RED 1
#define NEO_GREEN 0
#define NEO_BLUE 2



#define NEO_ALL_ON 0xFF
#define NEO_ALL_OFF 0x00

/*!
	\brief	Sets a pixel with the RGB code
 */
void neopixel_setPixel(uint8_t pixel, uint8_t red, uint8_t green, uint8_t blue);

/*!
	\brief	Shifts the pixels one pixel in the indicated direction
 */
void neopixel_shift( bool direction );

/*!
	\brief	Initialises the buffer with the given colour 
 */
void neopixel_fill(uint8_t red, uint8_t green, uint8_t blue);

/*!
	\brief Pushes the buffer out to the pixel strip.
 */
void neopixel_show();

#endif 

