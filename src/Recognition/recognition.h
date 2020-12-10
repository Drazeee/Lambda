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
	int *allPos, int *wordsPositions);

static MMContext CHARS_CTX = {"ABDEFGHJLMNQRTabcdefghijklmnopqrstuvwxyz0123456789.!?-%()&$\":;/+*=@#", 68};
static MMContext ACC_CTX = {"\x00\x01\x02\x03\x04", 5};

#endif
