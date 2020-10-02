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

            if ((r + g + b)/3 > 200)
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