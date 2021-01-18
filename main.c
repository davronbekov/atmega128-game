/*
 * alphazet.c
 *
 * Created: 1/13/2021 10:54:33 AM
 * Author : Cherokee team
 */ 

#include <avr/io.h>
#include "Headers/_main.h"
#include "Headers/_port.h"

#include "Headers/Image.h"
#include "Headers/DIsplay.h"

#include "Assets/squirrel.h"
#include "Assets/nute.h"
#include "Assets/cherry.h"

Image squirrel;
int currentY = 50;

void interruptInit(void)
{
	EIMSK = 0x03;
	EICRA = 0x0e;  
	SEI();      
}

SIGNAL(INT0_vect)
{
	if(currentY >= 5){
		squirrel.startColumn = currentY;
		DeleteImage(&squirrel);
	
		currentY -= 5;
		
		squirrel.bitmap = &squirrel_left_img;
		squirrel.startColumn = currentY;
		DrawImage(&squirrel);
	}	
}

SIGNAL(INT1_vect)
{
	if(currentY + 5 + squirrel.w <= 128){
		squirrel.startColumn = currentY;
		DeleteImage(&squirrel);			
		
		currentY += 5;
		
		squirrel.bitmap = &squirrel_right_img;
		squirrel.startColumn = currentY;
		DrawImage(&squirrel);
	}
}

int main(void)
{
	Port_init();
	interruptInit();
	lcd_clear();
	lcd_init();
	
	initDisplay();	
	
	squirrel.w = 34;
	squirrel.h = 25;
	squirrel.bitmap = &squirrel_left_img;
	squirrel.startRow = 39;
	squirrel.startColumn = currentY;
	squirrel.visible = 1;
	
	Image nutes[8];
	Image cherries[8];
	int r;
	int itemCounter[3] = {0,0,0};
	int itemType = 0;
	int i = 0;
	int score = 0;
	char scoreStr[100];
	
	DrawImage(&squirrel);
	
	int isGameOver = 0;
	
	while(1){
		
		_delay_ms(1000);
		itemType = rand() % 2;
		
		if(isGameOver == 0){
			switch(itemType){ //generating items
				case 0: //nutes
				
					if(itemCounter[0] < 8){
						r = rand() % 120;
						if(r > 15){
							r -= 15;
						}
					
						nutes[itemCounter[0]].visible = 1;
						nutes[itemCounter[0]].w = 15;
						nutes[itemCounter[0]].h = 15;
						nutes[itemCounter[0]].bitmap = &nute_image;
						nutes[itemCounter[0]].startRow = 7;
						nutes[itemCounter[0]].startColumn = r;
						DrawImage(&nutes[itemCounter[0]]);
					
						itemCounter[0]++;
					}
				
					break;
				case 1: // cherry
				
					if(itemCounter[1] < 8){
						r = rand() % 120;
						if(r > 11){
							r -= 11;
						}
						
						cherries[itemCounter[1]].visible = 1;
						cherries[itemCounter[1]].w = 11;
						cherries[itemCounter[1]].h = 15;
						cherries[itemCounter[1]].bitmap = &cherry_image;
						cherries[itemCounter[1]].startRow = 7;
						cherries[itemCounter[1]].startColumn = r;
						DrawImage(&cherries[itemCounter[1]]);
						
						itemCounter[1]++;
					}
					
					break;
			}
		}
		
		// nutes
		for(i = 0; i < itemCounter[0]; i++){
			if(nutes[i].visible && isGameOver == 0){
				
				_delay_ms(400);
				DeleteImage(&nutes[i]);
				nutes[i].startRow += 8 + score/2;
				DrawImage(&nutes[i]);
				
				if(squirrel.startRow <= (nutes[i].startRow + nutes[i].h))
				{
					if(nutes[i].startColumn > squirrel.startColumn){
						if(nutes[i].startColumn < (squirrel.startColumn + squirrel.w)){
							nutes[i].visible = 0;
							DeleteImage(&nutes[i]);
							score++;
							sprintf(scoreStr, "Score: %d", score);
							lcd_string(0, 1, scoreStr);
						}
					}
				}
				
				if((nutes[i].startRow + nutes[i].h) >= 64){
					isGameOver = 1;
				}
				
			}
		}
		
		//cherries
		for(i = 0; i < itemCounter[1]; i++){
			if(cherries[i].visible && isGameOver == 0){
				
				_delay_ms(400);
				DeleteImage(&cherries[i]);
				cherries[i].startRow += 8 + score/2;
				DrawImage(&cherries[i]);
				
				if(squirrel.startRow <= (cherries[i].startRow + cherries[i].h))
				{
					if(cherries[i].startColumn > squirrel.startColumn){
						if(cherries[i].startColumn < (squirrel.startColumn + squirrel.w)){
							cherries[i].visible = 0;
							DeleteImage(&cherries[i]);
							score++;
							sprintf(scoreStr, "Score: %d", score);
							lcd_string(0, 1, scoreStr);
						}
					}
				}
				
				if((cherries[i].startRow + cherries[i].h) >= 64){
					isGameOver = 1;
				}
				
			}
		}
	
		// if game is over
		if(isGameOver){
			// nutes
			for(i = 0; i < itemCounter[0]; i++){
				DeleteImage(&nutes[i]);
			}
			
			//cherries
			for(i = 0; i < itemCounter[1]; i++){
				DeleteImage(&cherries[i]);
			}
			lcd_clear();
			lcd_string(3, 3, "Game Over");
		}
		
	}
	
	
	
}

