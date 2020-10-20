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
                    if (r < 200 || g < 200 || b < 200)
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
    removeLines(img_copy, "lines");
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

/*
 * Removes green separating lines between paragraphs and lines and stores each of them in a folder
 * Param:
 *      - img : image to compute
 *      - directory : the directory name to store the different parts cut
 */

void removeLines(SDL_Surface *img, char *directory) {
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
        mkdir(directory, 0777);
        char path[22];
        snprintf(path, 22, "%s/%d.bmp", directory, paragraphsCount);
        paragraphsCount++;
        SDL_SaveBMP(newImage, path);
    }
}

/*
 * Removes blue separating lines between characters and stores each of them in a folder
 * Param:
 *      - img : image to compute
 *      - directory : the directory name to store the different parts cut
 */

void removeLinesForCharacters(SDL_Surface *img, char *directory) {
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int start = -1;
    int stop = -1;
    int positions[300];
    int pos = 0;

    for (int j = 0; j < img -> w; j++)
    {
        pixel = getpixel(img, j, 0);
        SDL_GetRGB(pixel, img -> format, &r, &g, &b);

        if (start == -1 && ((r < 200 && g < 200 && b == 255) || (r == 255 && g < 200 && b < 200))) {
            start = j;
        }

        else if (start != -1 && ((r < 200 && g < 200 && b == 255) || (r == 255 && g < 200 && b < 200))) {
            stop = j;
            positions[pos] = start;
            positions[pos + 1] = stop;
            pos += 2;
            start = -1;
            stop = -1;
            if (r == 255){
                j--;
            }
        }
    }
    
    for (int i = 0; i < pos; i+=2) {
        int width = positions[i + 1] - positions[i] - 1;
        SDL_Surface *newImage = SDL_CreateRGBSurface(0, width, img -> h, 32,
        0, 0, 0, 0);

        // Parcours le character dans l'image initial (encore entre deux barres bleues) pour le copier dans une image seule
        for (int y = 0; y < img -> h; y++)
        {
            for (int x = 0; x < width; x++)
            {
                putpixel(newImage, x, y , getpixel(img, positions[i] + x + 1, y));
            }
            
        }

        printf("tout début\n");

        // Parcours de l'image seule pour enlever les pixels blancs en haut et en bas de l'image
        unsigned int cut_top = 0;
        unsigned int cut_bottom = 0;

        // De haut en bas (cut_top)
        for (unsigned int h = 0; h < newImage -> h; h++)
        {
            unsigned char fullwhite = 1;
            for (unsigned int w = 0; w < newImage -> w && fullwhite; w++)
            {
                pixel = getpixel(newImage, w, h);
                SDL_GetRGB(pixel, newImage -> format, &r, &g, &b);
                fullwhite = r > 249 && g > 249 && b > 249;
            }

            // Coupe l'image en haut
            if (!fullwhite) {

                // Coupe 1 index plus haut et 0 sinon
                cut_top = h;
                break;
            }
        }

        printf("cut_top done (val: %u, height: %i)\n", cut_top, newImage -> h);

        // De bas en haut (cut_bottom)
        for (int h = (newImage -> h) - 1; h >= 0; h--)
        {
            unsigned char fullwhite = 1;
            for (unsigned int w = 0; w < newImage -> w && fullwhite; w++)
            {
                pixel = getpixel(newImage, w, h);
                SDL_GetRGB(pixel, newImage -> format, &r, &g, &b);
                fullwhite = r > 249 && g > 249 && b > 249;
            }

            // Coupe l'image en bas
            if (!fullwhite) {

                // Coupe 1 index plus bas et newImage->h-1 sinon
                cut_bottom = h;
                break;
            }
        }

        printf("cut_bottom done (val: %u)\n", cut_bottom);

        // Nouvelle image du caractère sans le haut et bas
        SDL_Surface *newImageSmall;
        newImageSmall = SDL_CreateRGBSurface(0, newImage -> w, cut_bottom - cut_top + 1, 32,
        0, 0, 0, 0);
        for (int y = cut_top; y < cut_bottom + 1; y++)
        {
            for (int x = 0; x < newImage -> w; x++)
            {
                putpixel(newImageSmall, x, y - cut_top, getpixel(newImage, x, y));
            }
        }

        printf("finished\n");


        // Ajoute l'image sur une un fond blanc de 32x32
        // TODO: Redimensionner si plus grand que 32x32

        SDL_Surface *lastImage = SDL_CreateRGBSurface(0, 32, 32, 32,
        0, 0, 0, 0);

        pixel = SDL_MapRGB(newImageSmall -> format, 255, 255, 255);

        for (int i = 0; i < 32; i++)
        {
            for (int j = 0; j < 32; j++)
            {
                putpixel(lastImage, i, j, pixel);
            }
            
        }
        

        for (int y = 0; y < newImageSmall -> h; y++)
        {
            for (int x = 0; x < newImageSmall -> w; x++)
            {
                putpixel(lastImage, x, y, getpixel(newImageSmall, x, y));
            }
        }
        
        // Enregistre l'image finale dans le dossier directory
        mkdir(directory, 0777);
        char path[22];
        snprintf(path, 22, "%s/%d.bmp", directory, paragraphsCount);
        paragraphsCount++;
        SDL_SaveBMP(lastImage, path);
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

        removeLines(newImage, "paragraphs");
    }
    
}