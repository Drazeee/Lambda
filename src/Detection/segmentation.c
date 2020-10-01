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
            if (r != 255 || g != 255 || b != 255)
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
                for (int k = 0; k < img -> w; k++)
                {
                    pixel = SDL_MapRGB(img_copy -> format, 0, 255, 0);
                    putpixel(img_copy, k, beginingText, pixel);
                }   
            }

            // Cuts lines
            for (int k = 0; k < img -> w; k++)
            {
                pixel = SDL_MapRGB(img_copy -> format, 255, 0, 0);
                putpixel(img_copy, k, i - 1, pixel);
            }
            firstCut = 0;
            printf("first cut");
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
                    if (r != 255 || g != 255 || b != 255)
                    {
                        fullWhite = 0;
                        break;
                    }
                }
                ii++;
            } while (fullWhite);
            if (ii - endText >= lastLineHeight || ii >= img -> h) {
                //Draw line
                for (int k = 0; k < img -> w; k++)
                {
                    pixel = SDL_MapRGB(img_copy -> format, 0, 255, 0);
                    putpixel(img_copy, k, i - 1, pixel);
                }
            }
            
            // Cuts lines
            for (int k = 0; k < img -> w; k++)
            {
                pixel = SDL_MapRGB(img_copy -> format, 255, 0, 0);
                putpixel(img_copy, k, i, pixel);
            }
            firstCut = 1;
            printf("second cut");
        }
        
    }
    SDL_SaveBMP(img_copy, "new_image.bmp");
    return img_copy;
}


/*void lineToSurface(SDL_Surface *img) {
    // Variables
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int firstCut;
    int lastCut = 0;


    //Code
    for(int i = 0; i < (img -> h); i++) {
        // If i is less than the last cut line and the latter has been modified
        if(i != 0 && i <= lastCut)
        {
            continue;
        }

        // Get first pixel of each line
        pixel = getpixel(img, 0, j);
        SDL_GetRGB(pixel, img -> format, &r, &g, &b);

        if(r == 255 && b == 0 && g == 0)
        {
        firstCut = i + 1;

        for(int j = firstCut + 1; j < (img -> h); j++)
        {
            pixel = getpixel(img, 0, j);
            SDL_GetRGB(pixel, img -> format, &r, &g, &b);

            //Detect the second line
            if(r == 255 && b==0 && g == 0)
            {
                lastCut = j;
                //Isolate into a surface the linecut
                cuttedSurface(img, firstCut, lastCut, net);
                break;
            }
        }
    }
}*/