#ifndef TOOLS_H_
#define TOOLS_H_
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <err.h>
#include <math.h>

SDL_Surface *resize(SDL_Surface *img, int x, int y);

SDL_Surface *rotation(SDL_Surface *img, double teta, int x0, int y0);

SDL_Surface *autoRotation(SDL_Surface *img);

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

SDL_Surface* copy_image(SDL_Surface *img);

unsigned char fullWhiteHeight(SDL_Surface *img, int width_index);

unsigned char fullWhiteWidth(SDL_Surface *img, int height_index);

unsigned char fullWhiteHeightChar(SDL_Surface *img, int width_index);

unsigned char fullWhiteWidthChar(SDL_Surface *img, int height_index);

unsigned char fullWhiteItalic(SDL_Surface *img, int width_index, 
	unsigned int mod);

# endif
