#include <SDL2/SDL.h>
#include <stdio.h>
# include "../Tools/tools.h"
# include <stdlib.h>

SDL_Surface *blackAndWhite(SDL_Surface *img, char save, char *path);
SDL_Surface *grayscale(SDL_Surface *img, char save, char *path);
SDL_Surface *convolute(SDL_Surface *img, float mask[], int num_rows, 
	int num_cols);
SDL_Surface *contrastImage(SDL_Surface *img);
SDL_Surface *noiseReduction(SDL_Surface *img);
