#include "recognition.h"

void filterChar(char *c) {
	if (*c > -1) {
		return;
	}
	switch(*c){
		// case -120:
		// case -119:
		// case -112:
		// 	return 'e';
		// case -113:
		// case -114:
		// case -111:
		// case -84:
		// 	return 'a';
		// case -108:
		// case -107:
		// 	return 'i';
		// case -103:
		// case -102:
		// 	return 'o';
		// case -99:
		// case -98:
		// case -97:
		// 	return 'u';
		// case -53:
		// case -27:
		// case -128:
		// 	return 'E';
		// case -125:
		// case -23:
		// case -26:
		// case -24:
		// 	return 'A';
		// case -20:
		// case -21:
		// 	return 'I';
		// case -17:
		// case -123:
		// 	return 'O';
		// case -12:
		// case -122:
		// case -13:
		// 	return 'U';
		// case -15:
		// case -126:
		// 	return 'C';
		default:
			*c = ' ';
			return;
	}
}


char recognition(MMImage img, MMNetwork nChar, MMNetwork nAccents) {
    double *output = Predict(nChar, &img);
    char character = OutputChar(output, &CHARS_CTX);
	
	double *outputAcc = Predict(nAccents, &img);
	char characterAcc = OutputChar(output, &ACC_CTX);

	if (character == 'Q') {
		character = 'e'; // There are more 'e' than 'Q' so anyway, we hardcode it...
	}
	
	//char* charWithAccent = Accent(character, characterAcc
	
    return character;
}


char *lineRecognition(char *directory, int size, 
	int *allPos, int *wordsPositions, char *result)
{
	DIR *d;
	struct dirent *dir;
	d = opendir(directory);
	char space = ' ';
	int charactersNumber = 0; // total number of chars in the DIR
	int len = strlen(directory);
	MMNetwork networkChar = LoadNetwork("src/NeuralNetwork/IA/IA-Char/");
	MMNetwork networkAcc = LoadNetwork("src/NeuralNetwork/IA/IA-Acc/");
	if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
			if (dir->d_name[0] != '.' && dir->d_name[0] != 'l') {
				charactersNumber++;
			}
		}

	}
	
	int wordIndex = 0;
	for (int i = 0; i < charactersNumber; i++) {
		char path[len + 40];
		snprintf(path, len + 40, "%s/%i.bmp", directory, i);
		MMImage mmimg = LoadImage(path);
		char ch = recognition(mmimg, networkChar, networkAcc);
		if (allPos[i * 2] > wordsPositions[wordIndex] 
		&& wordsPositions[wordIndex] != -42) {
			strncat(result, &space, 1);
			wordIndex++;
		}
		filterChar(&ch);
		strncat(result, &ch, 1);

	}
	DestroyNetwork(&networkChar);
	DestroyNetwork(&networkAcc);
	char end = '\0';
	strncat(result, &end, 1);
	return result;
}
