/*
 * attiny1614_sr595.h
 *
 * Created: 13/02/2018 08:50:22
 *  Author: Steven
 */ 


#ifndef ATTINY1614_SR595_H_
#define ATTINY1614_SR595_H_
#include <avr/io.h>

#define F_CPU 20000000UL


#define SR595_PA1 1
#define SR595_PA2 2
#define SR595_PA3 3
#define SR595_PA4 4
#define SR595_PA5 5
#define SR595_PA6 6
#define SR595_PA7 7

/*! The port for the shift register */
#define SR595_PORT VPORTA_OUT

/*! The data pin for the shift register */
#define SR595_SR_PIN SR595_PA1

/*! The clock pin for the shift register */
#define SR595_CLK_PIN SR595_PA2

/*! The latch pin for the shift register */
#define SR595_LATCH_PIN SR595_PA3

/*! Then enable pin for the shift register */
#define SR595_ENABLE SR595_PA4


void sr595_init();

 void sr595_shiftout( uint8_t channel );


#endif /* ATTINY1614_SR595_H_ */