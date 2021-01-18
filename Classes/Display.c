/*
 * Display.c
 *
 * Created: 1/14/2021 1:50:23 PM
 *  Author: alphazet team
 */ 


#include "../Headers/Display.h"
#include "../Headers/_main.h"
#include "../Headers/_glcd.h"

void initDisplay()
{
	lcd_string(3, 3, "alphazet's games");
	_delay_ms(2000);
	lcd_clear();
	lcd_string(3, 5, "LOADING...");
	
	for (int i = 2; i < 128; i++)
	{
		GLCD_Dot(40, i);
		GLCD_Dot(41, i);
		GLCD_Dot(42, i);
		GLCD_Dot(43, i);
		
		_delay_ms(50);
	}
	
	lcd_clear();
	
	for (int i = 2; i < 128; i++)
	{
		GLCD_Delete_Dot(40, i);
		GLCD_Delete_Dot(41, i);
		GLCD_Delete_Dot(42, i);
		GLCD_Delete_Dot(43, i);
	}
}