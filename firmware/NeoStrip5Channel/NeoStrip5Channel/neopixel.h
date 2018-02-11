
#ifndef INCLUDE_NEOPIXEL_H
#define INCLUDE_NEOPIXEL_H

/*! The port pin PA1 */
#define NEOPIXEL_PA1 1
/*! The port pin PA2 */
#define NEOPIXEL_PA2 2
/*! The port pin PA3 */
#define NEOPIXEL_PA3 3
/*! The port pin PA4 */
#define NEOPIXEL_PA4 4
/*! The port pin PA5 */
#define NEOPIXEL_PA5 5
/*! The port pin PA6 */
#define NEOPIXEL_PA6 6
/*! The port pin PA7 */
#define NEOPIXEL_PA7 7

/*! The data pin for the shift register */
#define NEOPIXEL_SR_PIN NEOPIXEL_PA1

/*! The clock pin for the shift register */
#define NEOPIXEL_CLK_PIN NEOPIXEL_PA2

/*! The latch pin for the shift register */
#define NEOPIXEL_LATCH_PIN NEOPIXEL_PA3

/*! Then enable pin for the shift register */
#define NEOPIXEL_ENABLE NEOPIXEL_PA4

/*! The port for the neopixel and shift register */
#define NEOPIXEL_PORT VPORTA_OUT

/*! The output port pin for driving the NeoPixel strip */
#define NEOPIXEL_NEOPIN NEOPIXEL_ENABLE

/*! The number of NeoPixels */
#define neopixel_pixels 60

/*! The NeoPixel buffer size */
#define neopixel_buffer_size neopixel_pixels * 3
/*! The location of the first pixel */
#define FIRST_PIXEL 0
/*! The location of the last pixel */
#define LAST_PIXEL ((neopixel_pixels-1) *3)

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

/*!
 * \brief	Sets a pixel with the RGB code
 */
void neopixel_setPixel(uint8_t pixel, uint8_t red, uint8_t green, uint8_t blue);

/*!
 * \brief	Shifts the pixels one pixel in the indicated direction
 */
void neopixel_shift( bool direction );

/*!
 * \brief	Initialises the buffer with the given colour 
 */
void neopixel_fill(uint8_t red, uint8_t green, uint8_t blue);

/*!
 * \brief Pushes the buffer out to the pixel strip.
 */
void neopixel_show();

/*!
 * \brief Sets the channel for the stip to use. The bits in the 
 * binary integer will each represent a channel.
 */
 void neopixel_setchannel( uint8_t channel );

#endif 

