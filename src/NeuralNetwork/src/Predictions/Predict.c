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

char OutputChar(double* outputLayer, MMContext* ctx) {

	int detectedAs;
	
	detectedAs = 0;
	double max = outputLayer[0];
	
	for (int i = 1; i < ctx->nb_classes; i++)
	{
		if (outputLayer[i] > max)
		{
			max = outputLayer[i];
			detectedAs = i;
		}
	}
	//printf("DEBUG intermediate: %g -> %d\n", max, detectedAs);
	
	return ctx->classes[detectedAs];
}


/*
 * Compare two Guess instances by their score
 */
int compareGuess(const void* a, const void* b) {
	MMGuess sA = *(MMGuess*) a;
	MMGuess sB = *(MMGuess*) b;

	if ( sA.score == sB.score ) return 0;
	else if ( sA.score < sB.score ) return 1;
	else return -1;
}

/*
 * Get more details about the prediction than just the OutputChar function.
 * This will return a pointer of array of MMGuess, sorted by success rate.
 * Don't forget to free later!
 *
 * Params:
 *	double* : Output layer of the neural network after prediction
 *	MMContext* : The context to use for prediction output
 *
 * Returns:
 *	MMGuess* : Pointer to array of MMGuess
 */
MMGuess* PredictionDetails(double* outputLayer, MMContext* ctx) {
	
	size_t l = ctx->nb_classes;
	MMGuess* guessList = calloc(l, sizeof(MMGuess));
	
	double sum = 0;
	for (size_t i = 0; i < l; i++) {
		sum += outputLayer[i];
	}
	
	for (size_t i = 0; i < l; i++) {
		guessList[i].character = ctx->classes[i];
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
		double c = image -> pixelsTable[i].pixelValue;
		test_input[i] = c;
	}
	
	return PredictRaw(network, test_input);
}

/*
 * Make a prediction from raw inputs, not a MMImage.
 *
 * Params:
 *	MMNetwork : Network to use for prediction
 *	double* : Inputs
 *
 * Returns:
 *	double* : Output layer of the network prediction
 */
double* PredictRaw(MMNetwork network, double* inputs) {
	double* hiddenLayer = HiddenLayer(network);
	double* outputLayer = OutputLayer(network);
	
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
	
	free(hiddenLayer);
	
	return outputLayer;
}
