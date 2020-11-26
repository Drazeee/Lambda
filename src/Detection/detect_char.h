# ifndef DETECT_CHAR_H_
# define DETECT_CHAR_H_

# include <stdlib.h>
# include <SDL2/SDL.h>
# include "../Tools/tools.h"
# include "../ImageTreatment/filters.h"
#include <sys/types.h> 
#include <sys/stat.h> 
#include <math.h>

int *cutCharacters(SDL_Surface *img, char *directory);
int *cutCharactersItalic(SDL_Surface *img, char *directory);

# endif