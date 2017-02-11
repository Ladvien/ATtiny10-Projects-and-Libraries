/*
 * ATtiny_test_v01.cpp
 *
 * Created: 2/9/2017 6:23:04 AM
 * Author : Thomas Brittain
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>

#define numberOfButtons 1
#include "AVR_Button_Debounce.h"


int main(void)
{
	DDRB |= 0x04;  // Setup PORTB, PIN2 as OUTPUT.
	PORTB |= 0x02; // Setup PORTB, PIN1 as INPUT.
	while (1)
	{	
		if(ButtonPressed(1, PINB, 1, 10, 10) == 1){
			PORTB ^= (1 << PINB2); // Toggles PORTB, PIN2.
		} 

	}
}

