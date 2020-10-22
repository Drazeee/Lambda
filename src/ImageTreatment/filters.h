#include <SDL2/SDL.h>
#include <stdio.h>
# include "../Tools/tools.h"
# include <stdlib.h>

SDL_Surface *blackAndWhite(SDL_Surface *img);
SDL_Surface *grayscale(SDL_Surface *img, char save, char *path);