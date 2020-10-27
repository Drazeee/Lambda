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

            if ((r + g + b)/3 > 190)
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


SDL_Surface *grayscale(SDL_Surface *img, char save, char *path) {
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;

    SDL_Surface *img_copy = copy_image(img);

    Uint8 average;


    for (int i = 0; i < img_copy -> w; i++)
    {
        for (int j = 0; j < img_copy -> h; j++)
        {
            pixel = getpixel(img_copy, i, j);
            SDL_GetRGB(pixel, img_copy->format, &r, &g, &b);
            average = 0.3*r + 0.59*g + 0.11*b;
            pixel = SDL_MapRGB(img_copy->format, average, average, average);
            putpixel(img_copy, i, j, pixel);
        }
    }

    if (save) {
        SDL_SaveBMP(img_copy, path);
    }
    return img_copy;
}


SDL_Surface *convolute(SDL_Surface *img, float mask[], int num_rows, int num_cols) {
    int width = img -> w;
    int height = img -> h;
    SDL_Surface *imgCopy = copy_image(img);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            float gradR = 0;
            float gradG = 0;
            float gradB = 0;
            Uint32 pixel;
            for (int k = 0; k < num_rows; k++)
            {
                for (int l = 0; l < num_cols; l++)
                {
                    if (i + k - num_rows / 2 > -1 && i + k - num_rows / 2 < width && j + l - num_rows / 2 > -1 && j + l - num_rows / 2 < height) {
                        Uint8 r;
                        Uint8 g;
                        Uint8 b;
                        pixel = getpixel(imgCopy, i + k - num_rows / 2, j + l - num_rows / 2);
                        SDL_GetRGB(pixel, imgCopy->format, &r, &g, &b);
                        gradR += (float)r * mask[k * num_cols + l];
                        gradG += (float)g * mask[k * num_cols + l];
                        gradB += (float)b * mask[k * num_cols + l];
                    }
                }
            }
            gradB = gradB < 256 ? gradB : 255;
            gradR = gradR < 256 ? gradR : 255;
            gradG = gradG < 256 ? gradG : 255;
            gradB = gradB > -1 ? gradB : 0;
            gradR = gradR > -1 ? gradR : 0;
            gradG = gradG > -1 ? gradG : 0;
            pixel = SDL_MapRGB(imgCopy->format, (int)gradR, (int)gradG, (int)gradB);
            putpixel(imgCopy, i, j, pixel);
        }
    }
    return imgCopy;
}


/* Grayscale image */
SDL_Surface *histogramNormalization(SDL_Surface *img) {
    unsigned long nbPixels = img->w * img->h;
    SDL_Surface *imgCopy = copy_image(img);


    // Initialization of all values to 0
    int histogram[256];
    for (short i = 0; i < 256; i++)
    {
        histogram[i] = 0;
    }


    // Create histogram of all pixels values
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint32 pixel;
    for (int i = 0; i < img->w; i++)
    {
        for (int j = 0; j < img->h; j++)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            histogram[r] += 1;
        }
    }
    
    // Apply formule to all pixels
    float normalizationConstant = 255.0/(float)nbPixels;

    for (int i = 0; i < img->w; i++)
    {
        for (int j = 0; j < img->h; j++)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            Uint32 newRGBValue = 0;
            for (short k = 0; k < r; k++)
            {
                newRGBValue += histogram[k];
            }
            newRGBValue = (int)(normalizationConstant * (float)newRGBValue);
            pixel = SDL_MapRGB(img->format, newRGBValue, newRGBValue, newRGBValue);
            putpixel(imgCopy, i, j, pixel);
        }
    }
    
    return imgCopy;
}

/* Noise reduction function
/* img: the image */

SDL_Surface *noiseReduction(SDL_Surface *img) {
    // Variables
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint32 pixel;

    SDL_Surface *imgCopy = copy_image(img);


    // Foreach pixels
    for (int i = 0; i < img->w; i++)
    {
        for (int j = 0; j < img->h; j++)
        {
            // Sum of each neighbors pixels

            Uint32 sum = 0;
            short count = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k > -1 && 
                        i + k < img->w && 
                        j + l > - 1 && 
                        j + l < img->h) 
                    {
                        pixel = getpixel(img, i + k, j + l);
                        SDL_GetRGB(pixel, img->format, &r, &g, &b);
                        sum += r;
                        count += 1;
                    }
                }
            }

            // Average of pixels values to get the new current pixel value
            sum /= count;
            pixel = SDL_MapRGB(img->format, sum, sum, sum);
            putpixel(imgCopy, i, j, pixel);
        }
    }
    return imgCopy;
}