#include <stdlib.h>
#include <stdio.h>
#include "tabPix.h"

int *transformPix(int *tabPix, SDL_Surface *screen)
{
	unsigned int* newData[256] = malloc(strlen(tabpix)*256*sizeof(int));
	unsigned int count = 0, nearestMatchX = 0, nearestMatchY = 0;
	while (tabPix[count])
	{
		double scaleWidth =  16. / (double)tabPix[count+2];
		double scaleHeight = 16. / (double)tabPix[count+3];

		for(int cy = 0; cy < 16; cy++)
		{
			for(int cx = 0; cx < 16; cx++)
			{
				nearestMatchX =  (int)(cy / scaleHeight) > tabPix[count+3] ? tabPix[count+3] : (int)(cy / scaleHeight);
				nearestMatchY =  (int)(cx / scaleWidth) > tabPix[count+2] ? tabPix[count+2] : (int)(cx / scaleWidth);;
				*newData[cy * 16 + cx] =  getPix(screen, tabPix[count] + nearestMatchX), tabPix[count + 1] + nearestMatchY); 
			}
		}
		count+=4;
		++newData;
	}
	newData-=(count/4);
	return newData;
}
