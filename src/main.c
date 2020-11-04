#include "main.h"

double Sigmoid(double Sum) {
	return (1.0/(1.0 + exp(-Sum)));
}

double dSigmoid(double x) {
	return (x * (1 - x));
}

float randomFloat() {
	float r = (float)rand() / (float)RAND_MAX;
	return r;
}

double init_weight() {
	return randomFloat();
}

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


int xorNetwork() {
	
	/* Init random seed */
	srand(time(NULL));
	
	// Parameters
	int numInputs = 2;
	int numHiddenNodes = 2;
	int numOutputs = 1;
	
	double lr = 0.1;
	
	// Declare hidden NN parameters
	double hiddenLayer[numHiddenNodes];
	double outputLayer[numOutputs];
	
	double hiddenLayerBias[numHiddenNodes];
	double outputLayerBias[numOutputs];
	
	double hiddenWeights[numInputs][numHiddenNodes];
	double outputWeights[numHiddenNodes][numOutputs];
	
	int numTrainingSets = 4;
	double training_inputs[numTrainingSets][numInputs];
	
	// 	Input groups
	training_inputs[0][0] = 0.0f;
	training_inputs[0][1] = 0.0f;
	
	training_inputs[1][0] = 1.0f;
	training_inputs[1][1] = 0.0f;
	
	training_inputs[2][0] = 0.0f;
	training_inputs[2][1] = 1.0f;
	
	training_inputs[3][0] = 1.0f;
	training_inputs[3][1] = 1.0f;
	
	double training_outputs[numTrainingSets][numOutputs];
	
	//	Output for groups
	training_outputs[0][0] = 0.0f;
	training_outputs[1][0] = 1.0f;
	training_outputs[2][0] = 1.0f;
	training_outputs[3][0] = 0.0f;
	
	
	// Init with random weights
	for (int i=0; i<numInputs; i++) {
		for (int j=0; j<numHiddenNodes; j++) {
			hiddenWeights[i][j] = init_weight();
		}
	}
	for (int i=0; i<numHiddenNodes; i++) {
		hiddenLayerBias[i] = init_weight();
		for (int j=0; j<numOutputs; j++) {
			outputWeights[i][j] = init_weight();
		}
	}
	for (int i=0; i<numOutputs; i++) {
		outputLayerBias[i] = init_weight();
	}
	

	
	int trainingSetOrder[] = {0,1,2,3};
	
	
	// NN
	
	for (int n=0; n < 1000000; n++) {
		shuffle(trainingSetOrder,numTrainingSets);
		
		for (int x=0; x<numTrainingSets; x++) {
			int i = trainingSetOrder[x];
			
			/* Forward pass */
			
			for (int j=0; j<numHiddenNodes; j++) {
				double activation=hiddenLayerBias[j];
				for (int k=0; k<numInputs; k++) {
					activation+=training_inputs[i][k]*hiddenWeights[k][j];
				}
				hiddenLayer[j] = Sigmoid(activation);
			}
			
			for (int j=0; j<numOutputs; j++) {
				double activation=outputLayerBias[j];
				for (int k=0; k<numHiddenNodes; k++) {
					activation+=hiddenLayer[k]*outputWeights[k][j];
				}
				outputLayer[j] = Sigmoid(activation);
			}
			
			if (n % 100 == 0) {
				printf("Input: %f %f	Output: %f	Expected Output: %f\n", training_inputs[i][0], training_inputs[i][1], outputLayer[0], training_outputs[i][0]);
			}
			
			/* Backprop */
			
			double deltaOutput[numOutputs];
			for (int j=0; j<numOutputs; j++) {
				double errorOutput = (training_outputs[i][j]-outputLayer[j]);
				deltaOutput[j] = errorOutput*dSigmoid(outputLayer[j]);
			}
			
			double deltaHidden[numHiddenNodes];
			for (int j=0; j<numHiddenNodes; j++) {
				double errorHidden = 0.0f;
				for(int k=0; k<numOutputs; k++) {
					errorHidden+=deltaOutput[k]*outputWeights[j][k];
				}
				deltaHidden[j] = errorHidden*dSigmoid(hiddenLayer[j]);
			}
			
			for (int j=0; j<numOutputs; j++) {
				outputLayerBias[j] += deltaOutput[j]*lr;
				for (int k=0; k<numHiddenNodes; k++) {
					outputWeights[k][j]+=hiddenLayer[k]*deltaOutput[j]*lr;
				}
			}
			
			for (int j=0; j<numHiddenNodes; j++) {
				hiddenLayerBias[j] += deltaHidden[j]*lr;
				for(int k=0; k<numInputs; k++) {
					hiddenWeights[k][j]+=training_inputs[i][k]*deltaHidden[j]*lr;
				}
			}
		}
	}
	
	// Results
	
	printf("Final Hidden Weights\n[ ");
	for (int j=0; j<numHiddenNodes; j++) {
		printf("[ ");
		for(int k=0; k<numInputs; k++) {
			printf("%f ", hiddenWeights[k][j]);
		}
		printf("] ");
	}
	printf("\n");
	
	
	printf("Final Hidden Biases\n[ ");
	for (int j=0; j<numHiddenNodes; j++) {
		printf("%f ", hiddenLayerBias[j]);
		
	}
	
	printf("]\n");
	printf("Final Output Weights");
	for (int j=0; j<numOutputs; j++) {
		printf("[ ");
		for (int k=0; k<numHiddenNodes; k++) {
			printf("%f ", outputWeights[k][j]);
		}
		printf("] ");
	}
	printf("\n");
	printf("Final Output Biases\n[ ");
	for (int j=0; j<numOutputs; j++) {
		printf("%f ", outputLayerBias[j]);
		
	}
	printf("]\n");
	
	return 0;
}


