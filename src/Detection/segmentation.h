# ifndef SEGMENTATION_H_
# define SEGMENTATION_H_

# include <stdlib.h>
# include <SDL2/SDL.h>
# include "../Tools/tools.h"
# include "../ImageTreatment/filters.h"
#include <sys/types.h> 
#include <sys/stat.h> 

SDL_Surface *cutLine(SDL_Surface *img, int first);
void linesToSurface(SDL_Surface *img);
SDL_Surface *cutColumn(SDL_Surface *img);
SDL_Surface *cutWord(SDL_Surface *img);
void convertColumns(SDL_Surface *img, char *directory);
void removeLines(SDL_Surface *img, char *directory);
void removeLinesForCharacters(SDL_Surface *img, char *directory);
void removeLinesForWords(SDL_Surface *img, char *directory);


# endif