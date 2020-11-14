//
//  Network.c
//  DigitsLearning
//
//  Created by Maxime on 30/09/2020.
//

#include <stdlib.h>
#include "Network.h"
#include <string.h>


//MARK: Alloc functions

/*
 * Allocate AND Initialize a new MMNetwork instance from input parameters
 *
 * Params:
 *	int : Amount of neurons on the input layer
 *	int : Amount of neurons on the hidden layer
 *	int : Amount of output neurons
 */
MMNetwork InitNetwork(int numInputs, int numHiddenNodes, int numOutputs)
{
	MMNetwork n;
	int   node;
	
	n.numInputs = numInputs;
	n.numHiddenNodes = numHiddenNodes;
	n.numOutputs = numOutputs;

	n.hiddenLayerBias = (double*)calloc(numHiddenNodes, sizeof(double));
	n.outputLayerBias = (double*)calloc(numOutputs, sizeof(double));

	n.hiddenWeights = (MMNode*)calloc(numHiddenNodes, sizeof(MMNode));
	n.outputWeights = (MMNode*)calloc(numHiddenNodes, sizeof(MMNode));
	
	for (node = 0; node <numHiddenNodes; node++) {
		n.hiddenWeights[node].weights = calloc(numInputs, sizeof(double));
		n.outputWeights[node].weights = calloc(numOutputs, sizeof(double));
	}

	return n;
}

/*
 Free memory of network allocation
 *
 * Params:
 *	MMNetwork : The network to free from memory
 */
void DestroyNetwork(struct MMNetwork n) {
	
	free(n.hiddenLayerBias);
	free(n.outputLayerBias);

	for (short node = 0; node <n.numHiddenNodes; node++) {
		free(n.hiddenWeights[node].weights);
		free(n.outputWeights[node].weights);
	}
	free(n.hiddenWeights);
	free(n.outputWeights);
}

/*
 * Copy a network into a new identical one.
 *
 * Params:
 *	MMNetwork* : The source network
 *
 * Returns:
 *	MMNetwork : The destination network
 */
MMNetwork CopyNetwork(MMNetwork *s) {
	MMNetwork d;

    d.numInputs = s->numInputs;
    d.numHiddenNodes = s->numHiddenNodes;
    d.numOutputs = s->numOutputs;

    d.hiddenLayerBias = (double*)calloc(d.numHiddenNodes, sizeof(double));
    d.outputLayerBias = (double*)calloc(d.numOutputs, sizeof(double));
	
    memcpy(
		   d.hiddenLayerBias,
		   s->hiddenLayerBias,
		   sizeof(double)*d.numHiddenNodes
		);
	
    memcpy(
		   d.outputLayerBias,
		   s->outputLayerBias,
		   sizeof(double)*d.numOutputs
		);

    d.hiddenWeights = (MMNode*)calloc(d.numHiddenNodes, sizeof(MMNode));
    d.outputWeights = (MMNode*)calloc(d.numHiddenNodes, sizeof(MMNode));
    for (short node = 0; node < d.numHiddenNodes; node++) {
        d.hiddenWeights[node].weights = calloc(d.numInputs, sizeof(double));
        d.outputWeights[node].weights = calloc(d.numOutputs, sizeof(double));
		
        memcpy(
		    d.hiddenWeights[node].weights,
			s->hiddenWeights[node].weights,
			sizeof(double)*d.numInputs
		);
		
        memcpy(
			d.outputWeights[node].weights,
			s->outputWeights[node].weights,
			sizeof(double)*d.numOutputs
		);
    }

    return d;
}

//TODO: Management functions


/*
 * Generate a random number in [-0.5; 0.5].
 * This is used to initialize network weights and nodes biases.
 */
double init_weight() {
	float r = (float)rand() / (float)RAND_MAX;
	return r - 0.5;
}

/*
 * Set random weights for specified neural network nodes.
 * Function used to generate random weights is init_weight.
 *
 * Params:
 *	MMNetwork : The network to set weights for.
 */
void InitWeightsForNetwork(MMNetwork network) {
	for (int i=0; i < network.numInputs; i++) {
		for (int j=0; j < network.numHiddenNodes; j++) {
			network.hiddenWeights[j].weights[i] = init_weight();
		}
	}
	for (int i=0; i < network.numHiddenNodes; i++) {
		network.hiddenLayerBias[i] = init_weight();
		for (int j=0; j < network.numOutputs; j++) {
			network.outputWeights[i].weights[j] = init_weight();
		}
	}
	for (int i=0; i < network.numOutputs; i++) {
		network.outputLayerBias[i] = init_weight();
	}
}

/*
 * Init an hidden layer.
 * Just a shortcut for a basic calloc.
 *
 * Parameters:
 *	MMNetwork
 *
 * Returns:
 *	double* : The hidden Layer
 */
double* HiddenLayer(MMNetwork network) {
	return calloc(network.numHiddenNodes, sizeof(double));
}


/*
 * Init an output layer.
 * Just a shortcut for a basic calloc.
 *
 * Parameters:
 *	MMNetwork
 *
 * Returns:
 *	double* : The output Layer
 */
double* OutputLayer(MMNetwork network) {
	return calloc(network.numOutputs, sizeof(double));

}

