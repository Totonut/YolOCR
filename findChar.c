#include "findChar.h"

unsigned findLines(SDL_Surface* ecran, unsigned *buffer)
{
	buffer[0]=5;
	unsigned ecriture = -2;
	int count=1;
	for (unsigned i=0; i<ecran->h;++i)
	{
		for (unsigned j=0;j<ecran->w;++j)
		{
			if (obtenirPixel(ecran, j, i)==0x00000000) 
			{		
				ecriture = i;
				j=ecran->w;
			}
			else if (i-ecriture==1 && j==ecran->w-1)
			{
				drawLine(ecran, i);
				buffer[count] =i;
				count++;
			}
		}
	}
	return count;
} 

void drawLine(SDL_Surface* ecran, unsigned line)
{
	for (int i=0; i<ecran->w;i++)
	{
		definirPixel(ecran, i, line, 0x000000ff);
	}
} 

/*int is_linked_pixel(unsigned* buffer1, unsigned* buffer2, size_t size, int i, int add)
{
	return (buffer2[i] && (buffer1[i] || (i>0 && buffer1[i-1]) || (i<size-1 && buffer1[i+1]) || (i+add>=0 && i+add <size && is_linked_pixel(buffer1, buffer2, size, i+add, add))));
}*/

/*int is_linked(unsigned* buffer1, unsigned* buffer2, size_t size)
{
	int i=0;
	for (;i<size;i++)
	{
		if (buffer2[i] && !is_linked_pixel(buffer1, buffer2, size, i, 1) && !is_linked_pixel(buffer1, buffer2, size, i, -1))
			break;
	}
	return i==size? 1 : 0;
}*/


/*void empty(unsigned* buffer, size_t lineHeight)
{
	for (int i=0;i<lineHeight;i++)
		buffer[i]=0;
}*/

/*void initialize(unsigned*buffer, size_t size)
{
	buffer = malloc(size*sizeof(unsigned));
	for (int i=0;i<size;i++)
		buffer[i]=0;	

}*/

unsigned* findChars(SDL_Surface* ecran, unsigned* lines, unsigned size)
{ 
	unsigned *buffer = malloc(2*ecran->w*size*sizeof(unsigned));
	unsigned i = 1, max=0, min=0, maxw=0, minw=0, x=0, caractere = 0, ecriture=0, count=0;
// Ecriture : valeure initialisees ?
// Caractere : pixels noirs sur la ligne ?


//	unsigned add1[] = {};
//	unsigned add2[] = {};
//	initialize(add1, ecran->h);
//	initialize(add2, ecran->h);
//	size_t lineHeight=0;
	unsigned prev = 0;
	unsigned suiv = 0;
	if (lines != NULL)
	{
		prev = 0;
		suiv = lines[0];
		while (i<size)
		{
			prev=suiv;
			suiv = lines[i];
//			lineHeight=suiv-prev;
			for (unsigned j=0;j<ecran->w;++j)
			{
				if (!caractere && ecriture)// || !is_linked(add1, add2, lineHeight))
				{
					buffer[count]=x;
					buffer[count+1]=min;
					buffer[count+2]=maxw-minw;
					buffer[count+3]=max-min;
					count+=4;
					drawChar(ecran, x, min, maxw-minw, max-min);
					ecriture=0;
				}
//				strncpy(add1, add2, lineHeight);
//				empty(add2, lineHeight);
				caractere=0;
				for (unsigned k=prev;k<suiv;++k)
				{
					if (obtenirPixel(ecran, j, k)==0x00000000)
					{	
//						add2[k-prev]=1;
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
			++i;
		}
	}
	return buffer;
}

void drawChar(SDL_Surface* ecran, unsigned x, unsigned y, unsigned w, unsigned h)
{
	// On essaye d'encadrer le caractère sans le toucher
	if (y>=1)
	{
		y--;
		h++;
	}
	if (x>=1)
	{	
		x--;
		w++;
	}
	if (x+w<=ecran->w-2)
	{	
		w++;
	}
	if (y+h<=ecran->h-2)
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
	unsigned* buffer = malloc(ecran->w*sizeof(unsigned));
	unsigned size = findLines(ecran, buffer);
	return findChars(ecran, buffer, size);
}

