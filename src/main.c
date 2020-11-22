#include "main.h"

int fullSegmentation(char *imagePath) {
	SDL_Surface *img;
	img = SDL_LoadBMP(imagePath);

	if (!img) {
		return 0;
	}

	// Filters
	img = grayscale(img, 0, "");
	img = blackAndWhite(img, 0, "");
	img = cutColumn(img);


	// Multi columns
	convertColumns(img, "columns");


	// Open columns directory
	DIR *d;
	struct dirent *dir;
	d = opendir("columns");

	// Variables declaration
	int indexLines = 0;
	int indexSublines = 0;
	int indexWords = 0;
	int indexCharacters = 0;
	// Conditions on read files
	if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
			// End
			if (dir->d_name[0] != '.') {

				// Paragraphs segmentation | Directory: linesI/*.bmp
				char path[30];
        		snprintf(path, 30, "%.8s/%.11s", "columns", dir->d_name);
				img = SDL_LoadBMP(path);
				img = cutLine(img, 1);
        		snprintf(path, 30, "%.6s%i", "lines", indexLines);
				removeLines(img, path);
				DIR *d1 = opendir(path);
				struct dirent *dir1;
				if (d1) {
					while ((dir1 = readdir(d1)) != NULL) {
						if (dir1->d_name[0] != '.') {

							// Lines segmentation | Directory: linesI/sublinesJ/*.bmp
							char path1[45];
							snprintf(path1, 45, "%.20s/%.14s", path, dir1->d_name);
							img = SDL_LoadBMP(path1);
							img = cutLine(img, 0);
							snprintf(path1, 45, "%.20s/%.9s%i", path, "sublines", indexSublines);
							removeLines(img, path1);
							DIR *d2 = opendir(path1);
							struct dirent *dir2;
							if (d2) {
								while ((dir2 = readdir(d2)) != NULL) {
									if (dir2->d_name[0] != '.') {

										// Characters pre-segmentation | Directory: linesI/sublinesJ/words/line.bmp
										char path2[60];
										snprintf(path2, 70, "%.35s/%.24s", path1, dir2->d_name);
										img = SDL_LoadBMP(path2);
										snprintf(path2, 70, "%.35s/%.6s%i", path1, "words", indexWords);
										int *pos = cutCharacters(img, path2);	// Changed return assignation

										// Words segmentation | Directory: linesI/sublinesJ/words/*.bmp
										char path3[85];
										snprintf(path3, 85, "%.60s/line.bmp", path2);
										img = SDL_LoadBMP(path3);
										img = cutWord(img);
										removeLinesForWords(img, path2);
										DIR *d3 = opendir(path2);
										struct dirent *dir3;
										if (d3) {
											while ((dir3 = readdir(d3)) != NULL) {
												if (dir3->d_name[0] != '.' && strcmp(dir3->d_name, "line.bmp") != 0) {

													// Characters segmentation | Directory: linesI/sublinesJ/words/characters/*.bmp
													char path4[110];
													snprintf(path4, 110, "%.60s/%.39s", path2, dir3->d_name);
													img = SDL_LoadBMP(path4);
													snprintf(path4, 110, "%.60s/%.11s%i", path2, "characters", indexCharacters);
													removeLinesForCharacters(img, path4, pos);
													indexCharacters++;
												}
											}
										}
										indexWords++;
									}
								}	
							}
							indexSublines++;
						}
					}
				}
				indexLines++;
			}
        }
        closedir(d);
    }
	return 1;
}

int columnSegmentation(char *path, char *destination, int print)
{
	SDL_Surface *imgDefault;
	imgDefault = SDL_LoadBMP(path);
	if (!imgDefault) {
		if (print) 
		{
			printf("\033[0;31m"); 
			printf("Error: unable to find bmp file at %s\n", path);
			printf("\033[0m");
		}
		return 1;
	}
	imgDefault = cutColumn(imgDefault);
	convertColumns(imgDefault, destination);
	if (print)
	{
		printf("\33[0;32mLambda: segmentation ended successfully.\n");
		printf("The result is here: \"%s\"\033[0m\n\n", destination);
	}
	return 0;
}

