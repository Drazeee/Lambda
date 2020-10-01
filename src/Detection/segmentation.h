# ifndef SEGMENTATION_H_
# define SEGMENTATION_H_

# include <stdlib.h>
# include <SDL2/SDL.h>
# include "../Tools/tools.h"

SDL_Surface *cutLine(SDL_Surface *img);
void linesToSurface(SDL_Surface *img);
SDL_Surface *cutColumn(SDL_Surface *img);


# endif