# include "segmentation.h"


/* insert red line after and before lines */
// Use removeLines after to save each line/paragraph
SDL_Surface *cutLine(SDL_Surface *img, int first) {
    // Variables
    int fullWhite = 1;
    int firstCut = 1;
    //Gets the first pixel (height wise) with full white width
    int endText = -1;
    //Gets the first pixel without full white width after several full white 
    int beginingText = -1;
    //Stores the number of pixels from the last text line
    int lastLineHeight = -1;
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    SDL_Surface *img_copy = copy_image(img);


    // Code
    for (int i = 0; i < img -> h; i++)
    {

        //Returns whether img's width is full of white pixels or not
        fullWhite = fullWhiteWidth(img, i);

        if (!fullWhite && firstCut)
        {   
            beginingText = i;

            int beginingTextIndex = beginingText != 0 ? 
				beginingText - 1 : beginingText;

            // Begins paragraphs
            if (!first) {
                if ((endText == -1 || 
					(lastLineHeight * 0.2 <= abs(endText - beginingText) && 
					lastLineHeight > 3)) && i != 0)
				{
                    for (int k = 0; k < img -> w; k++)
                    {
                        pixel = SDL_MapRGB(img_copy -> format, 0, 255, 0);
                        putpixel(img_copy, k, beginingTextIndex, pixel);
                    }   
                }
            }
            else {
                if ((endText == -1 || 
					(lastLineHeight <= abs(endText - beginingText) && 
					lastLineHeight > 3)) && i != 0)
				{
                    for (int k = 0; k < img -> w; k++)
                    {
                        pixel = SDL_MapRGB(img_copy -> format, 0, 255, 0);
                        putpixel(img_copy, k, beginingTextIndex, pixel);
                    }   
                }
            }
            
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
            if (!first) {
                if (ii - endText >= lastLineHeight * 0.2 && ii - endText > 3) {
                //Draw line
                    for (int k = 0; k < img -> w; k++)
                    {
                        pixel = SDL_MapRGB(img_copy -> format, 0, 255, 0);
                        putpixel(img_copy, k, i, pixel);
                    }
                }
                firstCut = 1;
            }
            else {
                if (ii - endText >= lastLineHeight && ii - endText > 3) {
                //Draw line
                    for (int k = 0; k < img -> w; k++)
                    {
                        pixel = SDL_MapRGB(img_copy -> format, 0, 255, 0);
                        putpixel(img_copy, k, i, pixel);
                    }
                }
                firstCut = 1;
            }
            
        }
        
    }
    //SDL_FreeSurface(img);
    return img_copy;
}

