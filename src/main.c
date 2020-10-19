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


int main1() {
	
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
	SDL_Surface *img;

	//img = SDL_LoadBMP("lines/0.bmp");

	//img = cutLine(img);
	img = cutCharacters(img);
	//removeLinesForCharacters(img, "lines/characters");

	//img = cutColumn(img);
	//convertColumns(img);

	

	SDL_Quit();
	// GtkApplication *app;
	// int status;

	// app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	// g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	// status = g_application_run (G_APPLICATION (app), argc, argv);
	// g_object_unref (app);

	return 0;
}