int fullSegmentation(char *imagePath) {
	SDL_Surface *img;
	img = SDL_LoadBMP(imagePath);

	if (!img) {
		return 0;
	}

	// Filters
	img = grayscale(img, 0, "");
	img = blackAndWhite(img);
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


// static void
// activate (GtkApplication* app)
// {
//   GtkWidget *window;

//   window = gtk_application_window_new (app);
//   gtk_window_set_title (GTK_WINDOW (window), "Window");
//   gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
//   gtk_widget_show_all (window);
// }

int main(int argc, char **argv) {
	SDL_Init(SDL_INIT_EVERYTHING);

	if (argc < 2) {
		printf("Lambda: Error during parsing command\n");
		return 1;
	}

	// Grayscale command

	if (strcmp(argv[1], "column") == 0) {
		SDL_Surface *imgDefault;
		imgDefault = SDL_LoadBMP(argv[2]);
		if (!imgDefault) {
			printf("Error: unable to find bmp file at %s\n", argv[2]);
			return 1;
		}
		imgDefault = cutColumn(imgDefault);
		convertColumns(imgDefault, "results/resultColumn");
	}
	else if (strcmp(argv[1], "paragraph") == 0) {
		SDL_Surface *imgDefault;
		imgDefault = SDL_LoadBMP(argv[2]);
		if (!imgDefault) {
			printf("Error: unable to find bmp file at %s\n", argv[2]);
			return 1;
		}
		imgDefault = cutLine(imgDefault, 1);
		removeLines(imgDefault, "results/resultParagraph");
	}
	else if (strcmp(argv[1], "line") == 0) {
		SDL_Surface *imgDefault;
		imgDefault = SDL_LoadBMP(argv[2]);
		if (!imgDefault) {
			printf("Error: unable to find bmp file at %s\n", argv[2]);
		return 1;
		}	
		imgDefault = cutLine(imgDefault, 0);
		removeLines(imgDefault, "results/resultLine");
	}
	else if (strcmp(argv[1], "word") == 0) {
		SDL_Surface *imgDefault;
		imgDefault = SDL_LoadBMP(argv[2]);
		if (!imgDefault) {
			printf("Error: unable to find bmp file at %s\n", argv[2]);
			return 1;
		}
		imgDefault = cutWord(imgDefault);
		removeLinesForWords(imgDefault, "results/resultWord");
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
				imgDefault = contrast(imgDefault);
				printf("Lambda: Noise reduction ended successfully\n");
			}
			
			imgDefault = contrast(imgDefault);
			printf("Lambda: Contrast ended successfully\n");
			SDL_SaveBMP(imgDefault, argv[3]);
			return 0;
		}
		else {
			printf("Lambda: Contrast take 2 or 3 paramaters but was called with %i parameter(s)\n", argc - 2);
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

	else if (strcmp(argv[1], "characters") == 0) {
		if (argc == 3) {
			SDL_Surface *img;
			img = SDL_LoadBMP(argv[2]);
			int *pos = cutCharacters(img, "results/resultChars/");
			if (!img) {
				printf("Lambda: Error during segmentation execution\n");
				return 1;
			}
			removeLinesForCharacters(img, "results/resultChars", pos);
			printf("Lambda: Segmentation ended successfully\n");
			return 0;
		}
		else {
			printf("Lambda: Characters take exactly 1 paramater but was called with %i parameter(s)\n", argc - 2);
			return 1;
		}
	}

	else {
		printf("Lambda: Error during parsing command\n");
		return 1;
	}

	

	SDL_Quit();
	// GtkApplication *app;
	// int status;

	// app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	// g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	// status = g_application_run (G_APPLICATION (app), argc, argv);
	// g_object_unref (app);

	return 0;
}
