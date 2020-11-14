//
//  main.c
//  Analyze
//
//  Created by Maxime on 16/09/2020.
//



/* This program will use a dataset as a testing-set and
 * get a prediction for every image of it.
 * Then, it will show a success rate.
 */



#include <err.h>
#include "Predict.h"

void Analyze(
			 const char* networkPath,
			 const char* datasetPath,
			 const int noImages,
			 const int showLogs) {
	
	int noChars = NO_CHARACTERS;
	int imgsPerChar = noImages;
	
	long numTrainingSets = noChars * imgsPerChar;
	
	
	// MARK: Loading
	
	
	MMImage* dataSet = LoadDataset(datasetPath, noChars, imgsPerChar); // Load dataset
	
	MMNetwork network = LoadNetwork(networkPath); // Load network
	
	
	
	//MARK: Test
	
	
	int success = 0;
	int fails = 0;
	int failsWoutCase = 0;
	
	for (int dsIdx = 0; dsIdx < numTrainingSets; dsIdx ++) {
		MMImage* img = &dataSet[dsIdx];
		
		double* output = Predict(network, img); // Get output layer for prediction
		
		char detectedAs = OutputChar(output); // Get predicted character
		
		
		if (detectedAs == img -> character) {
			success++;
		} else {
			if (!MatchCharNoCase(detectedAs, img -> character)) { // If same char but different case
				failsWoutCase++;
			}
			fails++;
		}
		
		if (showLogs) {
			printf("Detected as a %c, was a %c.\n", detectedAs, img -> character);
		}
		
	}
	
	// Calcul success rate
	double total = success + fails;
	double rate = 1.0f - (fails / total);
	double percentRate = 100.0f * rate;
	
	int successWoutCase = total - failsWoutCase; 			//TODO: It's ugly
	double rateWoutCase = 1.0 - (failsWoutCase / total);	// "
	double percentRateWoutCase = 100.0f * rateWoutCase;		// "
	
	
	
	// Show results
	
	printf("\n\n%d success\n%d fails\n", success, fails);
	printf("Success rate = %.2f%%\n\n", percentRate);
	
	printf("If not checking case:\n");
	printf("%d success\n%d fails\n", successWoutCase, failsWoutCase);
	printf("Success rate = %.2f%%\n\n", percentRateWoutCase);
	
	DestroyNetwork(network);
}




int main(int argc, const char * argv[]) {
	
#ifdef XCODE // If run in Xcode: parameters are predefined (see Macros.h)
	char* networkPath = NETWORK_PATH;
	char* datasetPath = DATASET_PATH;
	int noImages = 100;
	int showLogs = 1;
#else
	if (argc < 4) { // 3 args minimum (+ executable path)
		errx(1, "Not enough arguments\n\nUsage:\n%s networkPath datasetPath noImages -l", argv[0]);
	}
	
	const char* networkPath = argv[1];
	const char* datasetPath = argv[2];
	const int noImages =  strtoul(argv[3], NULL, 10);
	
	int showLogs = 0;
	if (argc >= 5) { // If there is a 4th arg...
		if (strcmp(argv[4], "-l") == 0) { // ... and it is "-l", show logs.
			showLogs = 1;
		}
	}
#endif
	
	Analyze(networkPath, datasetPath, noImages, showLogs);
	

	
}
