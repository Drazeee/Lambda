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

    //SilentUnusedWarnings(); // Just silent those warnings...

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


double Softmax(double a, double sum) {
	return a / sum;
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

/*
 * Get an accentued character it it can from the character and the accent type.
 * It this character can't take this accent (french syntax only), returns
 * the character without accent.
 * This actually is the worst function I had to write.
 *
 * Params:
 *	char : The character without accent
 *	char : Number between 0 and 5: type of accent
 *
 * Returns:
 *	char* : String of char = the char with accent.
 */
char* Accent(char character, char accent) {
	
	if (character == 'c' && accent == 0) {
		return "ç";
	} else if (character == 'a') {
		switch (accent) {
			case 1:
				return "à";
			case 3:
				return "â";
			case 4:
				return "ä";
			default:
				return "a";
		}
	} else if (character == 'e') {
		switch (accent) {
			case 1:
				return "è";
			case 2:
				return "é";
			case 3:
				return "ê";
			case 4:
				return "ë";
			default:
				return "e";
		}
	} else if (character == 'i') {
		switch (accent) {
			case 3:
				return "î";
			case 4:
				return "ï";
			default:
				return "i";
		}
	} else if (character == 'o') {
		switch (accent) {
			case 3:
				return "ô";
			case 4:
				return "ö";
			default:
				return "o";
		}
	} else if (character == 'u') {
		switch (accent) {
			case 1:
				return "ù";
			case 3:
				return "û";
			case 4:
				return "ü";
			default:
				return "u";
		}
	} else if (character == 'C' && accent == 0) {
		return "Ç";
	} else if (character == 'A') {
		switch (accent) {
			case 1:
				return "À";
			case 3:
				return "Â";
			case 4:
				return "Ä";
			default:
				return "A";
		}
	} else if (character == 'E') {
		switch (accent) {
			case 1:
				return "È";
			case 2:
				return "É";
			case 3:
				return "Ê";
			case 4:
				return "Ë";
			default:
				return "E";
		}
	} else if (character == 'I') {
		switch (accent) {
			case 3:
				return "Î";
			case 4:
				return "Ï";
			default:
				return "I";
		}
	} else if (character == 'O') {
		switch (accent) {
			case 3:
				return "Ô";
			case 4:
				return "Ö";
			default:
				return "O";
		}
	} else if (character == 'U') {
		switch (accent) {
			case 1:
				return "Ù";
			case 3:
				return "Û";
			case 4:
				return "Ü";
			default:
				return "U";
		}
	}
	char* s = malloc(sizeof(char));
	s[0] = character;
	return s;
	
}


