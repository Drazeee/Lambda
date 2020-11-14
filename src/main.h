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
#include "Interface/interface.h"


int fullSegmentation(char *imagePath);
int main(int argc, char **argv);
char *characterSegmentation(char *path, char *destination, int print);

#endif