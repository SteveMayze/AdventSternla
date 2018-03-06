/*
 * NeoStrip5Channel_plus.c
 *
 * Created: 13/02/2018 09:46:43
 * Author : Steven
 */ 

#include <avr/io.h>
#include "neopixel.h"
#include "neopixel_anim.h"

/*! The setting for the CLKCTRL.MCLKCTRLB register */
#define _MAIN_CLOCK 0x00

#define BASE_HUE ((uint8_t) 0x03)

uint8_t buffer[5][neopixel_buffer_size];

void barber_pole(bool direction){

	uint8_t c1[] = { 0x04, 0x00, 0x00 };
	uint8_t c2[] = { 0x00, 0x02, 0x00 };

	neopixel_anim_init_bicolor(buffer[0], c1, c2);
	neopixel_anim_init_bicolor(buffer[1], c1, c2);
	neopixel_anim_init_bicolor(buffer[2], c1, c2);
	neopixel_anim_init_bicolor(buffer[3], c1, c2);
	neopixel_anim_init_bicolor(buffer[4], c1, c2);

	for(uint8_t i=0; i<2; i++){
		neopixel_shift(buffer[1], direction);
		neopixel_shift(buffer[2], direction);
		neopixel_shift(buffer[3], direction);
		neopixel_shift(buffer[4], direction);
	}

	for(uint8_t i=0; i<2; i++){
		neopixel_shift(buffer[2], direction);
		neopixel_shift(buffer[3], direction);
		neopixel_shift(buffer[4], direction);
	}

	for(uint8_t i=0; i<2; i++){
		neopixel_shift(buffer[3], direction);
		neopixel_shift(buffer[4], direction);
	}

	for(uint8_t i=0; i<2; i++){
		neopixel_shift(buffer[4], direction);
	}

	for (uint8_t i = 0; i < 120; i++) {

		neopixel_setchannel((uint8_t)0b00000001);
		neopixel_show(buffer[0]);

		neopixel_setchannel((uint8_t)0b00000010);
		neopixel_show(buffer[1]);

		neopixel_setchannel((uint8_t)0b00000100);
		neopixel_show(buffer[2]);

		neopixel_setchannel((uint8_t)0b00001000);
		neopixel_show(buffer[3]);

		neopixel_setchannel((uint8_t)0b00010000);
		neopixel_show(buffer[4]);

		neopixel_shift(buffer[0], direction);
		neopixel_shift(buffer[1], direction);
		neopixel_shift(buffer[2], direction);
		neopixel_shift(buffer[3], direction);
		neopixel_shift(buffer[4], direction);

		delay_ms(50);
	}
}


void chevron(bool direction){

	uint8_t c1[] = { 0x04, 0x04, 0x04 };
	uint8_t c2[] = { 0x03, 0x00, 0x00 };

	neopixel_anim_init_bicolor(buffer[0], c1, c2);
	neopixel_anim_init_bicolor(buffer[1], c1, c2);
	neopixel_anim_init_bicolor(buffer[2], c1, c2);

	for(uint8_t i=0; i<2; i++){
		neopixel_shift(buffer[1], direction);
		neopixel_shift(buffer[2], direction);
	}

	for(uint8_t i=0; i<2; i++){
		neopixel_shift(buffer[2], direction);
	}

	for (uint8_t i = 0; i < 120; i++) {

		neopixel_setchannel((uint8_t)0b00010001);
		neopixel_show(buffer[0]);

		neopixel_setchannel((uint8_t)0b00001010);
		neopixel_show(buffer[1]);

		neopixel_setchannel((uint8_t)0b00000100);
		neopixel_show(buffer[2]);

		neopixel_shift(buffer[0], direction);
		neopixel_shift(buffer[1], direction);
		neopixel_shift(buffer[2], direction);

		delay_ms(50);
	}
}




void colour_shuffle(void){

   	neopixel_fill(buffer[0], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
   	neopixel_fill(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF);
   	neopixel_fill(buffer[2], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE);

	for (int i = 0; i < 5; i++){
		neopixel_setchannel((uint8_t)0b00010101);
		neopixel_show(buffer[0]);
		neopixel_setchannel((uint8_t)0b00001010);
		neopixel_show(buffer[1]);

		delay_ms(500);

		neopixel_setchannel((uint8_t)0b00010101);
		neopixel_show(buffer[1]);
		neopixel_setchannel((uint8_t)0b00001010);
		neopixel_show(buffer[2]);

		delay_ms(500);
		neopixel_setchannel((uint8_t)0b00010101);
		neopixel_show(buffer[2]);
		neopixel_setchannel((uint8_t)0b00001010);
		neopixel_show(buffer[0]);

		delay_ms(500);


	}
}





void worm(void){

   	neopixel_fill(buffer[0], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
   	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00011111);
	neopixel_show(buffer[0]);

	neopixel_setchannel((uint8_t)0b00000001);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);

   	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000010);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, false, 10);

   	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);

   	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00001000);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, false, 10);

   	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00010000);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);

	
	neopixel_setchannel((uint8_t)0b00000001);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, true, 10);

	neopixel_fill(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000010);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, false, 10);

	neopixel_fill(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, true, 10);

	neopixel_fill(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00001000);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, false, 10);

	neopixel_fill(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00010000);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, true, 10);


	neopixel_setchannel((uint8_t)0b00000001);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, true, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000010);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, false, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, true, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00001000);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, false, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00010000);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, true, 10);



	neopixel_setchannel((uint8_t)0b00000001);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE);
	neopixel_setchannel((uint8_t)0b00000010);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, false, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE);
	neopixel_setchannel((uint8_t)0b00001000);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, false, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE);
	neopixel_setchannel((uint8_t)0b00010000);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);


	delay_ms(1000);
}


void worm2(void){

	neopixel_fill(buffer[0], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00011111);
	neopixel_show(buffer[0]);


	neopixel_setchannel((uint8_t)0b00010001);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00001010);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, false, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF, true, 10);



	neopixel_setchannel((uint8_t)0b00010001);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, true, 10);

	neopixel_fill(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00001010);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, false, 10);

	neopixel_fill(buffer[1], BASE_HUE, NEO_ALL_OFF, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, true, 10);


	neopixel_setchannel((uint8_t)0b00010001);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, true, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00001010);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, false, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE, true, 10);



	neopixel_setchannel((uint8_t)0b00010001);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, true, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE);
	neopixel_setchannel((uint8_t)0b00001010);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, false, 10);

	neopixel_fill(buffer[1], NEO_ALL_OFF, NEO_ALL_OFF, BASE_HUE);
	neopixel_setchannel((uint8_t)0b00000100);
	neopixel_anim_wipe(buffer[1], NEO_ALL_OFF, BASE_HUE, NEO_ALL_OFF, true, 10);



	
	delay_ms(1000);
}





int main(void)
{

	// This register is protected and can not be changed until the CPP register in the CPU
	// is written with the signature of 0xD8 ... I think I need to insert some assembly code here
	// This PEN flag is reset, this means that the Source clock is fed right through and not pre-scaled.
	// This needs to be checked for the electrical characteristics is such that the full 5V is required.
	// uint8_t strips[NEOPIXELS_SIZE *3]; 

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = _MAIN_CLOCK;


	neopixel_init();

	while(true){
		barber_pole(true);
		delay_ms(1000);
		barber_pole(false);
		delay_ms(2000);

		colour_shuffle();
		delay_ms(2000);

		worm();
		delay_ms(2000);

		chevron(true);
		delay_ms(1000);
		chevron(false);
		delay_ms(2000);

		worm2();
		delay_ms(2000);


	}



	return 0;
}

