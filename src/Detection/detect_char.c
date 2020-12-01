# include "detect_char.h"


int *cutCharacters(SDL_Surface *img, char *directory){  // Changed return type
    //Variables
    SDL_Surface *img_copy = copy_image(img);
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int fullWhite = 1;
    int firstCut = 1;

    // Using width = height * 0.5
    float averageCharLength = (img -> h)*0.5;
    int beginingCharPixel = 0;
    int endingCharPixel = 0;
    short nbChars = 1;

    // Initialisazing characters' positions array 
    unsigned int estimatedCharNumber = 0; // Stores the estimated number of characters to create a good size array
    estimatedCharNumber = (int) (img->w/averageCharLength);
    int *allPositions = calloc(estimatedCharNumber, sizeof(int));
    int currentIndex = 0; // Current index position of 'allPositions' array

    // Using line drawing system
    for (int j = 0; j < img -> w; j++)
    {
        fullWhite = fullWhiteHeightChar(img, j);

        if (!fullWhite && firstCut)
        {
            // Saving beginning index (exclusive position: where we will need to cut)
            allPositions[currentIndex] = j - 1;
            currentIndex ++;

            // Drawing lines
            int put_j = j != 0 ? j - 1 : 0; // Change: evaluates j to draw line 1 pixel before (better in theory but misses some characters)
            beginingCharPixel = j;
            //for (int k = 0; k < img -> h; k++)
            //{
            //    pixel = SDL_MapRGB(img_copy -> format, 0, 0, 255);
            //    putpixel(img_copy, put_j, k, pixel);
            //}
            firstCut = 0;
        }
        
        if(fullWhite && !firstCut) 
        {
            // Saving ending index (exclusive position: where we will need to cut)
            allPositions[currentIndex] = j;

            // Drawing lines
            endingCharPixel = j - 1;
            int actualCharLength = abs(endingCharPixel - beginingCharPixel + 1); // Added + 1
            //for (int i = 0; i < img -> h; i++)
            //{
            //    pixel = SDL_MapRGB(img_copy -> format, 0, 0, 255);
            //    putpixel(img_copy, j, i, pixel);
            //}
            firstCut = 1;

            // When the char is too long
            if (actualCharLength > 2*averageCharLength)
            {
                // Middle segmentation
                int middle = actualCharLength/2 + beginingCharPixel;
                if (middle < img -> w)
                {
                    //for (int i = 0; i < img -> h; i++)
                    //{
                    //    pixel = SDL_MapRGB(img_copy -> format, 255, 0, 0);
                    //    putpixel(img_copy, middle, i, pixel);
                    //}

                    allPositions[currentIndex] = middle + 1;
                    allPositions[currentIndex+1] = middle;
                    allPositions[currentIndex+2] = j;
                    currentIndex += 2;
                }
                nbChars += 2;
                averageCharLength = (averageCharLength*(nbChars-2) + actualCharLength)/nbChars;
            }
            else {
                nbChars += 1;
                averageCharLength = (averageCharLength*(nbChars-1) + actualCharLength)/nbChars;
            }
            currentIndex ++;
        }
        else if (!firstCut && j == img->w-1) {
            allPositions[currentIndex] = j;
            currentIndex ++;

            // Could draw line but useless
        }
    }

    allPositions[currentIndex] = -42;

    // Everything to save the updated line correctly
    mkdir(directory, 0777);
    char path[100];
    snprintf(path, 100, "%s/%s.bmp", directory, "line");
    SDL_SaveBMP(img_copy, path);
   
    return allPositions;
}

int *cutCharactersItalic(SDL_Surface *img, char *directory){
    unsigned int mod = 5;
    printf("Entering char cutting\n");
    //Variables
    SDL_Surface *img_copy = copy_image(img);
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int fullWhite = 1;
    int firstCut = 1;

    // Using width = height * 0.5
    double averageCharLength = (img -> h)*0.5;
    int beginingCharPixel = 0;
    int endingCharPixel = 0;
    short nbChars = 1;

    // Initialisazing characters' positions array 
    unsigned int estimatedCharNumber = 0; // Stores the estimated number of characters to create a good size array
    estimatedCharNumber = (int) (img->w/averageCharLength);
    int *allPositions = calloc(estimatedCharNumber*2, sizeof(int));
    int currentIndex = 0; // Current index position of 'allPositions' array

    // Using line drawing system
    for (int j = 0; j < img -> w; j++)
    {
        fullWhite = fullWhiteItalic(img, j, mod);

        if (!fullWhite && firstCut)
        {
            // Saving beginning index (exclusive position: where we will need to cut)
            allPositions[currentIndex] = j - 1;
            currentIndex ++;

            // Drawing lines
            int put_j = j != 0 ? j - 1 : 0; // Change: evaluates j to draw line 1 pixel before (better in theory but misses some characters)
            beginingCharPixel = j;
            int jj = j;
            for (int i = 0; i < img -> h && jj > -1; i++)
            {
                pixel = SDL_MapRGB(img_copy -> format, 0, 0, 255);
                putpixel(img_copy, jj, i, pixel);

                //Updating indexes
                if (i % mod == mod-1){
                    jj--;
                }
            }
            firstCut = 0;
        }
        
        if(fullWhite && !firstCut) 
        {
            // Saving ending index (exclusive position: where we will need to cut)
            allPositions[currentIndex] = j + 1;

            // Drawing lines
            endingCharPixel = j - 1;
            int actualCharLength = abs(endingCharPixel - beginingCharPixel + 1); // Added + 1
            int jj = j;
            for (int i = 0; i < img -> h && jj > -1; i++)
            {
                pixel = SDL_MapRGB(img_copy -> format, 0, 0, 255);
                putpixel(img_copy, jj, i, pixel);

                //Updating indexes
                if (i % mod == mod-1){
                    jj--;
                }
            }
            firstCut = 1;

            // When the char is too long
            if (actualCharLength > 2*averageCharLength)
            {
                // Middle segmentation
                int times = (int)round((double)actualCharLength/averageCharLength);
                for (char k = 1; k <= times; k++){
                    int jj = beginingCharPixel + k*actualCharLength/times;
                    if (jj < img->w) {
                        for (int i = 0; i < img -> h && jj > -1; i++)
                        {
                            pixel = SDL_MapRGB(img_copy -> format, 255, 0, 0);
                            putpixel(img_copy, jj, i, pixel);

                            //Updating indexes
                            if (i % mod == mod-1){
                                jj--;
                            }
                        }
                    }
                    if (k == times) {
                        allPositions[currentIndex] = j + 1;
                    }
                    else {
                        allPositions[currentIndex] = jj + 2;
                        allPositions[currentIndex+1] = jj + 2;
                        currentIndex+=2;
                    }
                }
                nbChars += times;
                averageCharLength = (averageCharLength*(nbChars-times) + actualCharLength)/nbChars;
            }
            else {
                nbChars += 1;
                averageCharLength = (averageCharLength*(nbChars-1) + actualCharLength)/nbChars;
            }
            currentIndex ++;
        }
        else if (!firstCut && j == img->w-1) {
            allPositions[currentIndex] = j;
            currentIndex ++;

            // Could draw line but useless
        }
    }
    printf("Ending char cutting loop\n");

    allPositions[currentIndex] = -42;

    // Everything to save the updated line correctly
    mkdir(directory, 0777);
    char path[100];
    snprintf(path, 100, "%s/%s.bmp", directory, "line");
    SDL_SaveBMP(img_copy, path);

    printf("Ending char cutting\n");
    return allPositions;
}
