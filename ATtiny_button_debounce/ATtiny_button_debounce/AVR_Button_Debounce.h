#ifndef ButtonPress
#define ButtonPress

#include <avr/io.h>
// Code written by NewbieHack.
// https://www.newbiehack.com/MCUTutorial/ButtonsAndSwitches/ButtonLibrary.aspx
// Slightly modified for ATtiny10 by C. Thomas Brittain.
// "int" types were not allowing the press threshold past 255.  Switch to uint8_t.
// Also, broke out press and release confidence levels.

char ButtonPressed(uint8_t buttonNumber, unsigned char pinOfButton, unsigned char portBit, uint8_t pressConfidenceLevel, uint8_t releaseConfidenceLevel);

char Pressed[numberOfButtons];
uint8_t Pressed_Confidence_Level[numberOfButtons]; //Measure button press cofidence
uint8_t Released_Confidence_Level[numberOfButtons]; //Measure button release confidence

char ButtonPressed(uint8_t buttonNumber, unsigned char pinOfButton, unsigned char portBit, uint8_t pressConfidenceLevel, uint8_t releaseConfidenceLevel)
{
	if (bit_is_clear(pinOfButton, portBit))
	{
		Pressed_Confidence_Level[buttonNumber]++; //Increase Pressed Conficence
		Released_Confidence_Level[buttonNumber] = 0; //Reset released button confidence since there is a button press
		if (Pressed_Confidence_Level[buttonNumber] > pressConfidenceLevel) //Indicator of good button press
		{
			if (Pressed[buttonNumber] == 0)
			{
				Pressed[buttonNumber] = 1;
				return 1;
			}
			//Zero it so a new pressed condition can be evaluated
			Pressed_Confidence_Level[buttonNumber] = 0;
		}
	}
	else
	{
		Released_Confidence_Level[buttonNumber] ++; //This works just like the pressed
		Pressed_Confidence_Level[buttonNumber] = 0; //Reset pressed button confidence since the button is released
		if (Released_Confidence_Level[buttonNumber] > releaseConfidenceLevel)
		{
			Pressed[buttonNumber] = 0;
			Released_Confidence_Level[buttonNumber] = 0;
		}
	}
	return 0;
}

#endif