//
//  Functions.h
//  Predicate
//
//  Created by Maxime on 17/09/2020.
//

#ifndef Functions_h
#define Functions_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "Macros.h"

Uint32 GetPixel(SDL_Surface *surf, int x, int y);
double Sigmoid(double Sum);
double dSigmoid(double x);
double Tanh(double Sum);
double dTanh(double x);
float randomFloat(void);
void shuffle(int *array, size_t n);
void CopyArray(double* in, double* out, size_t len);
char* concat(const char *s1, const char *s2);
short MatchCharNoCase(char c1, char c2);
char* GetCharacters(void);

#endif /* Functions_h */
