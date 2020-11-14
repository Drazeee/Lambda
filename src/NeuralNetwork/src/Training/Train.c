//
//  Train.c
//  DigitsLearning
//
//  Created by Maxime on 26/10/2020.
//

#include <stdio.h>
#include "Train.h"

#define LOGS 0 // Show every test output
#define LEARNING_RATE 0.3


MMTrainingStats Train(MMNetwork network, int* trainingSetOrder, int numTrainingSets, MMImage* dataSet, double* hiddenLayer, double* outputLayer) {
	
	int fails = 0;
	int success = 0;
	
	shuffle(trainingSetOrder,numTrainingSets);
	
	
	
	for (int x = 0; x < numTrainingSets; x++) {
		int i = trainingSetOrder[x];
		
		/* Forward pass */
		
		for (int j=0; j < network.numHiddenNodes; j++) {
			double activation = network.hiddenLayerBias[j];
			
			for (int k=0; k < network.numInputs; k++) {
				
				activation += dataSet[i].pixelsTable[k].pixelValue * network.hiddenWeights[j].weights[k];
			}
			hiddenLayer[j] = Sigmoid(activation);
		}
		
		for (int j=0; j < network.numOutputs; j++) {
			double activation = network.outputLayerBias[j];
			for (int k=0; k < network.numHiddenNodes; k++) {
				activation += hiddenLayer[k] * network.outputWeights[k].weights[j];
			}
			outputLayer[j] = Sigmoid(activation);
		}
		
		
		//MARK: Tests & stats
		char detectedAs = OutputChar(outputLayer);
		
		if (detectedAs != dataSet[i].character) {
			fails ++;
		} else {
			success ++;
		}
		
#if (LOGS)
		printf("Outputs: [");
		for (int outputToShow = 0; outputToShow < network.numOutputs; outputToShow++) {
			printf("%.2f ", outputLayer[outputToShow]);
		}
		//printf("] Letter: %c\n", dataSet[i].character);
		
		//printf("Detected as a %c (r=%.2f), was %c\n\n", detectedAs, max, dataSet[i].character);
#endif
			
		
		/* Backprop */
		
		double deltaOutput[network.numOutputs];
		for (int j = 0; j < network.numOutputs; j++) {
			double errorOutput = (dataSet[i].expectedOutput[j] - outputLayer[j]);
			deltaOutput[j] = errorOutput * dSigmoid(outputLayer[j]);
		}
		
		double deltaHidden[network.numHiddenNodes];
		for (int j = 0; j < network.numHiddenNodes; j++) {
			double errorHidden = 0.0f;
			for (int k=0; k < network.numOutputs; k++) {
				errorHidden += deltaOutput[k] * network.outputWeights[j].weights[k];
			}
			deltaHidden[j] = errorHidden * dSigmoid(hiddenLayer[j]);
			
		}
		
		for (int j = 0; j < network.numOutputs; j++) {
			network.outputLayerBias[j] += deltaOutput[j] * LEARNING_RATE;
			for (int k = 0; k < network.numHiddenNodes; k++) {
				network.outputWeights[k].weights[j] += hiddenLayer[k] * deltaOutput[j] * LEARNING_RATE;
			}
		}
		
		for (int j = 0; j < network.numHiddenNodes; j++) {
			
			network.hiddenLayerBias[j] += deltaHidden[j] * LEARNING_RATE;
			for (int k = 0; k < network.numInputs; k++) {
				network.hiddenWeights[j].weights[k] += dataSet[i].pixelsTable[k].pixelValue * deltaHidden[j] * LEARNING_RATE;
			}
		}
	}
	
	
	// Print gen results
	double total = success + fails;
	double rate1 = fails / total;
	double rate = 1.0f - rate1;
	
	MMTrainingStats stats;
	stats.fails = fails;
	stats.success = success;
	stats.rate = rate;
	stats.total = total;
		
	return stats;

}
