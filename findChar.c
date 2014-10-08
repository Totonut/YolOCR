#include "findChar.h"

unsigned* findLines(SDL_Surface* ecran)
{
	unsigned *buffer = malloc(ecran->h * sizeof(unsigned));
	int count=0;
	unsigned ecriture = 0;
	unsigned j = 0;
	for (unsigned i=ecran->h-1; i>0;i--)
	{
		for (j=0;j<ecran->w;j++)
		{
			if (obtenirPixel(ecran, j, i)==0x00000000) 
			{
				if (count == 0)
				{
					drawLine(ecran, i);
					count++;
					buffer[0]=i;
				}
				else if (count != 0 && ecriture-i > 1)
				{
					j=ecran->w;
					drawLine(ecran, i);
					buffer[count]=i;
					count++;
				}
				ecriture = i;
			}
		}
	} 
	buffer[count]=1;
	return buffer;
} 

void drawLine(SDL_Surface* ecran, unsigned line)
{
	for (int i=0; i<ecran->w;i++)
	{
		definirPixel(ecran, i, line, 0x000000ff);
	}
} 

unsigned* findChars(SDL_Surface* ecran, unsigned* lines)
{
	unsigned buffer = NULL;
	unsigned i = 0, max=0, min=0, maxw=0, minw=0, x=0, caractere = 0, ecriture=0;
	if (lines != NULL)
	{
		unsigned prev = 0;
		unsigned suiv = lines[0];
		while (lines[i+1]!=0)
		{
			prev=suiv;
			suiv = lines[i+1];
			for (unsigned j=0;j<ecran->w;j++)
			{
				if (caractere==0 && ecriture==1)
				{
					drawChar(ecran, x, min, maxw-minw, max-min);
					ecriture=0;
				}
				caractere=0;
				for (unsigned k=prev;k>suiv;k--)
				{
					if (obtenirPixel(ecran, j, k)==0x00000000)
					{	
						caractere=1;
						if (ecriture==0)
						{
							min=k;
							max=k;
							minw=j;
							maxw=j;
							x=j;
							ecriture=1;
						}
						else
						{	
							min = k<min? k:min;
							max = k>max? k:max;
							minw = j<minw? j:minw;
							maxw = j>maxw? j:maxw;
						}
					}
						
				}
			} 
			i++;
		}
	}
	return buffer;
}

void drawChar(SDL_Surface* ecran, unsigned x, unsigned y, unsigned w, unsigned h)
{
	// On essaye d'encadrer le caractère sans le toucher
	if (y-1>=0)
	{
		y--;
		h++;
	}
	if (x-1>=0)
	{	
		x--;
		w++;
	}
	if (x+w+1<=ecran->w-1)
	{	
		w++;
	}
	if (y+h+1<=ecran->h-1)
	{	
		h++;
	}

	// On l'encadre
	for (int j=1;j<=w;j++)
		definirPixel(ecran, x+j, y, 0x0000ff00);
	for (int i = 0; i<=h;i++)
	{
		definirPixel(ecran, x, y+i, 0x0000ff00);
		definirPixel(ecran, x+w, y+i, 0x0000ff00);
	}
	for (int j=1;j<=w;j++)
		definirPixel(ecran, x+j, y+h, 0x0000ff00);
}

unsigned * findChar(SDL_Surface* ecran)
{
	return findChars(ecran, findLines(ecran));
}

