
#ifndef INCLUDE_NEOPIXEL_H
#define INCLUDE_NEOPIXEL_H


#define NeoPin (1 << 1)
#define neopixel_pixels 60

#define neopixel_buffer_size neopixel_pixels * 3

#define NEO_RED 1
#define NEO_GREEN 0
#define NEO_BLUE 2

void neopixel_setPixel(uint8_t pixel, uint8_t red, uint8_t green, uint8_t blue);
void neopixel_show();

#endif 