int paragraphSegmentation(char *path, char *destination, int print)
{
	SDL_Surface *imgDefault;
	imgDefault = SDL_LoadBMP(path);
	if (!imgDefault) {
		if (print) 
		{
			printf("\033[0;31m"); 
			printf("Error: unable to find bmp file at %s\n", path);
			printf("\033[0m");
		}
		return 1;
	}
	imgDefault = cutLine(imgDefault, 1);
	removeLines(imgDefault, destination);
	if (print)
	{
		printf("\33[0;32mLambda: segmentation ended successfully.\n");
		printf("The result is here: \"%s\"\033[0m\n\n", destination);
	}
	return 0;
}

int lineSegmentation(char *path, char *destination, int print)
{
	SDL_Surface *imgDefault;
	imgDefault = SDL_LoadBMP(path);
	if (!imgDefault) {
		if (print) 
		{
			printf("\033[0;31m"); 
			printf("Error: unable to find bmp file at %s\n", path);
			printf("\033[0m");
		}
		return 1;
	}
	imgDefault = cutLine(imgDefault, 0);
	removeLines(imgDefault, destination);
	if (print)
	{
		printf("\33[0;32mLambda: segmentation ended successfully.\n");
		printf("The result is here: \"%s\"\033[0m\n\n", destination);
	}
	return 0;
}

int wordSegmentation(char *path, char *destination, int print)
{
	SDL_Surface *imgDefault;
	imgDefault = SDL_LoadBMP(path);
	if (!imgDefault) {
		if (print) 
		{
			printf("\033[0;31m"); 
			printf("Error: unable to find bmp file at %s\n", path);
			printf("\033[0m");
		}
		return 1;
	}
	imgDefault = cutWord(imgDefault);
	removeLinesForWords(imgDefault, destination);
	if (print)
	{
		printf("\33[0;32mLambda: segmentation ended successfully.\n");
		printf("The result is here: \"%s\"\033[0m\n\n", destination);
	}
	return 0;
}

char *characterSegmentation(char *path, char *destination, int print)
{
	SDL_Surface *imgDefault;
	imgDefault = SDL_LoadBMP(path);
	if (!imgDefault) {
		if (print) 
		{
			printf("\033[0;31m"); 
			printf("Error: unable to find bmp file at %s\n", path);
			printf("\033[0m");
		}
		return NULL;
	}
	int *allPos = cutCharacters(imgDefault, destination);
	char *result = removeLinesForCharacters(imgDefault, destination, allPos);
	if (print)
	{
		printf("\33[0;32mLambda: segmentation ended successfully.\n");
		printf("The result is here: \"%s\"\033[0m\n\n", destination);
	}
	return result;
}

int fullSegementation1(char *path)
{
	SDL_Surface *imgDefault;
	imgDefault = SDL_LoadBMP(path);
	if (!imgDefault)
	{
		printf("\033[0;31m"); 
		printf("Error: unable to find bmp file at %s\n", path);
		printf("\033[0m");
		return 1;
	}
	mkdir("results/segmentation", 0777);

	// Multi columns
	grayscale(imgDefault, 1, path);
	columnSegmentation(path, "results/segmentation/columns", 1);

	int nbColumns = 0;
	DIR *d;
	struct dirent *dir;
	d = opendir("results/segmentation/columns");
	if (d)
    {
		mkdir("results/segmentation/paragraphs", 0777);
        while ((dir = readdir(d)) != NULL)
        {
			if (dir->d_name[0] != '.')
			{
				char pathForParagraph[40];
				snprintf(pathForParagraph, 40, "results/segmentation/paragraphs/para%i", nbColumns);
				char currentColumn[36];
				snprintf(currentColumn, 36, "results/segmentation/columns/%s", dir->d_name);
				nbColumns++;
				paragraphSegmentation(currentColumn, pathForParagraph, 1);
			}
		}
	}
	return 1;
}

void array_print(int *begin)
{
    int *i = begin;
    for (int line = 0; *i != -42; ++i)
    {
        if (line > 72)
        {
            printf("|`|\n");
            line = 0;
        }

        line += printf("| %4d ", *i);
    }

    printf("|\n");
}

