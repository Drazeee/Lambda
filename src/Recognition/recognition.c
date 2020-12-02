#include "recognition.h"

char filterChar(char c) {
	if (c > -1) {
		return c;
	}
	switch(c){
		case -120:
		case -119:
		case -112:
			return 'e';
		case -113:
		case -114:
		case -111:
		case -84:
			return 'a';
		case -108:
		case -107:
			return 'i';
		case -103:
		case -102:
			return 'o';
		case -99:
		case -98:
		case -97:
			return 'u';
		case -53:
		case -27:
		case -128:
			return 'E';
		case -125:
		case -23:
		case -26:
		case -24:
			return 'A';
		case -20:
		case -21:
			return 'I';
		case -17:
		case -123:
			return 'O';
		case -12:
		case -122:
		case -13:
			return 'U';
		case -15:
		case -126:
			return 'C';
		default:
			return '_';
	}
}


char recognition(MMImage img, MMNetwork n) {
    double *output = Predict(n, &img);
    char character = OutputChar(output);
    return character;
}


char *lineRecognition(char *directory, int size, 
	int *allPos, int *wordsPositions)
{
	DIR *d;
	struct dirent *dir;
	d = opendir(directory);
	char *result = malloc(150 * (sizeof(char)));
	int charactersNumber = 0; // total number of chars in the DIR
	int len = strlen(directory);
	MMNetwork network = LoadNetwork("src/NeuralNetwork/src/IA/IAC");
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
		char ch = recognition(mmimg, network);
		if (allPos[i * 2] > wordsPositions[wordIndex] 
		&& wordsPositions[wordIndex] != -42) {
			result[i + wordIndex] = ' ';
			wordIndex++;
		}
		ch = filterChar(ch);
		result[i + wordIndex] = ch;
	}
	result[charactersNumber + wordIndex] = 0;
	return result;
}
