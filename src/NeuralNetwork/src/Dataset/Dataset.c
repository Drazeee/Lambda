//
//  Dataset.c
//  Predicate
//
//  Created by Maxime on 19/09/2020.
//

#include "Dataset.h"

#ifdef XCODE
#	define LOADING_LOGS 1
#endif

/*
 * Load a single image from its path.
 *
 * Returns:
 *	MMImage
 */
MMImage LoadImage(const char* path) {
	
	SDL_Surface* image = SDL_LoadBMP(path);
	// If it crashs here, ensure the path is correct
	
	
	int width = image->w;
	int height = image->h;
	
	
	struct MMImage img;
	img.pixelsTable = (MMPixelsTable*)calloc(
										(width * height),
										sizeof(MMPixelsTable)
											);
	
	img.w = width;
	img.h = height;
	
	//printf("Image size is %d %d\n", width, height);
	
	SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);
	
	int idx = 0;
	
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			Uint32 p = GetPixel(image, i, j);
			
			Uint8 r;
			Uint8 g;
			Uint8 b;
			SDL_GetRGB(p, format, &r, &g, &b);
			
			int mid = (r + g + b) * 0.33;
			
			
			if (mid < 216) {
				img.pixelsTable[idx].pixelValue = 1.0f;
			} else {
				img.pixelsTable[idx].pixelValue = 0.0f;
			}

			idx ++;
		}
	}
	return img;
}


/*
 * Load the whole dataset, and init its content images as MMImages.
 *
 * Params:
 *	int : How much characters we will load (order: [Aa-Zz0-9])
 *	int : How many images per character
 */
MMImage* LoadDataset(
				const char* datasetPath,
				const int noDigits,
				const int imagesPerDigit
			) {
	
	long numTrainingSets = noDigits * imagesPerDigit;
	int size = 1024;

	
	MMImage* dataSet = (MMImage*)calloc((numTrainingSets), sizeof(MMImage));
	
	for (int i = 0; i < numTrainingSets; ++i) {
		dataSet[i].pixelsTable = (MMPixelsTable*)calloc(
													size,
													sizeof(MMPixelsTable)
													);
	}

	char order[] = ORDER;

	// Load images
	int imageInputIdx = 0;
	printf("Loading Images...\n");

	for (int digit = 0; digit < noDigits; digit++) {
		
		char c = order[digit];

		#if (LOADING_LOGS)
			printf("	- Loading images for \"%c\"\n",c);
		#endif
		
		for (int imageIdx = 0; imageIdx < imagesPerDigit; imageIdx ++) {
			
			char path[70] = {0};
			char *basepath = "%s/%i/%i.bmp";
			
			sprintf(path, basepath, datasetPath, digit, imageIdx);
			//snprintf(path, 70,  BASEPATH, c, imageIdx); //TODO: DEBUG snprintf

			
			dataSet[imageInputIdx] = LoadImage(path);
			dataSet[imageInputIdx].character = c;
						
			dataSet[imageInputIdx].expectedOutput = (double*)calloc(
																(NO_CHARACTERS),
																sizeof(double)
															);
			dataSet[imageInputIdx].expectedOutput[digit] = 1.0f;

			
			imageInputIdx ++;
		}
	}
	
	printf("\n%d images loaded\n", imageInputIdx);
	
	return dataSet;
}


MMImage MakeFakeData(int noInputs, double* inputs, int noOutputs, double* outputs) {
	MMImage data;
	data.h = 1;
	data.w = noInputs;
	
	data.pixelsTable = calloc(noInputs, sizeof(MMPixelsTable));
	for (int i = 0; i < noInputs; i++) {
		data.pixelsTable[i].pixelValue = inputs[i];
	}
	
	data.expectedOutput = calloc(noOutputs, sizeof(double));
	for (int o = 0; o < noOutputs; o++) {
		data.expectedOutput[o] = outputs[o];
	}
	
	return data;

}
