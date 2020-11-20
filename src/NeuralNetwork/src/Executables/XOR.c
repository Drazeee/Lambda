//
//  main.c
//  XOR
//
//  Created by Maxime on 26/10/2020.
//

#include <stdio.h>
#include "Network.h"
#include "Dataset.h"
#include "Train.h"
#include "Predict.h"

#define NO_HIDDEN_NODES 3
#define NO_GENS 50000
#define LEARNING_RATE 0.1


int main() {
	
	// Get data
	double data_raw[4 * 3] = {
		0.0, 0.0,	0.0,
		0.0, 1.0,	1.0,
		1.0, 0.0,	1.0,
		1.0, 1.0,	0.0
	};
	
	
	MMImage trainingData[4];
	
	for (short i = 0; i < 4; i++) {
		double inputs[2] = {data_raw[3 * i], data_raw[3 * i + 1]};
		double outputs[1] = {data_raw[3 * i + 2]};
		trainingData[i] = MakeFakeData(2, inputs, 1, outputs);
	}
	
	
	// Init network
	
	srand((unsigned)time(NULL)); // Init random seed
	
	MMNetwork network = InitNetwork(2, NO_HIDDEN_NODES, 1);
	InitWeightsForNetwork(network);
	
	
	// Train
	MMTrainingEnvironment env = TrainingEnvironment(network, 4, LEARNING_RATE);
	
	
	printf("Training...\n");
	for (int training = 0; training < NO_GENS; training ++) {
		Train(network, trainingData, env);
	}
	printf("Trained!\n\n");
	
	// Tests
		
	for (int test = 0; test < 4; test ++) {
		
		double* o = Predict(network, &trainingData[test]);
		double about = (o[0] >= 0.5);
		
		printf("%.0f ⊕ %.0f = %f ~ %.0f (Expected: %.0f)\n",
			   trainingData[test].pixelsTable[0].pixelValue,
			   trainingData[test].pixelsTable[1].pixelValue,
			   o[0],
			   about,
			   trainingData[test].expectedOutput[0]
			);
		
	}
	


	return 0;
}
