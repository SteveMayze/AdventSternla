/*
 * NeoStrip5Channel_plus.c
 *
 * Created: 11/06/2022 09:46:43
 * Author : Steven
 */ 

#include "stdlib.h"
#include "time.h"
#include <avr/io.h>
#include "neopixel.h"
#include "neopixel_anim.h"
#include <avr/pgmspace.h>

/*! The setting for the CLKCTRL.MCLKCTRLB register */
#define _MAIN_CLOCK 0x00

#define BASE_HUE ((uint8_t) 0x03)
#define MED_HUE  ((uint8_t) 0x06)
#define HI_HUE   ((uint8_t) 0x0C)
#define MAX_BUFFERS 8
#define NEO_ANIM_CYCLES 100 // NEO_HUE_ADJ * 5
#define NEO_ANIM_MAX_GRADIENT 100

#define DEFAULT_RED HI_HUE
#define DEFAULT_GREEN 0x00
#define DEFAULT_BLUE 0x00

// Ensure this goes into the FLASH/Program space rather than RAM. However, this
// will require a special work around to access this data.
const  uint8_t font_table[26][5] PROGMEM = { 
    // A, B, C, D, E, F
    {0x7E,0x90,0x90,0x90,0x7E}, {0xFE,0x92,0x92,0x92,0x6C}, {0x7C,0x82,0x82,0x82,0x44}, {0xFE,0x82,0x82,0x82,0x7C}, {0xFE,0x92,0x92,0x92,0x82}, {0xFE,0x90,0x90,0x90,0x80},
    // G, H, I, J, K, L
    {0x7C,0x82,0x92,0x92,0x5C}, {0xFE,0x10,0x10,0x10,0xFE}, {0x00,0x82,0xFE,0x82,0x00}, {0x84,0x82,0x82,0x82,0xFC}, {0xFE,0x10,0x28,0x44,0x82}, {0xFE,0x02,0x02,0x02,0x02},
    // M, N, O, P, Q, R
    {0xFE,0x40,0x20,0x40,0xFE}, {0xFE,0x20,0x10,0x08,0xFE}, {0x7C,0x82,0x82,0x82,0x7C}, {0xFE,0x90,0x90,0x90,0x60}, {0x7C,0x82,0x8A,0x86,0x7C}, {0xFE,0x90,0x98,0x94,0x62},
    // S T U V W X
    {0x64,0x92,0x92,0x92,0x4C}, {0x80,0x80,0xFE,0x80,0x80}, {0xFC,0x02,0x02,0x02,0xFC}, {0xF8,0x04,0x02,0x04,0xF8}, {0xF8,0x06,0x38,0x06,0xF8}, {0x82,0x44,0x38,0x44,0x82},
    // Y, Z
    {0xC0,0x30,0x0E,0x30,0xC0}, {0x86,0x8A,0x92,0xA2,0xC2}
    };


uint8_t display_buffer[MAX_BUFFERS][neopixel_buffer_size];

char message[255] = "ZAM PCS TEXTECK ";
uint8_t message_length = 16;
uint8_t chr_idx = 0;
uint8_t column = 0;

pixel_type message_buffer[MAX_BUFFERS][5]; // The number of characters in the string x 5 for each char and x3 for each LED.




uint8_t clear_message_buffer(uint8_t message_length, pixel_type message_buffer[][5]) {
        
    // For each character in the message 
    for(uint8_t i=0; i<message_length; i++) {
        for (uint8_t col=0; col < 5; col++){
            for(uint8_t row = 0; row < MAX_BUFFERS; row++){
                message_buffer[row][col].red = 0x00; 
                message_buffer[row][col].green = 0x00; 
                message_buffer[row][col].blue = 0x00; 
            }
        }
    }
    
    return 0;
}

uint8_t render_next_char(char *message, uint8_t message_length, uint8_t char_idx,
        uint8_t red, uint8_t green, uint8_t blue,
        pixel_type message_buffer[][5]){
    if (message[char_idx] == ' ') {
        clear_message_buffer(message_length, message_buffer);
        return 0;  
    } 
    uint8_t font_idx = (message[char_idx] & 0x7F) - 'A';
    // The font information is stored in the programs space and needs
    // this workaround to access it.
    uint8_t font_char[5];
    for (uint8_t i=0; i<5;i++){
        font_char[i] =  pgm_read_byte( &(font_table[font_idx][i]));        
    }
    for(uint8_t col = 0; col < 5; col++){
        for(uint8_t row = 0; row < MAX_BUFFERS; row++){
            if( font_char[col] & (1<<row)) {
                message_buffer[row][col].red = red;
                message_buffer[row][col].green = green;
                message_buffer[row][col].blue = blue;
            }
        }
    }
    return 0;
}

void roll_text(){
    if ( column > 4 ){
        for( uint8_t channel = 0; channel < MAX_BUFFERS; channel++){
            neopixel_shift(display_buffer[channel], true, false);
            display_buffer[channel][NEO_RED] = 0x00;
            display_buffer[channel][NEO_GREEN] = 0x00;
            display_buffer[channel][NEO_BLUE] = 0x00;
        }
        column = 0;
        chr_idx++;
        if ( chr_idx > message_length -1){
            chr_idx = 0;
        }
        clear_message_buffer(message_length, message_buffer);
        render_next_char(message, message_length, chr_idx, 
                DEFAULT_RED, DEFAULT_GREEN, DEFAULT_BLUE, message_buffer);
    }
    for( uint8_t channel = 0; channel < MAX_BUFFERS; channel++){
        neopixel_shift(display_buffer[channel], true, false);
        display_buffer[channel][NEO_RED] = message_buffer[channel][column].red;
        display_buffer[channel][NEO_GREEN] = message_buffer[channel][column].green;
        display_buffer[channel][NEO_BLUE] = message_buffer[channel][column].blue;
        neopixel_setchannel(1<<channel);
        neopixel_show(display_buffer[channel]);
    }
}

/************************************************************************/
/* The main control loop                                                */
/************************************************************************/
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
    
    clear_message_buffer(message_length, message_buffer);
    render_next_char(message, message_length, chr_idx, 
            DEFAULT_RED, DEFAULT_GREEN, DEFAULT_BLUE, message_buffer);

	while(true) {
        
        roll_text();
        column++;
        delay_ms(100);
        
	}
	return 0;
}

