#include <stdlib.h>
#include <stdio.h>
#include "tabPix.h"


int *transformPix(unsigned x, unsigned y, unsigned w, unsigned h, SDL_Surface *screen)
{
  int *data = malloc(256*sizeof(unsigned));

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
			//printf("%d ", data[cy * 16 + cx]);
		}
		//printf("\n");
	}	
	return data;
}
