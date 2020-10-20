#include "filters.h"

SDL_Surface *blackAndWhite(SDL_Surface *img) {
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;


    for (int i = 0; i < img -> w; i++)
    {
        for (int j = 0; j < img -> h; j++)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img -> format, &r, &g, &b);

            if ((r + g + b)/3 > 140)
            {
                pixel = SDL_MapRGB(img -> format, 255, 255, 255);
                putpixel(img, i, j, pixel);
            }
            else {
                pixel = SDL_MapRGB(img -> format, 0, 0, 0);
                putpixel(img, i, j, pixel);
            }
        }
        
    }
    
    return img;
}


SDL_Surface *grayscale(SDL_Surface *img) {
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;

    Uint8 average;


    for (int i = 0; i < img -> w; i++)
    {
        for (int j = 0; j < img -> h; j++)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            average = 0.3*r + 0.59*g + 0.11*b;
            pixel = SDL_MapRGB(img->format, average, average, average);
            putpixel(img, i, j, pixel);
        }
    }

    return img;
}