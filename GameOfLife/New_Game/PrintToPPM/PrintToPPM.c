#include "PrintToPPM.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
 
	unsigned char m_red;
	unsigned char m_green;
	unsigned char m_blue;

}PPMPixel;

typedef struct {

     int m_rows;
     int m_columns;
}PPMImage;


static void PrintPPMFile( GameBoard* _gameBoard, const char *_filename, PPMImage* _img  )
{
    FILE *fp = NULL;
	int _x = 0, _y = 0;
	int printPoint;
	
	PPMPixel* pixels = (PPMPixel*)malloc( _img->m_rows * sizeof(PPMPixel) );
	if(NULL == pixels )
	{
	
		return;
	}
	
	fp = fopen(_filename, "w");
    if (0 == fp) 
    {
		 fprintf(stderr, "Unable to open file '%s'\n", _filename );
		 exit(1);
    }
    
    (void)fprintf( fp, "P3\n" );
    (void)fprintf( fp, "%d %d\n255\n",_img->m_rows,_img->m_columns );
    
    for(_y = 0; _y < _img->m_columns; ++_y)
	{
		for(_x = 0; _x < _img->m_rows; ++_x)
		{	
			printPoint = Search_Point(_gameBoard, _x, _y);
			
			if(1 == printPoint)
			{
				pixels[_x].m_red = 150;
				pixels[_x].m_green = 200;
				pixels[_x].m_blue = 35;
			}
			
			if(0 == printPoint)
			{
				pixels[_x].m_red = 35;
				pixels[_x].m_green = 100;
				pixels[_x].m_blue = 120;
			}
			fprintf(fp, "%d %d %d ", pixels[_x].m_red, pixels[_x].m_green, pixels[_x].m_blue);
		}
		fprintf(fp,"\n");
	}
	
	free(pixels);
	fclose( fp );

	return;
  
}

void Board_Write_To_PPM(GameBoard* _gameBoard, const char* _filename)
{
	int columns = NumOfCol( _gameBoard);
	int rows = NumOfRows( _gameBoard);
	PPMImage* img;
	
	img = malloc(sizeof( PPMImage) * 1 );
	if(NULL == img)
	{
		printf("img");
		return;
	}
	img->m_rows = rows;
 	img->m_columns = columns;
 
	PrintPPMFile( _gameBoard, _filename, img );
	free(img);
}


