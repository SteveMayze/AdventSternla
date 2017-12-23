/*
 * neopixel.c
 *
 * Created: 22/12/2017 22:07:00
 *  Author: Steve
 */ 

#include <avr/io.h>
#include "neopixel.h"

#define _NEO_SHOW_SLOW

#define BIT_TEST(byte, bitCount) (((byte >> bitCount) & 0x01) << bitCount)

uint8_t buffer[neopixel_buffer_size];
uint8_t pinMask = 0x02;

void neopixel_setPixel(uint8_t pixel, uint8_t red, uint8_t green, uint8_t blue)
{
    uint8_t location = pixel * 3;
	buffer[ location + red ] = red;
	buffer[ location + green ] = green;
	buffer[ location + blue ] = blue;

}

#ifdef _NEO_SHOW_SLOW
void neopixel_show()
{
	volatile uint16_t  i   = neopixel_buffer_size; // Loop counter

	volatile uint8_t *port;

	volatile uint8_t *ptr = &buffer[0],   // Pointer to next byte
	b   = *ptr++,   // Current byte value
	hi,             // PORT w/output bit set high
	lo;             // PORT w/output bit set low

	volatile uint8_t next, bit;

	hi = VPORTA_OUT |  pinMask;
	lo = VPORTA_OUT & ~pinMask;
    next = lo;
    bit  = 8;

	port = &VPORTA_OUT;

    asm volatile(
    "head20:"                   "\n\t" // Clk  Pseudocode    (T =  0)
    "st   %a[port],  %[hi]"    "\n\t" // 2    PORT = hi     (T =  2)
    "sbrc %[byte],  7"         "\n\t" // 1-2  if(b & 128)
    "mov  %[next], %[hi]"     "\n\t" // 0-1   next = hi    (T =  4)
    "dec  %[bit]"              "\n\t" // 1    bit--         (T =  5)
    "st   %a[port],  %[next]"  "\n\t" // 2    PORT = next   (T =  7)
    "mov  %[next] ,  %[lo]"    "\n\t" // 1    next = lo     (T =  8)
    "breq nextbyte20"          "\n\t" // 1-2  if(bit == 0) (from dec above)
    "rol  %[byte]"             "\n\t" // 1    b <<= 1       (T = 10)
    "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 12)
    "nop"                      "\n\t" // 1    nop           (T = 13)
    "nop"                      "\n\t" // 1    nop           (T = 13)
    "nop"                      "\n\t" // 1    nop           (T = 13)
    "st   %a[port],  %[lo]"    "\n\t" // 2    PORT = lo     (T = 15)
    "nop"                      "\n\t" // 1    nop           (T = 16)
    "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 18)
    "rjmp head20"              "\n\t" // 2    -> head20 (next bit out)
    "nextbyte20:"               "\n\t" //                    (T = 10)
    "ldi  %[bit]  ,  8"        "\n\t" // 1    bit = 8       (T = 11)
    "ld   %[byte] ,  %a[ptr]+" "\n\t" // 2    b = *ptr++    (T = 13)
    "st   %a[port], %[lo]"     "\n\t" // 2    PORT = lo     (T = 15)
    "nop"                      "\n\t" // 1    nop           (T = 16)
    "sbiw %[count], 1"         "\n\t" // 2    i--           (T = 18)
    "brne head20"             "\n"   // 2    if(i != 0) -> (next byte)
    : [port]  "+e" (port),
    [byte]  "+r" (b),
    [bit]   "+r" (bit),
    [next]  "+r" (next),
    [count] "+w" (i)
    : [ptr]    "e" (ptr),
    [hi]     "r" (lo),
    [lo]     "r" (hi));


/*
    asm volatile(
    "head20:"                   "\n\t" // Clk  Pseudocode    (T =  0)
    "st   %a[port],  %[hi]"    "\n\t" // 2    PORT = hi     (T =  2)
    "sbrc %[byte],  7"         "\n\t" // 1-2  if(b & 128)
    "mov  %[next], %[hi]"     "\n\t" // 0-1   next = hi    (T =  4)
    "dec  %[bit]"              "\n\t" // 1    bit--         (T =  5)
    "st   %a[port],  %[next]"  "\n\t" // 2    PORT = next   (T =  7)
    "mov  %[next] ,  %[lo]"    "\n\t" // 1    next = lo     (T =  8)
    "breq nextbyte20"          "\n\t" // 1-2  if(bit == 0) (from dec above)
    "rol  %[byte]"             "\n\t" // 1    b <<= 1       (T = 10)
    "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 12)
    "nop"                      "\n\t" // 1    nop           (T = 13)
    "st   %a[port],  %[lo]"    "\n\t" // 2    PORT = lo     (T = 15)
    "nop"                      "\n\t" // 1    nop           (T = 16)
    "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 18)
    "rjmp head20"              "\n\t" // 2    -> head20 (next bit out)
    "nextbyte20:"               "\n\t" //                    (T = 10)
    "ldi  %[bit]  ,  8"        "\n\t" // 1    bit = 8       (T = 11)
    "ld   %[byte] ,  %a[ptr]+" "\n\t" // 2    b = *ptr++    (T = 13)
    "st   %a[port], %[lo]"     "\n\t" // 2    PORT = lo     (T = 15)
    "nop"                      "\n\t" // 1    nop           (T = 16)
    "sbiw %[count], 1"         "\n\t" // 2    i--           (T = 18)
    "brne head20"             "\n"   // 2    if(i != 0) -> (next byte)
    : [port]  "+e" (port),
    [byte]  "+r" (b),
    [bit]   "+r" (bit),
    [next]  "+r" (next),
    [count] "+w" (i)
    : [ptr]    "e" (ptr),
    [hi]     "r" (hi),
    [lo]     "r" (lo));
*/



}
#else
void neopixel_show()
{

    volatile uint16_t  i   = neopixel_buffer_size; // Loop counter

    volatile uint8_t *ptr = &buffer[0],   // Pointer to next byte
		             b   = *ptr++,   // Current byte value
		             hi,             // PORT w/output bit set high
		             lo;             // PORT w/output bit set low
    //volatile uint8_t *port;         // Output PORT register

    volatile uint8_t n1, n2 = 0;  // First, next bits out

    // Squeezing an 800 KHz stream out of an 8 MHz chip requires code
    // specific to each PORT register.

    // 10 instruction clocks per bit: HHxxxxxLLL
    // OUT instructions:              ^ ^    ^   (T=0,2,7)

    // PORTA OUTPUT ----------------------------------------------------

	hi = PORTA.OUT |  pinMask;
	lo = PORTA.OUT & ~pinMask;
	//port = &PORTA.OUT;
	n1 = lo;
	if(b & 0x80) n1 = hi;
	// Dirty trick: RJMPs proceeding to the next instruction are used
	// to delay two clock cycles in one instruction word (rather than
	// using two NOPs).  This was necessary in order to squeeze the
    // loop down to exactly 64 words -- the maximum possible for a
    // relative branch
    asm volatile (
	    "headD:"                   "\n\t" // Clk  Pseudocode
	    // Bit 7:
	    "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
	    "mov  %[n2]   , %[lo]"    "\n\t" // 1    n2   = lo
	    "out  %[port] , %[n1]"    "\n\t" // 1    PORT = n1
	    "rjmp .+0"                "\n\t" // 2    nop nop
	    "sbrc %[byte] , 6"        "\n\t" // 1-2  if(b & 0x40)
	    "mov %[n2]   , %[hi]"    "\n\t" // 0-1   n2 = hi
	    "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
	    "rjmp .+0"                "\n\t" // 2    nop nop
	    // Bit 6:
	    "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
	   "mov  %[n1]   , %[lo]"    "\n\t" // 1    n1   = lo
	    "out  %[port] , %[n2]"    "\n\t" // 1    PORT = n2
	    "rjmp .+0"                "\n\t" // 2    nop nop
	    "sbrc %[byte] , 5"        "\n\t" // 1-2  if(b & 0x20)
	    "mov %[n1]   , %[hi]"    "\n\t" // 0-1   n1 = hi
	    "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
	    "rjmp .+0"                "\n\t" // 2    nop nop
	    // Bit 5:
	    "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
	    "mov  %[n2]   , %[lo]"    "\n\t" // 1    n2   = lo
	    "out  %[port] , %[n1]"    "\n\t" // 1    PORT = n1
	    "rjmp .+0"                "\n\t" // 2    nop nop
	    "sbrc %[byte] , 4"        "\n\t" // 1-2  if(b & 0x10)
	    "mov %[n2]   , %[hi]"    "\n\t" // 0-1   n2 = hi
	    "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
	    "rjmp .+0"                "\n\t" // 2    nop nop
	    // Bit 4:
	    "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
	    "mov  %[n1]   , %[lo]"    "\n\t" // 1    n1   = lo
	    "out  %[port] , %[n2]"    "\n\t" // 1    PORT = n2
	    "rjmp .+0"                "\n\t" // 2    nop nop
	    "sbrc %[byte] , 3"        "\n\t" // 1-2  if(b & 0x08)
	      "mov %[n1]   , %[hi]"    "\n\t" // 0-1   n1 = hi
	      "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
	      "rjmp .+0"                "\n\t" // 2    nop nop
	      // Bit 3:
	      "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
	      "mov  %[n2]   , %[lo]"    "\n\t" // 1    n2   = lo
	      "out  %[port] , %[n1]"    "\n\t" // 1    PORT = n1
	      "rjmp .+0"                "\n\t" // 2    nop nop
	      "sbrc %[byte] , 2"        "\n\t" // 1-2  if(b & 0x04)
	      "mov %[n2]   , %[hi]"    "\n\t" // 0-1   n2 = hi
	      "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
	      "rjmp .+0"                "\n\t" // 2    nop nop
	      // Bit 2:
	      "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
	      "mov  %[n1]   , %[lo]"    "\n\t" // 1    n1   = lo
	      "out  %[port] , %[n2]"    "\n\t" // 1    PORT = n2
	      "rjmp .+0"                "\n\t" // 2    nop nop
	      "sbrc %[byte] , 1"        "\n\t" // 1-2  if(b & 0x02)
	      "mov %[n1]   , %[hi]"    "\n\t" // 0-1   n1 = hi
	      "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
	      "rjmp .+0"                "\n\t" // 2    nop nop
	      // Bit 1:
	      "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
	      "mov  %[n2]   , %[lo]"    "\n\t" // 1    n2   = lo
	      "out  %[port] , %[n1]"    "\n\t" // 1    PORT = n1
	      "rjmp .+0"                "\n\t" // 2    nop nop
	      "sbrc %[byte] , 0"        "\n\t" // 1-2  if(b & 0x01)
	      "mov %[n2]   , %[hi]"    "\n\t" // 0-1   n2 = hi
	      "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
	      "sbiw %[count], 1"        "\n\t" // 2    i-- (don't act on Z flag yet)
	      // Bit 0:
	      "out  %[port] , %[hi]"    "\n\t" // 1    PORT = hi
	      "mov  %[n1]   , %[lo]"    "\n\t" // 1    n1   = lo
	      "out  %[port] , %[n2]"    "\n\t" // 1    PORT = n2
	      "ld   %[byte] , %a[ptr]+" "\n\t" // 2    b = *ptr++
	      "sbrc %[byte] , 7"        "\n\t" // 1-2  if(b & 0x80)
	      "mov %[n1]   , %[hi]"    "\n\t" // 0-1   n1 = hi
	      "out  %[port] , %[lo]"    "\n\t" // 1    PORT = lo
	      "brne headD"              "\n"   // 2    while(i) (Z flag set above)
	      : [byte]  "+r" (b),
	      [n1]    "+r" (n1),
	      [n2]    "+r" (n2),
	      [count] "+w" (i)
	      : [port]   "I" (_SFR_IO_ADDR(VPORTA_OUT)),
	      [ptr]    "e" (ptr),
	      [hi]     "r" (hi),
	      [lo]     "r" (lo)
		  );
}
#endif
