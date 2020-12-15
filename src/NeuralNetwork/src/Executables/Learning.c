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
	
	
	int imgsPerChars = noImages;
	
	int numTrainingSets = CHARS_CTX.nb_classes * imgsPerChars;
	
	
	
	
	// Load dataset
	MMImage* dataSet = LoadDataset(datasetPath, CHARS_CTX.nb_classes, imgsPerChars, &CHARS_CTX);
	
	
	// Load/ Init network
	MMNetwork network;
	
	if (newNetwork) {
		
		// Set network parameters
		int numInputs = 1024;
		int numHiddenNodes = 204; // 100
		int numOutputs = CHARS_CTX.nb_classes;
		
		// Init empty network
		network = InitNetwork(numInputs, numHiddenNodes, numOutputs);
		InitWeightsForNetwork(network);
		SaveNetwork(network, networkPath);
		
		FILE* statsFile = fopen(concat(networkPath, "/training.tcsv"), "w+");
		fprintf(statsFile, "rate;success;fails\n");
		fclose(statsFile);

		
	} else {
		
		// Load network from files
		network = LoadNetwork(networkPath);
		printf("Network loaded\n");
	}
	
	MMTrainingEnvironment env = TrainingEnvironment(network, numTrainingSets, 0.5);
		
	
	printf("\n");
	
	
	//MARK: Training
	
	int gen = 0;
	while (1) {
		
		MMTrainingStats stats = Train(network, dataSet, env, &CHARS_CTX);
		
		SaveNetwork(network, networkPath);
		
		double percentRate = stats.rate * 100;
		
		printf("Generation %d (%.2f%%) [t=%d, s=%d, f=%d] \n",
			   gen,
			   percentRate,
			   stats.total,
			   stats.success,
			   stats.fails
			   );
		
		FILE* statsFile = fopen(concat(networkPath, "/training.tcsv"), "a+");
		fprintf(statsFile, "%f;%d;%d\n", stats.rate, stats.success, stats.fails);
		fclose(statsFile);
		
		
		gen ++;
	}
	
	//DestroyNetwork(network); // TODO: Breaking case
}



int main(int argc, const char * argv[]) {
    
    
#ifdef XCODE // If run in Xcode: all parameters are predefined (see Macros.h)
	char* networkPath = NETWORK_PATH;
	char* datasetPath = DATASET_PATH;
	int newNetwork = NEW_NETWORK;
	int noImages = 10000;
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