// Use convertColumn after to save each word
SDL_Surface *cutColumn(SDL_Surface *img) {
    int fullWhite = 1;
    int firstCut = 1;
    //Gets the first pixel (height wise) with full white width
    int endText = -1;
    //Gets the first pixel without full white width after several full white
    int beginingText = -1; 
    //Stores the number of pixels from the last text line
    int lastLineHeight = 0.03 * img -> w; 
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    SDL_Surface *img_copy = copy_image(img);

    for (int i = 0; i < img -> w; i++) 
    {
        //Returns whether img's height is full of white pixels or not
        fullWhite = fullWhiteHeight(img, i);

        if (!fullWhite && firstCut)
        {   
            beginingText = i;

            // Begins paragraphs
            if ((endText == -1 || 
				lastLineHeight <= abs(endText - beginingText)) && 
				i != 0)
			{
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

            // Ends paragraphs
            int ii = i;
            do
            {
                fullWhite = fullWhiteHeight(img, ii);
                ii++;
            } while (fullWhite);
            if (ii - endText >= 0.03 * img -> w) {
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

SDL_Surface *cutWord(SDL_Surface *img) {
    int fullWhite = 1;
    int firstCut = 1;
    //Gets the first pixel (height wise) with full white width
    int endText = -1; 
    //Gets the first pixel without full white width after several full white 
    int beginingText = -1;
    //Average width of a space character, const
    float spaceAverage = img -> h * 0.3; 
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    SDL_Surface *img_copy = copy_image(img);

    for (int i = 0; i < img -> w; i++) 
    {
        //Returns whether img's height is full of white pixels or not
        fullWhite = fullWhiteHeight(img, i);

        if (!fullWhite && firstCut)
        {   
            beginingText = i;
            int begininTextIndex = beginingText > 0 ? beginingText -1 : 0;

            // Begins word
            if (endText == -1 || spaceAverage <= abs(endText - beginingText)){
                for (int k = 0; k < img -> h; k++)
                {
                    pixel = SDL_MapRGB(img_copy -> format, 0, 255, 0);
                    putpixel(img_copy, begininTextIndex, k, pixel);
                }   
            }
            firstCut = 0;
        }
        
        if(fullWhite && !firstCut) {
            endText = i;

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
            if (ii - endText >= spaceAverage || ii >= img -> w) { // Word ending
                //Draw line
                for (int k = 0; k < img -> h; k++)
                {
                    pixel = SDL_MapRGB(img_copy -> format, 0, 255, 0);
                    putpixel(img_copy, i, k, pixel);
                }
                firstCut = 1;
            }
        }
    }
    //SDL_FreeSurface(img);
    return img_copy;
}

int paragraphsCount = 0;

/*
 * Removes green separating lines between paragraphs and lines 
 * and stores each of them in a folder
 * Param:
 *      - img : image to compute
 *      - directory : the directory name to store the different parts cut
 * 		- isLineSegmentation : true if we are on a line
 */

void removeLines(SDL_Surface *img, char *directory, 
	int isLineSegmentation, int isItalic, char *result) 
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int start = -42;
    int stop = -1;
    int positions[40];
    int pos = 0;

    for (int i = 0; i < img -> h; i++)
    {
        pixel = getpixel(img, 0, i);
        SDL_GetRGB(pixel, img -> format, &r, &g, &b);
        unsigned char isGreenLine = r < 250 && g == 255 && b < 250;

        if (start == -42 && isGreenLine) {
            start = i;
        }
        else if (i == 0 && !fullWhiteWidth(img, i) && start == -42) {
            // Corner case for no beginning green line
            start = -1;
        }

        else if (start != -42 && isGreenLine) {
            stop = i;
            positions[pos] = start;
            positions[pos + 1] = stop;
            pos += 2;
            start = -42;
            stop = -1;
        }
        else if (start != -42 && i == img->h-1 && !isGreenLine) {
            // Corner case for no ending green line
            stop = i+1;
            positions[pos] = start;
            positions[pos + 1] = stop;
            pos += 2;
            start = -42;
            stop = -1;
        }
    }
    
    int currentLine = 0;
    char path[40];
    char newline = '\n';
    mkdir(directory, 0777);

    for (int i = 0; i < pos; i+=2) {
        int height = positions[i + 1] - positions[i] - 1;
        SDL_Surface *newImage;
        newImage = SDL_CreateRGBSurface(0, img -> w, height, 32,
        0, 0, 0, 0);
        for (int x = 0; x < img -> w; x++)
        {
            for (int y = 0; y < height; y++)
            {
                putpixel(newImage, x, y ,
                getpixel(img,  x, positions[i] + y + 1));
            }
            
        }

        snprintf(path, 40, "%s/%d.bmp", directory, currentLine);
        SDL_SaveBMP(newImage, path);
        if (isLineSegmentation) {
			characterSegmentationWithoutLoad(newImage, 
				"results/tempChar", 0, isItalic, result);
			strncat(result, &newline, 1);
		}
		else {
			lineSegmentationWithoutLoad(newImage, 
				"result/tempLine", 0, isItalic, result);
			strncat(result, &newline, 1);
            strncat(result, &newline, 1);
		}
        currentLine++;
    }
    //free(line);
    return;
}

/*
 * Removes blue/red separating lines between characters 
 * and stores each of them in a folder (old method)
 * Uses begining and ending indexes from allPos array 
 * to separate characters and store them in a folder
 * Param:
 *      - img : image to compute
 *      - directory : the directory name to store the different parts cut
 *      - *allPos : the array containing every begining and ending indexes
 */

char *removeLinesForCharacters(SDL_Surface *img, char *directory, int *allPos,
    char *result)
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int currentIndex = 0;
    // Define size
    float averageCharLength = (img -> h)*0.5;
    // Stores the estimated number of characters to create a good size array
    unsigned int size = (int) ((img->w/averageCharLength) * 2); 
    char path[300];
    
    for (size_t i = 0; i < size && allPos[i] != -42; i+=2) {
        int width = 0;
        // Corner case: last pixel is not full white, we need to keep it
        if (allPos[i+1] == img->w-1) { 
            width = allPos[i + 1] - allPos[i];
        }
        else {
			// -1 corner case is ok
            width = allPos[i + 1] - allPos[i] - 1;  
        }

        SDL_Surface *newImage = SDL_CreateRGBSurface(0, width, img -> h, 32,
        0, 0, 0, 0);
        
        for (int y = 0; y < img -> h; y++)
        {
            for (int x = 0; x < width; x++)
            {
                putpixel(newImage, x, y , getpixel(img, allPos[i] + x + 1, y));
            }
        }

        // Remove top and bottom white spaces
        unsigned int cut_top = 0;
        unsigned int cut_bottom = 0;

        // Cut top
        for (unsigned int h = 0; h < newImage -> h; h++)
        {
            unsigned char fullwhite = 1;
            for (unsigned int w = 0; w < newImage -> w && fullwhite; w++)
            {
                pixel = getpixel(newImage, w, h);
                SDL_GetRGB(pixel, newImage -> format, &r, &g, &b);
                fullwhite = r > 100 && g > 100 && b > 100;
            }

            if (!fullwhite) {
                cut_top = h;
                break;
            }
        }

        // Cut bottom
        for (int h = (newImage -> h) - 1; h >= 0; h--)
        {
            unsigned char fullwhite = 1;
            for (unsigned int w = 0; w < newImage -> w && fullwhite; w++)
            {
                pixel = getpixel(newImage, w, h);
                SDL_GetRGB(pixel, newImage -> format, &r, &g, &b);
                fullwhite = r > 249 && g > 249 && b > 249;
            }

            if (!fullwhite) {
                cut_bottom = h;
                break;
            }
        }

        // New image without white spaces
        SDL_Surface *newImageSmall;
        newImageSmall = SDL_CreateRGBSurface(0, newImage -> w,
        cut_bottom - cut_top + 1, 32, 0, 0, 0, 0);
        for (int y = cut_top; y < cut_bottom + 1; y++)
        {
            for (int x = 0; x < newImage -> w; x++)
            {
                putpixel(newImageSmall, x, y - cut_top,
                getpixel(newImage, x, y));
            }
        }
        
        
        // Resize image if width or height is higher than 32
        if (newImageSmall->w > 32 && newImageSmall->w >= newImageSmall->h) {
			newImageSmall = resize(newImageSmall, 32, 
				(int)(((double)32 * 
				(double)newImageSmall->h)/(double)newImageSmall->w));
		}
		else if (newImageSmall->h > 32) {
			newImageSmall = resize(newImageSmall, 
				(int)(((double)32 * 
				(double)newImageSmall->w)/(double)newImageSmall->h), 32);
		}



        // New full white 32x32 image
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
        
        // Copy image with character on the new image
        for (int y = 0; y < newImageSmall -> h; y++)
        {
            for (int x = 0; x < newImageSmall -> w; x++)
            {
                putpixel(lastImage, x, y, getpixel(newImageSmall, x, y));
            }
        }
        
        // Save final image into directory in param
        mkdir(directory, 0777);
        snprintf(path, 300, "%s/%d.bmp", directory, paragraphsCount);
        paragraphsCount++;
        SDL_SaveBMP(lastImage, path);
        // SDL_FreeSurface(newImageSmall);
        // SDL_FreeSurface(lastImage);
        // SDL_FreeSurface(newImage);
    }
    int *wordPos;
    wordPos = wordPositions(img);
    lineRecognition(directory, paragraphsCount, allPos, wordPos, result);
    paragraphsCount = 0;
    free(allPos);
    free(wordPos);
    return result;
}


/*
 * Removes blue/red separating lines between characters 
 * and stores each of them in a folder (old method)
 * Uses begining and ending indexes from allPos array 
 * to separate characters and store them in a folder
 * Param:
 *      - img : image to compute
 *      - directory : the directory name to store the different parts cut
 *      - *allPos : the array containing every begining and ending indexes
 */

void *removeLinesForItalicChars(SDL_Surface *img, char *directory, int *allPos,
    char *result)
{
    unsigned int mod = 5;
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int currentIndex = 0;

    // Define size
    float averageCharLength = (img -> h)*0.5;
    // Stores the estimated number of characters to create a good size array
    unsigned int size = (int) ((img->w/averageCharLength) * 2); 

    for (size_t i = 0; i < size && allPos[i] != -42; i+=2) {
        int width = 0;
        // Corner case: last pixel is not full white, we need to keep it
        if (allPos[i+1] == img->w-1) { 
            width = allPos[i + 1] - allPos[i];
        }
        else {
            width = allPos[i + 1] - allPos[i] - 1;  // -1 corner case is ok
        }
        width *= 2; // Char is italic so we create a bigger image to store it

        SDL_Surface *newImage = SDL_CreateRGBSurface(0, width, img -> h, 32,
        0, 0, 0, 0);
        
        // Fills the new image with white pixels
        for (int ii = 0; ii < newImage->h; ii++){   
            for (int kk = 0; kk < newImage->w; kk++) {
                pixel = SDL_MapRGB(newImage -> format, 255, 255, 255);
                putpixel(newImage, kk, ii, pixel);
            }
        }

        int offset = 0; // descreasing variable to be italic (to be negative)
        for (int y = 0; y < img -> h; y++)
        {
            for (int x = 0; x < width/2; x++)
            {
                if (allPos[i] + x + offset < img->w && width/2 + offset + x > -1 
					&& allPos[i] + x + offset > -1)
                {
                    putpixel(newImage, width/2 + offset + x, y , 
						getpixel(img, allPos[i] + x + offset, y));
                }
            }
            if (y % mod == mod-1){
                offset--;
            }
        }
        
        
        // Remove white spaces at top and bottom
        unsigned int cut_top = 0;
        unsigned int cut_bottom = 0;

        // Cut top
        for (unsigned int h = 0; h < newImage -> h; h++)
        {
            unsigned char fullwhite = 1;
            for (unsigned int w = 0; w < newImage -> w && fullwhite; w++)
            {
                pixel = getpixel(newImage, w, h);
                SDL_GetRGB(pixel, newImage -> format, &r, &g, &b);
                fullwhite = r > 100 && g > 100 && b > 100;
            }

            if (!fullwhite) {
                cut_top = h;
                break;
            }
        }

        // Cut bottom
        for (int h = (newImage -> h) - 1; h >= 0; h--)
        {
            unsigned char fullwhite = 1;
            for (unsigned int w = 0; w < newImage -> w && fullwhite; w++)
            {
                pixel = getpixel(newImage, w, h);
                SDL_GetRGB(pixel, newImage -> format, &r, &g, &b);
                fullwhite = r > 249 && g > 249 && b > 249;
            }


            if (!fullwhite) {
                cut_bottom = h;
                break;
            }
        }

        // inclusive value for left starting index
        int leftStart = 0;
        for (int w = 0; w < newImage->w; w++) {
            unsigned char fullwhite = 1;
            for (int h = 0; h < newImage->h && fullwhite; h++) {
                pixel = getpixel(newImage, w, h);
                SDL_GetRGB(pixel, newImage -> format, &r, &g, &b);
                fullwhite = r > 100 && g > 100 && b > 100;
            }

            if (!fullwhite) {
                leftStart = w;
                break;
            }
        }

        // Nouvelle image du caractère sans le haut et bas
        SDL_Surface *newImageSmall;
        newImageSmall = SDL_CreateRGBSurface(0, newImage -> w - leftStart,
        cut_bottom - cut_top + 1, 32, 0, 0, 0, 0);
        for (int y = cut_top; y < cut_bottom + 1; y++)
        {
            for (int x = leftStart; x < newImage -> w; x++)
            {
                putpixel(newImageSmall, x - leftStart, y - cut_top,
                getpixel(newImage, x, y));
            }
        }


        if (newImageSmall->w > 32 && newImageSmall->w >= newImageSmall->h) {
			newImageSmall = resize(newImageSmall, 32, 
			(int)(((double)32 * 
				(double)newImageSmall->h)/(double)newImageSmall->w));
		}
		else if (newImageSmall->h > 32) {
			newImageSmall = resize(newImageSmall, 
			(int)(((double)32 * 
				(double)newImageSmall->w)/(double)newImageSmall->h), 32);
		}


        // New full white 32x32 image
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

        // Save final image into directory
        mkdir(directory, 0777);
        char path[300];
        snprintf(path, 300, "%s/%d.bmp", directory, paragraphsCount);
        paragraphsCount++;
        SDL_SaveBMP(lastImage, path);
    }
    int *wordPos;
    wordPos = wordPositionsItalic(img);
    lineRecognition(directory, paragraphsCount, allPos, wordPos, result);
    paragraphsCount = 0;
    free(allPos);
    free(wordPos);
    return result;
}

/*
 * Removes green separating lines between words and stores each 
 * of them in a folder
 * Param:
 *      - img : image to compute
 *      - directory : the directory name to store the different parts cut
 */

void removeLinesForWords(SDL_Surface *img, char *directory) {
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

        if (start == -1 && (r < 200 && g == 255 && b < 200)) {
            start = j;
        }

        else if (start != -1 && (r < 200 && g == 255 && b < 200)) {
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

        // Copy word in a new image
        for (int y = 0; y < img -> h; y++)
        {
            for (int x = 0; x < width; x++)
            {
                putpixel(newImage, x, y,
					getpixel(img, positions[i] + x + 1, y));
            }
        }
        
        // Save final image into directory
        mkdir(directory, 0777);
        char path[100];
        snprintf(path, 100, "%s/%d.bmp", directory, paragraphsCount);
        paragraphsCount++;
        SDL_SaveBMP(newImage, path);
        //SDL_FreeSurface(img);
        //SDL_FreeSurface(newImage);
    }
}


int *wordPositions(SDL_Surface *img){
	int fullWhite = 1;
    int firstCut = 1;
    //Gets the first pixel (height wise) with full white width
    int endText = -1;
    //Gets the first pixel without full white width after several full white 
    int beginingText = -1;
    //Average width of a space character, const
    float spaceAverage = img -> h * 0.3; 
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int *positions;
    positions = malloc(150 * sizeof(int));
    
    int numberOfCharacters = 0;
    int current = 0;

    for (int i = 0; i < img -> w; i++) 
    {
        //Returns whether img's height is full of white pixels or not
        fullWhite = fullWhiteHeight(img, i);

        if (!fullWhite && firstCut)
        {   
            beginingText = i;
            int begininTextIndex = beginingText > 0 ? beginingText -1 : 0;
            firstCut = 0;
        }
        
        if(fullWhite && !firstCut) {
            endText = i;

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
            if (ii - endText >= spaceAverage || ii >= img -> w) { // Word ending
                firstCut = 1;
                *(positions + current) = endText;
                current++;
            }
        }
    }
    *(positions + current) = -42;
    //SDL_FreeSurface(img);
    return positions;
}

int *wordPositionsItalic(SDL_Surface *img){
	unsigned int mod = 5;
	int fullWhite = 1;
    int firstCut = 1;
    // Gets the first pixel (height wise) with full white width
    int endText = -1;
    // Gets the first pixel without full white width after several full white
    int beginingText = -1;
    //Average width of a space character, const
    float spaceAverage = img -> h * 0.3;
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int *positions;
    positions = malloc(150 * sizeof(int));
    
    int numberOfCharacters = 0;
    int current = 0;

    for (int i = 0; i < img -> w; i++) 
    {
        //Returns whether img's height is full of white pixels or not
        fullWhite = fullWhiteItalic(img, i, mod);

        if (!fullWhite && firstCut)
        {   
            beginingText = i;
            int begininTextIndex = beginingText > 0 ? beginingText -1 : 0;
            // Drawing lines
            int jj = i;
            for (int j = 0; j < img -> h && jj > -1; j++)
            {
                pixel = SDL_MapRGB(img -> format, 0, 0, 255);
                putpixel(img, jj, j, pixel);

                //Updating indexes
                if (j % mod == mod-1){
                    jj--;
                }
            }
            firstCut = 0;
        }
        
        if(fullWhite && !firstCut) {
            endText = i;

            // Ends paragraphs
            int ii = i;
            while (fullWhiteItalic(img, ii, mod))
            {
                ii++;
            }
            if (ii - endText >= spaceAverage || ii >= img -> w) { // Word ending
				int jj = i;
				for (int j = 0; j < img -> h && jj > -1; j++)
				{
					pixel = SDL_MapRGB(img -> format, 0, 0, 255);
					putpixel(img, jj, j, pixel);

					//Updating indexes
					if (j % mod == mod-1){
						jj--;
					}
				}
                firstCut = 1;
                *(positions + current) = endText;
                current++;
            }
        }
    }
    *(positions + current) = -42;
    //SDL_FreeSurface(img);
    return positions;
}

/*
 * Removes green separating lines between columns 
 * and calls removeLines for each column
 * Param:
 *      - img : image to compute
 *      - directory : directory's name for where to store the output
 */

void convertColumns(SDL_Surface *img, char *directory)
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int start = -42;
    int stop = -1;
    int positions[40];
    int pos = 0;

    for (int i = 0; i < img -> w; i++)
    {
        pixel = getpixel(img, i, 0);
        SDL_GetRGB(pixel, img -> format, &r, &g, &b);
        unsigned char isGreenLine = r < 250 && g == 255 && b < 250;

        // Beginning index
        if (start == -42 && isGreenLine) {
            start = i;
        }
        else if (i == 0 && !fullWhiteHeight(img, i) && start == -42) {
            // Corner case for no beginning green line
            start = -1;
        }

        // Ending index
        else if (start != -42 && isGreenLine) {
            stop = i;
            positions[pos] = start;
            positions[pos + 1] = stop;
            pos += 2;
            start = -42;
            stop = -1;
        }
        else if (start != -42 && i == img->w-1 && !isGreenLine) {
            // Corner case for no ending green line
            stop = i+1;
            positions[pos] = start;
            positions[pos + 1] = stop;
            pos += 2;
            start = -42;
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
                putpixel(newImage, x, y ,
                getpixel(img, positions[i] + x + 1, y));
            }
            
        }

        mkdir(directory, 0777);
        char path[100];
        snprintf(path, 100, "%s/%d.bmp", directory, i/2);
        SDL_SaveBMP(newImage, path);
    }
    
}
