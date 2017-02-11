/*
 * State_Controller.cpp
 *
 * Created: 2/11/2017 8:43:11 AM
 * Author : Thomas Brittain
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/io.h>

#define numberOfButtons 1
#include "AVR_Button_Debounce.h"

int state = 0;

void clearPins();

int main(void)
{

	DDRB |= 0b00000101;  // Setup PORTB, PIN2 as OUTPUT.
	//PORTB |= 0x02; // Setup PORTB, PIN1 as INPUT.

    /* Replace with your application code */
    while (1) 
    {
		if(ButtonPressed(1, PINB, 1, 300, 300) == 1){
			state++;
			if(state > 3) { state = 0; }
			//PORTB ^= (1 << PINB2); // Toggles PORTB, PIN2.
		}
		
		switch(state){			
			case 0:
				clearPins();
				PORTB |= (1 << PINB2); // Toggles PORTB, PIN2.
				break;
			case 1:
				clearPins();
				PORTB |= (1 << PINB0); // Toggles PORTB, PIN0.
				break;
			case 2:
				clearPins();
				PORTB |= (1 << PINB2); // Toggles PORTB, PIN2.
				PORTB |= (1 << PINB0); // Toggles PORTB, PIN0.				
				break;
			case 3:
				clearPins();
				break;
			default:
				clearPins();
				break;
		}
    }
}

void clearPins(){
	PORTB &=~ (1 << PINB2); // Toggles PORTB, PIN2.
	PORTB &=~ (1 << PINB0); // Toggles PORTB, PIN2.
}