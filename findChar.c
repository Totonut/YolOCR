#include "findChar.h"


unsigned find_lines(SDL_Surface* screen, unsigned *buffer)
{
	buffer[0]=5;
	unsigned write = -2;
	unsigned width=(unsigned)screen->w, height=(unsigned)screen->h;
	int count=1;
	for (unsigned i=0; i<height;++i)
	{
		for (unsigned j=0;j<width;++j)
		{
			if (getPix(screen, j, i)==0x00000000) 
			{		
				write = i;
				j=screen->w;
			}
			else if (i-write==1 && j==width-1)
			{
//				draw_line(screen, i);
				draw_char(screen, 0, i, width-1, -1, 0x000000ff);
				buffer[count] =i;
				count++;
			}
		}
	}
	return count;
} 

unsigned* find_chars(SDL_Surface* screen, unsigned* lines, unsigned size)
{
	unsigned *buffer = malloc(screen->w*size*2*sizeof(unsigned));
	unsigned i = 1, max=0, min=0, maxw=0, minw=0, x=0, found = 0, write=0, 
		count=0, moy=0, total_length=0, number_space=0, number_found=0;
	// Ecriture : valeure initialisees ?
	// Caractere : pixels noirs sur la ligne ?

	unsigned width=(unsigned)screen->w;
	unsigned prev = 0;
	unsigned next = 0;
	if (lines != NULL)
	{
		prev = 0;
		next = lines[0];
		while (i<size)
		{
			moy=0;
			total_length=0;
			number_found=0;
			prev=next;
			next = lines[i];
			for (unsigned j=0;j<width;++j)
			{
				moy=0;
				if (!found && write)
				{
					buffer[count]=x;
					buffer[count+1]=min;
					buffer[count+2]=maxw-minw;
					buffer[count+3]=max-min;
					count+=4;
					number_found++;
					draw_char(screen, x, min, maxw-minw, max-min, 0x0000ff00);
					write=0;
					total_length+=maxw-minw;	
				}
				found=0;
				for (unsigned k=prev;k<next;++k)
				{
					if (getPix(screen, j, k)==0x00000000)
					{
						number_space=0;
						found=1;
						if (!write)
						{
							min=k;
							max=k;
							minw=j;
							maxw=j;
							x=j;
							write=1;
						}
						else
						{		
							min = k<min? k:min;
							max = k>max? k:max;
							minw = j<minw? j:minw;
							maxw = j>maxw? j:maxw;
						}
					}
					else if (k==next-1 && !write && total_length > 0)
					{
						number_space++;
						moy= total_length/number_found;
						if (number_space>= (moy*4/5))
						{
							buffer[count]=maxw+1;
							buffer[count+1]=prev;
							buffer[count+2]=-2;
							buffer[count+3]=next-prev;
							count+=4;
							draw_char(screen, maxw+1, prev, -1, next-prev, 0x000000ff);
							number_space=0;
						}
					}
				}
			} 
			++i;
		}
	}
	return buffer;
}

void draw_char(SDL_Surface* screen, unsigned x, unsigned y, unsigned w,
	unsigned h, Uint32 color)
{
	unsigned width = (unsigned)screen->w-2, height=(unsigned)screen->h-2;
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
		if (x+w<=width)
		{	
			w++;
		}
		if (y+h<=height)
		{	
			h++;
		}

		// On l'encadre
		for (unsigned j=1;j<=w;j++)
			setPix(screen, x+j, y, color);
		for (unsigned i = 0; i<=h;i++)
		{
			setPix(screen, x, y+i, color);
			setPix(screen, x+w, y+i, color);
		}
		for (unsigned j=1;j<=w;j++)
			setPix(screen, x+j, y+h, color);
}


unsigned* find_char(SDL_Surface* screen)
{
	unsigned* buffer = malloc(screen->w*sizeof(unsigned));
	return find_chars(screen, buffer, find_lines(screen, buffer));
}
