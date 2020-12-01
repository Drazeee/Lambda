# ifndef SEGMENTATION_H_
# define SEGMENTATION_H_

# include <stdlib.h>
# include <SDL2/SDL.h>
# include "../Tools/tools.h"
# include "../ImageTreatment/filters.h"
#include <sys/types.h> 
#include <sys/stat.h>
#include "../Recognition/recognition.h"
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include "../main.h"

SDL_Surface *cutLine(SDL_Surface *img, int first);
void linesToSurface(SDL_Surface *img);
SDL_Surface *cutColumn(SDL_Surface *img);
SDL_Surface *cutWord(SDL_Surface *img);
char *convertColumns(SDL_Surface *img, char *directory);
char *removeLines(SDL_Surface *img, char *directory, int isLineSegmentation);
char *removeLinesForCharacters(SDL_Surface *img, char *directory, int *allPos);
void *removeLinesForItalicChars(SDL_Surface *img, char *directory, int *allPos);
void removeLinesForWords(SDL_Surface *img, char *directory);
int *wordPositions(SDL_Surface *img);


# endif
