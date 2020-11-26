#ifndef RECOGNITION_H_
#define RECOGNITION_H_

#include <stdio.h>
#include "../NeuralNetwork/src/LambdaNeuralNetwork.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>

char recognition(MMImage img, MMNetwork n);
char *lineRecognition(char *directory, int size, int *allPos, int *wordsPositions);

#endif
