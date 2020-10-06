# include "segmentation.h"

/* insert red line after and before lines */

SDL_Surface *cutLine(SDL_Surface *img) {
    // Variables
    int fullWhite = 1;
    int firstCut = 1;
    int endText = -1; //Gets the first pixel (height wise) with full white width
    int beginingText = -1; //Gets the first pixel without full white width after several full white 
    int lastLineHeight = -1; //Stores the number of pixels from the last text line
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    SDL_Surface *img_copy = copy_image(img);


    // Code
    for (int i = 0; i < img -> h; i++)
    {
        fullWhite = 1;

        //Returns whether img's width is full of white pixels or not
        for (int j = 0; j < img -> w; j++)
        {
            Uint32 pixel = getpixel(img, j, i);
            SDL_GetRGB(pixel, img -> format, &r, &g, &b);
            if (r < 250 || g < 250 || b < 250)
            {
                fullWhite = 0;
                break;
            }
        }

        if (!fullWhite && firstCut)
        {   
            beginingText = i;

            // Begins paragraphs
            if (endText == -1 || (lastLineHeight <= abs(endText - beginingText) && lastLineHeight > 6)){
                for (int k = 0; k < img -> w; k++)
                {
                    pixel = SDL_MapRGB(img_copy -> format, 0, 255, 0);
                    putpixel(img_copy, k, beginingText, pixel);
                }   
            }

            // Cuts lines
            /*
            for (int k = 0; k < img -> w; k++)
            {
                pixel = SDL_MapRGB(img_copy -> format, 255, 0, 0);
                putpixel(img_copy, k, i, pixel);
            }
            */
            firstCut = 0;
        }
        
        if(fullWhite && !firstCut) {
            endText = i-1;
            lastLineHeight = endText - beginingText;

            // Ends paragraphs
            int ii = i;
            do
            {
                for (int j = 0; j < img -> w; j++)
                {
                    Uint32 pixel = getpixel(img, j, ii);
                    SDL_GetRGB(pixel, img -> format, &r, &g, &b);
                    if (r < 250 || g < 250 || b < 250)
                    {
                        fullWhite = 0;
                        break;
                    }
                }
                ii++;
            } while (fullWhite);
            if ((ii - endText >= lastLineHeight && ii - endText > 6) || ii >= img -> h) {
                //Draw line
                for (int k = 0; k < img -> w; k++)
                {
                    pixel = SDL_MapRGB(img_copy -> format, 0, 255, 0);
                    putpixel(img_copy, k, i, pixel);
                }
            }
            
            // Cuts lines
            /*
            for (int k = 0; k < img -> w; k++)
            {
                pixel = SDL_MapRGB(img_copy -> format, 255, 0, 0);
                putpixel(img_copy, k, i, pixel);
            }*/
            firstCut = 1;
        }
        
    }
    return img_copy;
}


SDL_Surface *cutColumn(SDL_Surface *img) {
    int fullWhite = 1;
    int firstCut = 1;
    int endText = -1; //Gets the first pixel (height wise) with full white width
    int beginingText = -1; //Gets the first pixel without full white width after several full white 
    int lastLineHeight = -1; //Stores the number of pixels from the last text line
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    SDL_Surface *img_copy = copy_image(img);

    for (int i = 0; i < img -> w; i++) 
    {
        fullWhite = 1;
        //Returns whether img's width is full of white pixels or not
        for (int j = 0; j < img -> h; j++)
        {
            Uint32 pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img -> format, &r, &g, &b);
            if (r < 250 || g < 250 || b < 250)
            {
                fullWhite = 0;
                break;
            }
        }

        if (!fullWhite && firstCut)
        {   
            beginingText = i;

            // Begins paragraphs
            if (endText == -1 || lastLineHeight <= abs(endText - beginingText)){
                for (int k = 0; k < img -> h; k++)
                {
                    pixel = SDL_MapRGB(img_copy -> format, 0, 255, 0);
                    putpixel(img_copy, beginingText, k, pixel);
                }   
            }
            firstCut = 0;
        }
        
        if(fullWhite && !firstCut) {
            endText = i-1;
            lastLineHeight = 0.03 * img -> w;

            // Ends paragraphs
            int ii = i;
            do
            {
                for (int j = 0; j < img -> h; j++)
                {
                    Uint32 pixel = getpixel(img, ii, j);
                    SDL_GetRGB(pixel, img -> format, &r, &g, &b);
                    if (r < 250 || g < 250 || b < 250)
                    {
                        fullWhite = 0;
                        break;
                    }
                }
                ii++;
            } while (fullWhite);
            if (ii - endText >= 0.03 * img -> w || ii >= img -> w) {
                //Draw line
                for (int k = 0; k < img -> h; k++)
                {
                    pixel = SDL_MapRGB(img_copy -> format, 0, 255, 0);
                    putpixel(img_copy, i, k, pixel);
                }
            }
            firstCut = 1;
        }
        
    }
    return img_copy;
}


int paragraphsCount = 0;

void removeLines(SDL_Surface *img) {
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int start = -1;
    int stop = -1;
    int positions[40];
    int pos = 0;

    for (int i = 0; i < img -> h; i++)
    {
        pixel = getpixel(img, 0, i);
        SDL_GetRGB(pixel, img -> format, &r, &g, &b);

        if (start == -1 && (r < 250 && g == 255 && b < 250)) {
            start = i;
        }

        else if (start != -1 && (r < 250 && g == 255 && b < 250)) {
            stop = i;
            positions[pos] = start;
            positions[pos + 1] = stop;
            pos += 2;
            start = -1;
            stop = -1;
        }
    }
    
    for (int i = 0; i < pos; i+=2) {
        int height = positions[i + 1] - positions[i] - 1;
        SDL_Surface *newImage = SDL_CreateRGBSurface(0, img -> w, height, 32,
        0, 0, 0, 0);
        for (int x = 0; x < img -> w; x++)
        {
            for (int y = 0; y < height; y++)
            {
                putpixel(newImage, x, y , getpixel(img,  x, positions[i] + y + 1));
            }
            
        }
        mkdir("paragraphs", 0777);
        char path[22];
        snprintf(path, 22, "paragraphs/%d.bmp", paragraphsCount);
        paragraphsCount++;
        SDL_SaveBMP(newImage, path);
    }
}

void convertColumns(SDL_Surface *img)
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int start = -1;
    int stop = -1;
    int positions[40];
    int pos = 0;

    for (int i = 0; i < img -> w; i++)
    {
        pixel = getpixel(img, i, 0);
        SDL_GetRGB(pixel, img -> format, &r, &g, &b);

        if (start == -1 && (r < 250 && g == 255 && b < 250)) {
            start = i;
        }

        else if (start != -1 && (r < 250 && g == 255 && b < 250)) {
            stop = i;
            positions[pos] = start;
            positions[pos + 1] = stop;
            pos += 2;
            start = -1;
            stop = -1;
        }
    }
    

    for (int i = 0; i < pos; i+=2)
    {
        int width = positions[i + 1] - positions[i] - 1;
        SDL_Surface *newImage = SDL_CreateRGBSurface(0, width, img -> h, 32,
        0, 0, 0, 0);
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < img -> h; y++)
            {
                putpixel(newImage, x, y , getpixel(img, positions[i] + x + 1, y));
            }
            
        }
        newImage = cutLine(newImage);

        removeLines(newImage);
    }
    
}