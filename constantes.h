#ifndef CONSTANTES_H
#define CONSTANTES_H

#define BUTTON_WIDTH        150
#define BUTTON_HEIGHT        50
#define WINDOW_WIDTH        1000
#define WINDOW_HEIGHT       800

#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
	#include <SDL_image/SDL_image.h>
	#include <SDL_ttf/SDL_ttf.h>
#else
	#include "SDL/SDL_image.h"
	#include "SDL/SDL_ttf.h"
#endif
#endif
