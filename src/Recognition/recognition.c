#include "recognition.h"

char recognition(MMImage img, MMNetwork n) {
    double *output = Predict(n, &img);
    char character = OutputChar(output);
    printf("%d\n", character);
    return character;
}


char *lineRecognition(char *directory, int size, int *allPos, int *wordsPositions)
{
	DIR *d;
	struct dirent *dir;
	d = opendir(directory);
	char *result = malloc((size + 5) * (sizeof(char)));
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
		printf("%s\n", path);
		MMImage mmimg = LoadImage(path);
		char ch = recognition(mmimg, network);
		if (allPos[i * 2] > wordsPositions[wordIndex] 
		&& wordsPositions[wordIndex] != -42) {
			result[i + wordIndex] = ' ';
			wordIndex++;
		}
		//if (ch == 'Q') {
		//	ch = 'e';
		//}
		//if (ch == '8') {
		//	ch = 'a';
		//}
		//if (ch == 'D') {
		//	ch = 'p';
		//}
		result[i + wordIndex] = ch;
	}
	result[charactersNumber + wordIndex] = 0;
	printf("recognition: %s\n", result);
	return result;
}
