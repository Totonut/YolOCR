#include <stdlib.h>
#include <stdio.h>
#include "tabPix.h"

unsigned int **transformPix(unsigned int *tabPix, SDL_Surface *screen)
{
	unsigned** newData = malloc(500*sizeof(int *));
	unsigned nearestMatchX = 0, nearestMatchY = 0, n = 0;
	Uint32 pixel = 0;
	while (tabPix)
	{		
		double scaleWidth =  16.0 / (double)tabPix[2];
		double scaleHeight = 16.0 / (double)tabPix[3];
		newData[n] = malloc(256*sizeof(int));
		for(int cy = 0; cy < 16; cy++)
		{
			for(int cx = 0; cx < 16; cx++)
			{
				nearestMatchY =  (unsigned)(cy / scaleHeight) > tabPix[3] ? tabPix[3] : (unsigned)(cy / scaleHeight);
				nearestMatchX =  (unsigned)(cx / scaleWidth) > tabPix[2] ? tabPix[2] : (unsigned)(cx / scaleWidth);;
				pixel = getPix(screen, tabPix[0] + nearestMatchX, tabPix[1] + nearestMatchY); 
				newData[n][cy * 16 + cx] = (pixel != 0x00000000) ? 0 : 1;
				printf("%d ", newData[n][cy * 16 + cx]);
			}
			printf("\n");
		}
		++n;
		tabPix+=4;
		printf("\n");
	}
	return newData;
}


unsigned *transformPix2(unsigned x, unsigned y, unsigned w, unsigned h, SDL_Surface *screen)
{
  unsigned *data = malloc(256*sizeof(unsigned));

	unsigned nearestMatchX = 0, nearestMatchY = 0;
	Uint32 pixel = 0;
		
	double scaleWidth =  16.0 / (double)w;
	double scaleHeight = 16.0 / (double)h;

	for(int cy = 0; cy < 16; cy++)
	{
		for(int cx = 0; cx < 16; cx++)
		{
			nearestMatchY =  (unsigned)(cy / scaleHeight) > h ? h : (unsigned)(cy / scaleHeight);
			nearestMatchX =  (unsigned)(cx / scaleWidth) > w ? w : (unsigned)(cx / scaleWidth);;
			pixel = getPix(screen, x + nearestMatchX, y + nearestMatchY); 
			data[cy * 16 + cx] = (pixel != 0x00000000) ? 0 : 1;
			printf("%d ", data[cy * 16 + cx]);
		}
		printf("\n");
	}	
	return data;
}
