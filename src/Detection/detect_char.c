# include "detect_char.h"

SDL_Surface *cutCharacters(SDL_Surface *img){

    //Variables
    SDL_Surface *img_copy = copy_image(img);
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int fullWhite = 1;
    int firstCut = 1;
    int averageCharLength = 0;
    int beginingCharPixel = 0;
    int endingCharPixel = 0;
    short nbChars = 0;

    // for (int j = 0; j < img -> w; j++)
    // {
    //     fullWhite = 1;
    //     int jj = j;
    //     for (int i = 0; i < img -> h && jj > -1; i++)
    //     {
    //         Uint32 pixel = getpixel(img, j, i);
    //         SDL_GetRGB(pixel, img -> format, &r, &g, &b);
    //         if (r < 100  || g < 100 || b < 100 )
    //         {
    //             fullWhite = 0;
    //             break;
    //         }

    //         //Updating indexes
    //         if (i % 3 == 2){
    //             jj--;
    //         }
    //     }

    //     if (!fullWhite && firstCut)
    //     {
    //         // Cuts lines
    //         /* NON ITALIC VERSION
    //         for (int k = 0; k < img -> h; k++)
    //         {
    //             pixel = SDL_MapRGB(img_copy -> format, 255, 0, 0);
    //             putpixel(img_copy, j, k, pixel);
    //         }
    //         */

    //         // ITALIC VERSION

    //         int jj = j;
    //         for (int i = 0; i < img -> h && jj > -1; i++)
    //         {
    //             pixel = SDL_MapRGB(img_copy -> format, 0, 0, 255);
    //             putpixel(img_copy, jj, i, pixel);

    //             //Updating indexes
    //             if (i % 3 == 2){
    //                 jj--;
    //             }
    //         }
    //         firstCut = 0;
    //         printf("first cut");
    //     }
        
    //     if(fullWhite && !firstCut) 
    //     {
    //         // Cuts lines
    //         int jj = j;
    //         for (int i = 0; i < img -> h && jj > -1; i++)
    //         {
    //             pixel = SDL_MapRGB(img_copy -> format, 0, 0, 255);
    //             putpixel(img_copy, jj, i, pixel);

    //             //Updating indexes
    //             if (i % 3 == 2){
    //                 jj--;
    //             }
    //         }
    //         firstCut = 1;
    //         printf("second cut");
    //     }
        
        
    // }

    for (int j = 0; j < img -> w; j++)
    {
        fullWhite = 1;
        for (int i = 0; i < img -> h; i++)
        {
            Uint32 pixel = getpixel(img, j, i);
            SDL_GetRGB(pixel, img -> format, &r, &g, &b);
            if (r < 150  || g < 150 || b < 150 )
            {
                fullWhite = 0;
                break;
            }
        }

        if (!fullWhite && firstCut)
        {
            // Cuts lines

            // NON ITALIC VERSION
            beginingCharPixel = j;
            for (int k = 0; k < img -> h; k++)
            {
                pixel = SDL_MapRGB(img_copy -> format, 0, 0, 255);
                putpixel(img_copy, j, k, pixel);
            }
            firstCut = 0;
            printf("first cut");
        }
        
        if(fullWhite && !firstCut) 
        {
            // Cuts lines
            
            endingCharPixel = j-1;
            int actualCharLength = abs(endingCharPixel - beginingCharPixel);
            for (int i = 0; i < img -> h; i++)
            {
                pixel = SDL_MapRGB(img_copy -> format, 0, 0, 255);
                putpixel(img_copy, j, i, pixel);
            }
            firstCut = 1;
            printf("second cut");

            // Traitement dans le cas ou le caratère découpé est trop long 
            if (actualCharLength >= 1.9*averageCharLength)
            {
                // Découpage au milieu

                int middle = actualCharLength/2 + beginingCharPixel;
                if (middle < img -> w)
                {
                    for (int i = 0; i < img -> h; i++)
                    {
                        pixel = SDL_MapRGB(img_copy -> format, 255, 0, 0);
                        putpixel(img_copy, middle, i, pixel);
                    }
                }
            }
            else {
                nbChars += 1;
                averageCharLength = (averageCharLength*(nbChars-1) + actualCharLength)/nbChars;
            }
        }
    }


    SDL_SaveBMP(img_copy, "new_image_char.bmp");
    return img_copy;
}