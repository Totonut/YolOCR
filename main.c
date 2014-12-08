#include "constantes.h"
#include "perfectImage.h"
#include "interface.h"


int main(int argc, char *argv[])
{	
  int in_size = 256;
  int ou_size = 88;

  char *chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+=/%()[]éèàùëêç.,;:?!&@$€";
  int layers = 4;
  int layers_Size[] = {in_size, 2*in_size, in_size, ou_size};

  struct neuron **net = load_network(layers_Size, layers);

  

  gtk_init(&argc, &argv);
  SDL_Surface *image = NULL;

  if (argc==2)
	image = IMG_Load(argv[1]);
  else
	image = IMG_Load("image.jpg");
	SDL_SaveBMP(image, "image.bmp");
	
  perfectImage(image);
 	char *string = find_char(image, net, layers_Size, layers, chars);
	SDL_SaveBMP(image, "image2.bmp");

  printf("%s\n", string);

  open_window();

  SDL_FreeSurface(image);	
	
	SDL_Quit();
	return 0;
}
