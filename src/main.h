#ifndef MAIN_I
#define MAIN_I

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "Detection/segmentation.h"
#include "Detection/detect_char.h"
#include <dirent.h>
#include <gtk-3.0/gtk/gtk.h>
#include "ImageTreatment/filters.h"



int main(int argc, char **argv);
char *characterSegmentation(char *path, char *destination, int print);
char *characterSegmentationWithoutLoad(SDL_Surface *imgDefault, char *destination, int print);
char *lineSegmentationWithoutLoad(SDL_Surface *imgDefault, char *destination, int print);
char *paragraphSegmentation(char *path, char *destination, int print);
void array_print(int *begin);
int remove_directory(const char *path);

#endif
