//
//  Predict.c
//  DigitsLearning
//
//  Created by Maxime on 10/10/2020.
//


#include <stdio.h>
#include "Predict.h"


/*
 * Returns a char corresponding to the output of a prediction
 * from the output layer values
 *
 * Params:
 *	double* : outputLayer values
 *
 * Returns:
 *	char : Output char
 */

char OutputChar(double* outputLayer) {
	int detectedAs;
	
	detectedAs = 0;
	double max = outputLayer[0];
	
	for (int i = 0; i < NO_CHARACTERS; i++)
	{
		if (outputLayer[i] > max)
		{
			max = outputLayer[i];
			detectedAs = i;
		}
	}
		
	return ORDER[detectedAs];
}


/*
 * Private function:
 * Compare two Guess instances by their score
 */
int compareGuess(const void* a, const void* b) {
	MMGuess sA = *(MMGuess*) a;
	MMGuess sB = *(MMGuess*) b;

	if ( sA.score == sB.score ) return 0;
	else if ( sA.score < sB.score ) return 1;
	else return -1;
}

MMGuess* PredictionDetails(double* outputLayer) {
	
	size_t l = NO_CHARACTERS;
	MMGuess* guessList = calloc(l, sizeof(MMGuess));
	
	double sum = 0;
	for (size_t i = 0; i < l; i++) {
		sum += outputLayer[i];
	}
	
	for (size_t i = 0; i < l; i++) {
		guessList[i].character = ORDER[i];
		guessList[i].score = outputLayer[i];
		guessList[i].rate = outputLayer[i] / sum * 100;
	}
	
	qsort( guessList, l, sizeof(MMGuess), compareGuess );
	
	return guessList;
}


/*
 * Make a Prediction for the specified network and image
 *
 * Params:
 *	MMNetwork : Neural network
 *	MMImage* : Image containing a character to recognize
 *
 * Returns:
 *	double* : Output layer of the network prediction
 */
double* Predict(MMNetwork network, const MMImage* image) {
	double test_input[network.numInputs];
	
	// Get all pixels in a single array
	for (int i = 0; i < network.numInputs; i++) {
		int c = image -> pixelsTable[i].pixelValue;
		test_input[i] = c;
	}
	
	return PredictRaw(network, test_input);
}

double* PredictRaw(MMNetwork network, double* inputs) {
	double hiddenLayer[network.numHiddenNodes]; // TODO: Calloc ?
	double* outputLayer;
	outputLayer = calloc(network.numOutputs, sizeof(double));
	
	// Get hidden nodes values
	for (int j = 0; j < network.numHiddenNodes; j++) {
		double activation = network.hiddenLayerBias[j];
		for (int k = 0; k < network.numInputs; k++) {
			activation += inputs[k] * network.hiddenWeights[j].weights[k];
		}
		hiddenLayer[j] = Sigmoid(activation);
	}
	
	// Get output nodes values
	for (int j=0; j < network.numOutputs; j++) {
		double activation = network.outputLayerBias[j];
		for (int k=0; k < network.numHiddenNodes; k++) {
			activation += hiddenLayer[k] * network.outputWeights[k].weights[j];
		}
		outputLayer[j] = Sigmoid(activation);
	}
	
	
	return outputLayer;
}
