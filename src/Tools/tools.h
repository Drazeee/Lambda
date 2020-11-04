# ifndef TOOLS_H_
# define TOOLS_H_

# include <stdlib.h>
# include <SDL2/SDL.h>
# include <err.h>

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

SDL_Surface* copy_image(SDL_Surface *img);

unsigned char fullWhiteHeight(SDL_Surface *img, int width_index);

unsigned char fullWhiteWidth(SDL_Surface *img, int height_index);

unsigned char fullWhiteHeightChar(SDL_Surface *img, int width_index);

unsigned char fullWhiteWidthChar(SDL_Surface *img, int height_index);

# endif