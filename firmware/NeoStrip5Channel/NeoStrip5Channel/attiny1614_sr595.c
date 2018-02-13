/*
 * ATTINY1614_SR74HC595.c
 *
 * Created: 13/02/2018 08:49:38
 *  Author: Steven
 */ 
 #include <avr/io.h>
 #include "attiny1614_sr595.h"
 #include <util/delay.h>

#define SR595_CHANNEL_HI() ( SR595_PORT |= (1 << SR595_SR_PIN ))
#define SR595_CHANNEL_LO() (SR595_PORT &= (~(1 << SR595_SR_PIN )))


void sr595_init(){
	PORTA.DIR |= (1 << SR595_SR_PIN) | (1 << SR595_CLK_PIN) | (1 << SR595_LATCH_PIN);
	SR595_PORT  |= (1<<SR595_LATCH_PIN);
	SR595_PORT &= (~(1<<SR595_CLK_PIN));
	SR595_PORT &= (~(1<<SR595_SR_PIN));
}

/*!
 * \brief sends a clock pulse to the shift register
 */
void sr595_pulse(){
   SR595_PORT |= ( 1 << SR595_CLK_PIN );
   _delay_us(10);
   SR595_PORT &= (~(1 << SR595_CLK_PIN));
   _delay_us(10);
}

void sr595_latch(){
   SR595_PORT |= (1<<SR595_LATCH_PIN);
   _delay_us(10);
   SR595_PORT &= (~(1<< SR595_LATCH_PIN));
   _delay_us(10);
   
}

 void sr595_shiftout( uint8_t channel ) {
    SR595_PORT &= (~(1<<SR595_CLK_PIN));
	SR595_CHANNEL_LO();
    for( uint8_t i=0; i<8; i++){
		if( channel & 0b10000000 ) {
			SR595_CHANNEL_HI();
		} else {
			SR595_CHANNEL_LO();
		}
		sr595_pulse();
		channel = channel << 1;
	}
   SR595_PORT &= (~(1<<SR595_CLK_PIN));
   sr595_latch();
 }

