/*
 * neopixel_anim.h
 *
 * Created: 13/02/2018 09:20:39
 *  Author: Steven
 */ 


#ifndef NEOPIXEL_ANIM_H_
#define NEOPIXEL_ANIM_H_


void neopixel_anim_wipe(uint8_t red, uint8_t green, uint8_t blue, bool direction, int delay);

void neopixel_anim_rainbow_wipe(uint8_t hue, bool direction, int delay);

void neopixel_anim_init_rainbow_pulse(uint8_t hue);

void neopixel_anim_pixel_chaser(bool direction, int positions, int delay);


#endif /* NEOPIXEL_ANIM_H_ */