#ifndef ButtonPress
#define ButtonPress

#include <avr/io.h>

char ButtonPressed(int buttonNumber, unsigned char pinOfButton, unsigned char portBit, int confidenceLevel);

char Pressed[numberOfButtons];
int Pressed_Confidence_Level[numberOfButtons]; //Measure button press cofidence
int Released_Confidence_Level[numberOfButtons]; //Measure button release confidence

char ButtonPressed(int buttonNumber, unsigned char pinOfButton, unsigned char portBit, int confidenceLevel)
{
	if (bit_is_clear(pinOfButton, portBit))
	{
		Pressed_Confidence_Level[buttonNumber] ++; //Increase Pressed Conficence
		Released_Confidence_Level[buttonNumber] = 0; //Reset released button confidence since there is a button press
		if (Pressed_Confidence_Level[buttonNumber] > confidenceLevel) //Indicator of good button press
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
		if (Released_Confidence_Level[buttonNumber] > confidenceLevel)
		{
			Pressed[buttonNumber] = 0;
			Released_Confidence_Level[buttonNumber] = 0;
		}
	}
	return 0;
}

#endif