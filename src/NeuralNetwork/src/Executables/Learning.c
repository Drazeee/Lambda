//
//  main.c
//  DigitsLearning
//
//  Created by Maxime on 15/09/2020.
//



/* This program will create/load and train a neural network
 * to recognize symbols on an image.
 */



#include <err.h>
#include "Macros.h"
#include "Train.h"




void TrainMain(
			const int newNetwork,
			const char* networkPath,
			const char* datasetPath,
			const int noImages ) {
	
	// Init random seed
	srand((unsigned)time(NULL));
	
	
	int noChars = NO_CHARACTERS;
	int imgsPerChars = noImages;
	
	long numTrainingSets = noChars * imgsPerChars;
	
	
	// Load dataset
	MMImage* dataSet = LoadDataset(datasetPath, noChars, imgsPerChars);
	
	// Load/ Init network
	MMNetwork network;
	
	if (newNetwork) {
		
		// Set network parameters
		int numInputs = 1024;
		int numHiddenNodes = 760; // 100
		int numOutputs = NO_CHARACTERS;
		
		// Init empty network
		network = InitNetwork(numInputs, numHiddenNodes, numOutputs);
		InitWeightsForNetwork(network);
	} else {
		
		// Load network from files
		network = LoadNetwork(networkPath);
		printf("Network loaded\n");
	}
	
	
	double* hiddenLayer = (double*)calloc(
										  network.numHiddenNodes,
										  sizeof(double)
										);
	double* outputLayer = (double*)calloc(network.numOutputs, sizeof(double));
	
	
	int trainingSetOrder[numTrainingSets];
	
	for (int i = 0;i < numTrainingSets;i++) { // TODO: Could be improved
		trainingSetOrder[i] = i;
	}
	
	
	
	printf("\n");
	
	
	//MARK: Training
	
	int gen = 0;
	while (1) {
		
		MMTrainingStats stats = Train(network, trainingSetOrder, numTrainingSets, dataSet, hiddenLayer, outputLayer);
		
		SaveNetwork(network, networkPath);
		
		int percentRate = stats.rate * 100;
		
		printf("Generation (%d%%) [t=%d, s=%d, f=%d] \n",
			   percentRate,
			   stats.total,
			   stats.success,
			   stats.fails
			   );
		
		gen ++;
	}
	
	//DestroyNetwork(network); // TODO: Breaking case
}



int main(int argc, const char * argv[]) {
    
    
#ifdef XCODE // If run in Xcode: all parameters are predefined (see Macros.h)
	char* networkPath = NETWORK_PATH;
	char* datasetPath = DATASET_PATH;
#	ifdef XCODE_DTK
	int newNetwork = 0;
#	else
	int newNetwork = 0;
#	endif
	int noImages = 100;
#else
	if (argc < 4) { // 3 args minimum (+ executable path)
		errx(1, "Not enough arguments\n\nUsage:\n%s networkPath datasetPath noImages --new-network", argv[0]);
	}
	const char* networkPath = argv[1];
	const char* datasetPath = argv[2];
	int noImages =  strtoul(argv[3], NULL, 10);
	
	int newNetwork = 0;
	if (argc >= 5) {
		// If there is a 4th argument and it is "--new-network",
		// will init & create a new network.
		if (strcmp(argv[4], "--new-network") == 0) {
			newNetwork = 1;
		}
	}
#endif
    
	
	TrainMain(newNetwork, networkPath, datasetPath, noImages);
	

    
    return 0;
}
