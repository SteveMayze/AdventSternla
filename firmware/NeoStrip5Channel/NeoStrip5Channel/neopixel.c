/*!
 * \brief The library for driving the NeoPixels for the ATTiny1614
 *
 * \file neopixel.c
 *
 * Created: 22/12/2017 22:07:00
 * \author Steve Mayze
 * \version 1.0
 */ 
#define F_CPU 20000000UL
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include "neopixel.h"
#include "attiny1614_sr595.h"

/*! The buffer that contains all pixel and colour data */
uint8_t buffer[neopixel_buffer_size];
/*! The pin mask for the output port pin that drives the NeoPixels */
uint8_t pinMask = 0x10; // PA4 NEOPIXEL_ENABLE




/*!
 * \brief a wrapper over the _delay_ms function
 *
 *	This wrapper enables the ms count to be passed in as variable
 *	and not as a integer constant as dictated by the _delay_ms 
 *	function.
 */
void delay_ms(int ms){
	for(int i =0; i < ms; i++){
		_delay_ms(1);
	}
}


void neopixel_init(){
	PORTA.DIR |= (1 << NEOPIXEL_NEOPIN);
	sr595_init();

}


/*!
 * \brief	Sets a pixel with the RGB code
 */
void neopixel_setPixel(uint8_t pixel, uint8_t red, uint8_t green, uint8_t blue)
{
    uint8_t location = pixel * 3;
	buffer[ location + NEO_RED ] = red;
	buffer[ location + NEO_GREEN ] = green;
	buffer[ location + NEO_BLUE ] = blue;
}

/*!
 * \brief	Initialises the buffer with the given colour 
 */
void neopixel_fill(uint8_t red, uint8_t green, uint8_t blue){
   for(int i = 0; i < neopixel_pixels; i++)
   {
      neopixel_setPixel(i, red, green, blue);
   }
}

/*!
 * \brief	Shifts the pixels one pixel in the indicated direction
 */
void neopixel_shift(bool direction){

   if( direction ) {
		for (int i = 0; i < ( neopixel_pixels - 1); i++){
			uint8_t baseLocation = i * 3;
			uint8_t newBaseLocation = (i + 1) * 3;

			buffer[ baseLocation + NEO_RED ] = buffer[ newBaseLocation + NEO_RED ];
			buffer[ baseLocation + NEO_GREEN ] = buffer[newBaseLocation + NEO_GREEN];
			buffer[ baseLocation +NEO_BLUE ] = buffer[newBaseLocation + NEO_BLUE];
		}
		uint8_t lastLocation = (neopixel_pixels -1) *3;
		buffer[lastLocation + NEO_RED] = buffer[NEO_RED];
		buffer[lastLocation + NEO_GREEN] = buffer[NEO_GREEN];
		buffer[lastLocation + NEO_BLUE] = buffer[NEO_BLUE];
	} else {


	    uint8_t firstPixel = 0;
	    buffer[firstPixel + NEO_RED] =  buffer[ LAST_PIXEL + NEO_RED];
	    buffer[firstPixel + NEO_GREEN] = buffer[ LAST_PIXEL + NEO_GREEN];
	    buffer[firstPixel + NEO_BLUE] = buffer[ LAST_PIXEL + NEO_BLUE];

		for (int i = neopixel_pixels -1; i > 0; i--){
			uint8_t  baseLocation= i * 3;
			uint8_t newBaseLocation = ( i - 1) * 3;

			buffer[ baseLocation + NEO_RED ] = buffer[ newBaseLocation + NEO_RED ];
			buffer[ baseLocation + NEO_GREEN ] = buffer[newBaseLocation + NEO_GREEN];
			buffer[ baseLocation +NEO_BLUE ] = buffer[newBaseLocation + NEO_BLUE];
		}
	}
}

/*!
 * \brief Pushes the buffer out to the pixel strip.
 */
void neopixel_show()
{
	volatile uint16_t  i = neopixel_buffer_size; // Loop counter

	volatile uint8_t *port;

	volatile uint8_t *ptr = &buffer[0],   // Pointer to next byte
	b   = *ptr++,   // Current byte value
	hi,             // PORT w/output bit set high
	lo;             // PORT w/output bit set low

	volatile uint8_t bit;

	lo = VPORTA_OUT |  pinMask;
	hi = VPORTA_OUT & ~pinMask;
    bit  = 8;

	port = &VPORTA_OUT;

	VPORTA_OUT = lo;

    asm volatile(
    "neo_start:"						"\n\t"	//	Tick	Pseudo code	
		"st %a[port], %[hi]"			"\n\t"	//	2		PORT = Hi
	    "sbrc %[byte],  7"				"\n\t"	//	1-3		Skip the next operation if bit 7 is clear
		"rjmp do_HI"					"\n\t"	//	0-2		Jump and Do the HI case

	"do_LOW:"							"\n\t"	//			At 3 cycles. For LOW, still need 3 for HI and then 18 LOW
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"st %a[port], %[lo]"			"\n\t"	//	2		PORT = Low (Finish of 6 Hi cycles- start the 18 LOW)
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"rjmp next_bit"					"\n\t"	//	2

	"do_HI:"							"\n\t"	//			At 3 cycles. For HI, still need 9 for HI and then 12 LOW
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"nop"							"\n\t"	//	1
		"st %a[port], %[lo]"			"\n\t"	//	2		PORT = Low (Finish of 16 Hi cycles- start the 9 LOW)
		 "nop"							"\n\t"	//	1
		 "nop"							"\n\t"	//	1
		 "nop"							"\n\t"	//	1
		"rjmp next_bit"					"\n\t"	//	2
		 "nop"							"\n\t"	//	1
	"next_bit:"							"\n\t"	//			This section costs 3 - 5 cycles
		"dec  %[bit]"					"\n\t"	//	1		bit--
		"breq next_byte"				"\n\t"	//	1-2		branch if(bit == 0) (from dec above)
		"rol  %[byte]"					"\n\t"	//	1		b <<= 1 - Roll the byte left one bit.
		"rjmp neo_start"				"\n\t"	//	2		Jump to start for the next bit

	"next_byte:"						"\n\t"	//			This section costs 9 cycles!
		"ldi %[bit], 8"					"\n\t"	// 1		Set bit = 8
		"ld %[byte], %a[ptr]+"			"\n\t"	// 2		Set b = *ptr++
		"st %a[port], %[lo]"			"\n\t"	// 2		PORT = lo
		"sbiw %[count], 1"				"\n\t"	// 2		i--
		"brne neo_start"				"\n"	// 2		if(i != 0) -> (next byte)
    : [port]  "+e" (port),
      [byte]  "+r" (b),
      [bit]   "+r" (bit),
      [count] "+w" (i)
    : [ptr]    "e" (ptr),
      [hi]     "r" (hi),
      [lo]     "r" (lo));

}

 void neopixel_setchannel( uint8_t channel ) {
	sr595_shiftout( channel );
 }

