#include "findChar.h"

unsigned *find_lines(SDL_Surface* screen, unsigned *nb_lines)
{
  unsigned count = 1;
  unsigned *buffer = malloc(count*sizeof(unsigned));
  
  buffer[0]=5;
  
  unsigned write = -2;
  unsigned width=(unsigned)screen->w, height=(unsigned)screen->h;
    
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
        count++;
        draw_char(screen, 0, i, width-1,
	        -1, 0x000000ff);
        buffer = realloc(buffer, count*sizeof(unsigned));
	      buffer[count-1] = i;
      }  
	  }
  } 
  *nb_lines = count;
  return buffer;
} 

int *find_chars(SDL_Surface* screen, unsigned *lines, unsigned size, unsigned *nb_chars)
{
    int *buffer = NULL;
    unsigned i = 1;
    int max=0, min=0, maxw=0,
	     minw=0, x=0, found = 0, write=0, count=0,
	     moy=0, total_length=0, number_space=0, number_found=0;
    int width=screen->w;
    int prev = 0;
    int next = 0;

    int chars = 0;

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
	      for (int j=0;j<width;++j)
	      {
		      moy=0;
		      if (!found && write)
		      {
            chars++;
            buffer = realloc(buffer,chars*4*sizeof(int));

		        buffer[count]=x;
		        buffer[count+1]=min;
		        buffer[count+2]=maxw-minw;
		        buffer[count+3]=max-min;
		        count+=4;
		        number_found++;
		        draw_char(screen, x, min, maxw-minw, max-min,
		    	    0x0000ff00);
		        write=0;
		        total_length+=maxw-minw;	
		      }
		      found=0;
		      for (int k=prev;k<next;++k)
		      {
		        if (getPix(screen, j, k)
			        ==0x00000000)
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
		        else if (k==next-1 && !write 
			        && total_length > 0)
		        {
			        number_space++;
			        moy= total_length
			          /number_found;
			        if (number_space>=(moy*4/5))
			        {
                chars++;
                buffer = realloc(buffer, chars*4*sizeof(int));
			          buffer[count]=maxw+1;
			          buffer[count+1]=prev;
			          buffer[count+2]=-2;
			          buffer[count+3]=next-prev;
			          count+=4;
			          draw_char(screen, maxw+1, prev, -1, 
			    	    next-prev, 0x000000ff);
			          number_space=0;
			        }
		        }
		      }
	      } 
	      ++i;
	    }
    }    
    *nb_chars = chars;
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
      w++;
    if (y+h<=height)
      h++;
    
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


char *find_char(SDL_Surface* screen)
{
  int in_size = 256;
  int ou_size = 88;

  char *chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+=/%()[]éèàùëêç.,;:?!&@$€";
  int layers = 4;
  int layers_Size[] = {in_size, 2*in_size, in_size, ou_size};
  struct neuron **net = load_network(layers_Size, layers);
  

  unsigned nb_lines = 0;
  unsigned *lines = find_lines(screen, &nb_lines);
  unsigned tot_chars = 0;
  int *chars2 = find_chars(screen, lines, nb_lines, &tot_chars);
  
  //unsigned nbChars = 0;

  //display_weights(net,layers_Size,layers);

  int *inputs = NULL;

  char *string = malloc(tot_chars * sizeof(char));
  unsigned i = 0;
  
  for(i = 0; i<tot_chars; i++)
  {    
    int j = i*4;
    if(chars2[j+2] == -2)
    {
      string[i] = ' ';
    }
    else
    {
      inputs = transformPix2(chars2[j], chars2[j+1], chars2[j+2], chars2[j+3], screen);
      char ans = comput(net, inputs, layers_Size, layers, chars);
      string[i] = ans;      
    }
  }
  string[i] = '\0';
  printf("%s\n", string); 
  return string;    
}
