//
//  Train.c
//  DigitsLearning
//
//  Created by Maxime on 26/10/2020.
//

#include <stdio.h>
#include "Train.h"

#define LOGS 0 // Show every test output

/*
 * Main function for training a MMNetwork.
 * Here applies the whole training by backpropagation.
 * This is a training for only one generation.
 * This will return statistics about this generation after this training.
 *
 * Params:
 *	MMNetwork : The network to train
 *	MMImage* : The dataset to use for training
 *	MMTrainingEnvironment : Environment for the training
 *	MMContext* : Context to use for the training
 *
 * Returns:
 *	MMTrainingStats : Statistics about this generation training
 */
MMTrainingStats Train(MMNetwork network, MMImage* dataset, MMTrainingEnvironment env, MMContext* ctx) {
	int fails = 0;
	int success = 0;
	
	shuffle(env.trainingSetOrder,env.trainingSetSize);
	
	
	
	for (int x = 0; x < env.trainingSetSize; x++) {
		int i = env.trainingSetOrder[x];
		
		/* Forward pass */
		
		for (int j=0; j < network.numHiddenNodes; j++) {
			double activation = network.hiddenLayerBias[j];
			
			for (int k=0; k < network.numInputs; k++) {
				
				activation += dataset[i].pixelsTable[k].pixelValue * network.hiddenWeights[j].weights[k];
			}
			env.hiddenLayer[j] = Sigmoid(activation);
		}
		
		for (int j=0; j < network.numOutputs; j++) {
			double activation = network.outputLayerBias[j];
			for (int k=0; k < network.numHiddenNodes; k++) {
				activation += env.hiddenLayer[k] * network.outputWeights[k].weights[j];
			}
			env.outputLayer[j] = Sigmoid(activation);
		}
		
		
		//MARK: Tests & stats
		char detectedAs = OutputChar(env.outputLayer, ctx);
		
		if (detectedAs != dataset[i].character) {
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
			double errorOutput = (dataset[i].expectedOutput[j] - env.outputLayer[j]);
			deltaOutput[j] = errorOutput * dSigmoid(env.outputLayer[j]);
		}
		
		double deltaHidden[network.numHiddenNodes];
		for (int j = 0; j < network.numHiddenNodes; j++) {
			double errorHidden = 0.0f;
			for (int k=0; k < network.numOutputs; k++) {
				errorHidden += deltaOutput[k] * network.outputWeights[j].weights[k];
			}
			deltaHidden[j] = errorHidden * dSigmoid(env.hiddenLayer[j]);
			
		}
		
		for (int j = 0; j < network.numOutputs; j++) {
			network.outputLayerBias[j] += deltaOutput[j] * env.learningRate;
			for (int k = 0; k < network.numHiddenNodes; k++) {
				network.outputWeights[k].weights[j] += env.hiddenLayer[k] * deltaOutput[j] *  env.learningRate;
			}
		}
		
		for (int j = 0; j < network.numHiddenNodes; j++) {
			
			network.hiddenLayerBias[j] += deltaHidden[j] *  env.learningRate;
			for (int k = 0; k < network.numInputs; k++) {
				network.hiddenWeights[j].weights[k] += dataset[i].pixelsTable[k].pixelValue * deltaHidden[j] *  env.learningRate;
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
