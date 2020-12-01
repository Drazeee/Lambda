//
//  Structs.h
//  TestImage
//
//  Created by Maxime on 18/09/2020.
//

#ifndef Structs_h
#define Structs_h

#include <stdint.h>


typedef struct MMPixelsTable
{
	double	pixelValue;
} MMPixelsTable;

typedef struct MMImage
{
	MMPixelsTable*	pixelsTable;
	char*			fileName;
	int32_t			w;
	int32_t			h;
	char			character;
	double*			expectedOutput;
} MMImage;

#endif /* Structs_h */
