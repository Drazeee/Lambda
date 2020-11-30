# include "tools.h"

/* Variables */
Uint32 pixel;
Uint8 r;
Uint8 g;
Uint8 b;


SDL_Surface *resize(SDL_Surface *img, int x, int y) {

	SDL_Surface *imgCopy = SDL_CreateRGBSurface(0, x, y, 32,
        0, 0, 0, 0);
	int width = img->w;
	int height = img->h;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			double coordX = (double)i * ((double)width/(double)x);
			double coordY = (double)j * ((double)height/(double)y);
			if (coordX < img->w-1 && coordY < img->h-1){
				putpixel(imgCopy, i, j, getpixel(img, (int)coordX, (int)coordY));
			}
		}
	}
	return imgCopy;
}



/* Classic tools */
static inline Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y)
{
 int bpp = surf -> format -> BytesPerPixel;
 return (Uint8*)surf -> pixels + y * surf -> pitch + x * bpp;
}

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y)
{
 Uint8 *p = pixelref(surface, x, y);
 switch(surface -> format -> BytesPerPixel) {
 case 1:
   return *p;
 case 2:
   return *(Uint16 *)p;
 case 3:
   if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
     return p[0] << 16 | p[1] << 8 | p[2];
   else
     return p[0] | p[1] << 8 | p[2] << 16;
 case 4:
   return *(Uint32 *)p;
 }
 return 0;
}

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
 Uint8 *p = pixelref(surface, x, y);
 switch(surface -> format -> BytesPerPixel) {
 case 1:
   *p = pixel;
   break;
 case 2:
   *(Uint16 *)p = pixel;
   break;
 case 3:
   if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
     p[0] = (pixel >> 16) & 0xff;
     p[1] = (pixel >> 8) & 0xff;
     p[2] = pixel & 0xff;
   } else {
     p[0] = pixel & 0xff;
     p[1] = (pixel >> 8) & 0xff;
     p[2] = (pixel >> 16) & 0xff;
   }
   break;
 case 4:
   *(Uint32 *)p = pixel;
   break;
 }
}


/* Copy a SDL_Surface */
SDL_Surface* copy_image(SDL_Surface *img)
{
  Uint32 pixel;
  SDL_Surface* copy;
  copy = SDL_CreateRGBSurface(0,
                              img -> w,
                              img -> h,
                              img -> format -> BitsPerPixel,0,0,0,0);
  for(int i = 0; i < img -> w; i++)
  {
    for(int j = 0;j < img -> h; j++)
    {
      pixel = getpixel(img, i, j);
      putpixel(copy, i, j, pixel);
    }
  }
  return(copy);
}

unsigned char fullWhiteHeight(SDL_Surface *img, int width_index) {
    unsigned char fullWhite = 1;
    for (int j = 0; j < img -> h; j++)
    {
        Uint32 pixel = getpixel(img, width_index, j);
        SDL_GetRGB(pixel, img -> format, &r, &g, &b);
        if (r < 250 || g < 250 || b < 250)
        {
            fullWhite = 0;
            break;
        }
    }
    return fullWhite;
}

unsigned char fullWhiteWidth(SDL_Surface *img, int height_index) {
    unsigned char fullWhite = 1;
    for (int j = 0; j < img -> w; j++)
    {
        Uint32 pixel = getpixel(img, j, height_index);
        SDL_GetRGB(pixel, img -> format, &r, &g, &b);
        if (r < 250 || g < 250 || b < 250)
        {
            fullWhite = 0;
            break;
        }
    }
    return fullWhite;
}

unsigned char fullWhiteHeightChar(SDL_Surface *img, int width_index) {
    unsigned char fullWhite = 1;
    for (int j = 0; j < img -> h; j++)
    {
        Uint32 pixel = getpixel(img, width_index, j);
        SDL_GetRGB(pixel, img -> format, &r, &g, &b);
        if (r < 100 || g < 100 || b < 100)
        {
            fullWhite = 0;
            break;
        }
    }
    return fullWhite;
}

unsigned char fullWhiteWidthChar(SDL_Surface *img, int height_index) {
    unsigned char fullWhite = 1;
    for (int j = 0; j < img -> w; j++)
    {
        Uint32 pixel = getpixel(img, j, height_index);
        SDL_GetRGB(pixel, img -> format, &r, &g, &b);
        if (r < 100 || g < 100 || b < 100)
        {
            fullWhite = 0;
            break;
        }
    }
    return fullWhite;
}

unsigned char fullWhiteItalic(SDL_Surface *img, int width_index, unsigned int mod) {
    unsigned char fullWhite = 1;
    for (int i = 0; i < img -> h && width_index > -1; i++)
    {
        Uint32 pixel = getpixel(img, width_index, i);
        SDL_GetRGB(pixel, img -> format, &r, &g, &b);
        if (r < 100 || g < 100 || b < 100)
        {
            fullWhite = 0;
            break;
        }

        //Updating indexes
        if (i % mod == mod-1){
            width_index--;
        }
    }
	return fullWhite;
}
