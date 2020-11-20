//
//  Functions.c
//  Predicate
//
//  Created by Maxime on 17/09/2020.
//

#include "Functions.h"

/*
 * Get a pixel color UInt from a pixel coord in an image.
 * The returned UInt could then be parsed with the SDL_GetRGB function.
 *
 * This function has been found on:
 * https://discourse.libsdl.org/t/truble-to-get-the-color-of-a-surface-pixel/13545/3
 *
 * Params:
 *	SDL_Surface* : Reference to the image to get the pixel of
 *	int : X coord of the pixel
 *	int : Y coord of the pixel
 *
 * Returns:
 *	UInt32 : Pixel color
 */
Uint32 GetPixel(SDL_Surface *surf, int x, int y)
{
	//This function returns pixels color
	int bpp = surf->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surf->pixels + y * surf->pitch + x * bpp;
	
	switch (bpp)
	{
		case 1:
			return *p;
			
		case 2:
			return *(Uint16 *)p;
			
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
			
		case 4:
			return *(Uint32 *)p;
			
		default:
			return 0;
	}
}

/*
 * Just a Sigmoid function.
 * Used as activation function for the neural network.
 */
double Sigmoid(double Sum) {
    return (1.0/(1.0 + exp(-Sum)));
}


/*
 * Derivate of the sigmoid.
 * Input is already a Sigmoid.
 *
 * Params:
 *	double : A Sigmoid
 *
 * Returns:
 *	double : Derivative
 */
double dSigmoid(double a) {
    //double a = Sigmoid(x);
	return a * (1.0 - a);
}


/*
 * Returns:
 *	float : A random float between 0 and 1
 */
float randomFloat() {
	float r = (float)rand() / (float)RAND_MAX;
	return r;
}

/*
 * Shuffle an array of integers
 *
 * Params:
 *	int* : Pointer to the int array
 *	size_t : Length of the array
 */
void shuffle(int *array, size_t n)
{
	if (n > 1)
	{
		size_t i;
		for (i = 0; i < n - 1; i++)
		{
			size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
			int t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
	}
}

/*
 * Duplicate an array of double
 *
 * Params:
 *	double* : Source array pointer
 *	double* : Destination array pointer
 *	size_t : Length of the array
 */
void CopyArray(double* in, double* out, size_t len) {
    for (size_t i = 0; i < len; i++)
        out[i] = in[i];
}


/*
 * Concat two strings and returns the new one
 *
 * Params:
 *	char* : First string
 *	char* : End string
 *
 * Returns:
 *	char* : First_string + End_string
 */
char* concat(const char *s1, const char *s2) {
	char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
	// in real code you would check for errors in malloc here
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

/*
 * Check if two characters are equal but not matching the case.
 * Ex:
 *	MatchCharNoCase('#','#') -> 1
 *	MatchCharNoCase('E','E') -> 1
 *	MatchCharNoCase('A','a') -> 1
 *	MatchCharNoCase('z','Z') -> 1
 *	MatchCharNoCase('P','d') -> 0
 *
 * Params:
 *	char : First char to compare
 *	char : Other char to compare
 *
 * Returns:
 *	short : 1 if comparaison is verified, 0 otherwise
 */
short MatchCharNoCase(char c1, char c2) {
	// If characters are equal, return True
	if (c1 == c2) {
		return 1;
	}
	
	// If c1 is uppercase: check if equal to c2 - 32
	if (c1 >= 65 && c1 < 91) {
		return (c1 + 32 == c2);
	}
	
	// If c1 is lowercase: check if equal to c2 + 32
	if (c1 >= 97 && c1 < 123) {
		return (c1 - 32 == c2);
	}
	return 0;
}


char* GetCharacters() {
	return ORDER;
}