int main(int argc, char **argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	if (argc < 2) {
		interface();
		//printf("Lambda: Error during parsing command\n");
		return 1;
	} 


	// ITALIC TEST
	if (strcmp(argv[1], "italic") == 0){
		SDL_Surface *imgDefault;
		char *destination = "results/resultItalic";
		imgDefault = SDL_LoadBMP(argv[2]);
		if (!imgDefault) {
			if (1) 
			{
				printf("\033[0;31m"); 
				printf("Error: unable to find bmp file at %s\n", argv[2]);
				printf("\033[0m");
			}
			return 1;
		}
		int *allPos = cutCharactersItalic(imgDefault, destination);
		array_print(allPos);
		removeLinesForItalicChars(imgDefault, destination, allPos);
		if (1)
		{
			printf("\33[0;32mLambda: segmentation ended successfully.\n");
			printf("The result is here: \"%s\"\033[0m\n\n", destination);
		}
		//printf("%s\n", result);
		return 0;
	}


	if (strcmp(argv[1], "column") == 0) {
		return columnSegmentation(argv[2], "results/resultColumn", 1);
	}
	else if (strcmp(argv[1], "paragraph") == 0) {
		return paragraphSegmentation(argv[2], "results/resultParagraph", 1);
	}
	else if (strcmp(argv[1], "line") == 0) {
		return lineSegmentation(argv[2], "results/resultLine", 1);
	}
	else if (strcmp(argv[1], "word") == 0) {
		return wordSegmentation(argv[2], "results/resultWord", 1);
	}
	else if (strcmp(argv[1], "character") == 0) {
		return characterSegmentation(argv[2], "results/resultChar", 1) != NULL;
	}
	else if (strcmp(argv[1], "grayscale") == 0) {
		if (argc == 4) {
			SDL_Surface *imgDefault;
			imgDefault = SDL_LoadBMP(argv[2]);
			if (!imgDefault) {
				printf("Error: unable to find bmp file at %s\n", argv[2]);
				return 1;
			}
			imgDefault = grayscale(imgDefault, 1, argv[3]);
			printf("Lambda: Grayscale ended successfully\n");
			return 0;
		}
		else {
			printf("Lambda: Grayscale take exactly 2 paramaters but was called with %i parameter(s)\n", argc - 2);
			return 1;
		}
	}
	else if (strcmp(argv[1], "contrast") == 0)
	{
		if (argc == 4 || argc == 5) {
			SDL_Surface *imgDefault;
			imgDefault = SDL_LoadBMP(argv[2]);
			if (!imgDefault) {
				printf("Error: unable to find bmp file at %s\n", argv[2]);
				return 1;
			}
			if (argc == 5 && strcmp(argv[4], "true") == 0)
			{
				imgDefault = noiseReduction(imgDefault);
				printf("Lambda: Noise reduction ended successfully\n");
			}
			
			imgDefault = contrastImage(imgDefault);
			printf("Lambda: Contrast ended successfully\n");
			SDL_SaveBMP(imgDefault, argv[3]);
			return 0;
		}
		else {
			printf("Lambda: Contrast take 2 or 3 paramaters but was called with %i parameter(s)\n", argc - 2);
			return 1;
		}
	}
	else if (strcmp(argv[1], "blackwhite") == 0) {
		if (argc == 4) {
			SDL_Surface *imgDefault;
			imgDefault = SDL_LoadBMP(argv[2]);
			if (!imgDefault) {
				printf("Error: unable to find bmp file at %s\n", argv[2]);
				return 1;
			}
			imgDefault = blackAndWhite(imgDefault, 1, argv[3]);
			printf("Lambda: Black and White ended successfully\n");
			return 0;
		}
		else {
			printf("Lambda: Black and White take exactly 2 paramaters but was called with %i parameter(s)\n", argc - 2);
			return 1;
		}
	}

	else if (strcmp(argv[1], "segmentation") == 0) {
		if (argc == 3) {
			if (!fullSegmentation(argv[2])) {
				printf("Lambda: Error during segmentation execution\n");
				return 1;
			}
			printf("Lambda: Segmentation ended successfully\n");
			return 0;
		}
		else {
			printf("Lambda: Segmentation take exactly 1 paramater but was called with %i parameter(s)\n", argc - 2);
			return 1;
		}
	}
	else {
		//printf("Lambda: Error during parsing command\n");
		interface();
		return 1;
	}
	SDL_Quit();
	return 0;
}
