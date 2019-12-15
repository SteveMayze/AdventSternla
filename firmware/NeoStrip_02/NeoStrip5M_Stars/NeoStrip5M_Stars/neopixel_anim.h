/*
 * neopixel_anim.h
 *
 * Created: 22/12/2018 15:46:02
 *  Author: Steven
 */ 


#ifndef NEOPIXEL_ANIM_H_
#define NEOPIXEL_ANIM_H_

#define _NEOPIXEL_ANIM_NEW

#define MAX_STARS 25
#define NEO_ANIM_CYCLES NEO_HUE_ADJ * 100
#define NEO_ANIM_MAX_GRADIENT 10

uint8_t buffer[neopixel_buffer_size];

void neo_anim_stars();

#endif /* NEOPIXEL_ANIM_H_ */