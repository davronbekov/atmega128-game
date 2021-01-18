/*
 * Image.h
 *
 * Created: 1/13/2021 3:17:42 PM
 *  Author: alphazet team
 */ 

#ifndef IMAGE_CLASS
#define IMAGE_CLASS

typedef struct
{
	int w;
	int h;
	char *bitmap;
	int startRow;
	int startColumn;
	int visible;
} Image;

void DrawImage(Image *ImageItem);
void DeleteImage(Image *ImageItem);

#endif