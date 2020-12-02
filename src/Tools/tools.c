# include "tools.h"

/* Variables */
Uint32 pixel;
Uint8 r;
Uint8 g;
Uint8 b;


double toradians(double teta) {
    return (teta * M_PI) / 180;
}

typedef struct coords {
    int x;
    int y;
} coords;

coords shear(double angle, int x, int y) {
    double tangent = tan(angle/2);

    double new_x = round(x-y * tangent);
    double new_y = (double)y;

    new_y = round(new_x * sin(angle) + new_y);

    new_x = round(new_x - new_y * tangent);

    coords result;
    result.x = round(new_x);
    result.y = round(new_y);
    return result;
}

SDL_Surface *rotation(SDL_Surface *img, double teta, int x0, int y0) {
    SDL_Surface *imgCopy = SDL_CreateRGBSurface(0, img->w, img->h, 32,
        0, 0, 0, 0);
    // Full white image
    pixel = SDL_MapRGB(img->format, 255, 255, 255);
    for (int i = 0; i < img->w; i++) {
        for (int j = 0; j < img->h; j++) {
            putpixel(imgCopy, i, j, pixel);
        }
    }

    teta = toradians(teta);

    int original_center_w = round(((img->w + 1) / 2) - 1);
    int original_center_h = round(((img->h + 1) / 2) - 1);


    for (int x = 0; x < img->w; x++) {
        for (int y = 0; y < img->h; y++) {
            int x2 = round(cos(teta) * (double)(x - x0) + 
				sin(teta) * (double)(y - y0));
            int y2 = round(cos(teta) * (double)(y - y0) - 
				sin(teta) * (double)(x - x0));

            // int new_x = img->w - 1 - x - original_center_w;
            // int new_y = img->w - 1 - x - original_center_h;

            // coords new_coords = shear(teta, new_x, new_y);

            // int x2 = original_center_w - new_coords.x;
            // int y2 = original_center_h - new_coords.y;

            x2 += x0;
            y2 += y0;

            if (x2 > -1 && x2 < img->w && y2 > -1 && y2 < img->h ) {
                putpixel(imgCopy, x2, y2, getpixel(img, x, y));
            }
        }
    }

    return imgCopy;
}


SDL_Surface *autoRotation(SDL_Surface *img) {
    // Searching bottom left pivot point

    coords leftpivot;
    for (int i = img->h - 1; i > -1; i--)
    {
        unsigned char fullWhite = 1;
        for (int j = 0; j < img -> w; j++)
        {
            Uint32 pixel = getpixel(img, j, i);
            SDL_GetRGB(pixel, img -> format, &r, &g, &b);
            if (r < 250 || g < 250 || b < 250)
            {
                fullWhite = 0;
                leftpivot.x = j;
                leftpivot.y = i;
                break;
            }
        }
    }
    

    // Searching upper right point

    coords rightpivot;
    for (int i = img->w - 1; i > -1; i--)
    {
        unsigned char fullWhite = 1;
        for (int j = 0; j < img -> h; j++)
        {
            Uint32 pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img -> format, &r, &g, &b);
            if (r < 250 || g < 250 || b < 250)
            {
                fullWhite = 0;
                rightpivot.x = i;
                rightpivot.y = j;
                break;
            }
        }
    }
    

    double teta = atan((double)(rightpivot.y - leftpivot.y) / 
		(double)(rightpivot.x - leftpivot.x));
    int original_center_w = round(((img->w + 1) / 2) - 1);
    int original_center_h = round(((img->h + 1) / 2) - 1);

    teta = round(teta * 180 / M_PI);

    printf("%f, (%i, %i)\n", teta, original_center_w, original_center_h);

    SDL_Surface *newImage = rotation(img, teta,
		original_center_w, original_center_h);

    return newImage;
}

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
				putpixel(imgCopy, i, j, 
					getpixel(img, (int)coordX, (int)coordY));
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

unsigned char fullWhiteItalic(SDL_Surface *img, int width_index, 
	unsigned int mod) 
{
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
