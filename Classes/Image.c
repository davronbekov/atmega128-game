/*
 * Image.c
 *
 * Created: 1/13/2021 4:01:09 PM
 *  Author: alphazet team
 */ 

#include "../Headers/Image.h"
#include "../Headers/Display.h"
#include "../Headers/_glcd.h"

void DrawImage(Image *ImageItem)
{
	for (int i = 0; i < ImageItem->h; i++)
	{
		for (int j = 0; j < ImageItem->w; j++)
		{
			if(ImageItem->bitmap[i*ImageItem->w + j] != 0xff)
			{
				GLCD_Dot(i + ImageItem->startRow, j + ImageItem->startColumn);
			}
		}
	}
}

void DeleteImage(Image *ImageItem)
{
	for (int i = 0; i < ImageItem->h; i++)
	{
		for (int j = 0; j < ImageItem->w; j++)
		{
			if(ImageItem->bitmap[i*ImageItem->w + j] != 0xff){
				GLCD_Delete_Dot(i + ImageItem->startRow, j + ImageItem->startColumn);
			}
		}
	}
}

