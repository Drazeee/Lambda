#ifndef RECOGNITION_H_
#define RECOGNITION_H_

#include <stdio.h>
#include "LambdaNeuralNetwork.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>

char recognition(MMImage img, MMNetwork nChar, MMNetwork nAccents);
char *lineRecognition(char *directory, int size, 
	int *allPos, int *wordsPositions, char *result);

#endif
