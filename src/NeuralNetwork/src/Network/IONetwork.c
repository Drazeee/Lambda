//
//  IONetwork.c
//  DigitsLearning
//
//  Created by Maxime on 03/10/2020.
//


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "Network.h"
#include "Functions.h"


/*
 * Prints hidden/output weights/biases for a network
 */
void PrintNetwork(const MMNetwork n) {
	
	printf("Inputs: %d\n", n.numInputs);
	printf("Hidden nodes: %d\n", n.numHiddenNodes);
	printf("Outputs: %d\n\n", n.numOutputs);
	
	printf("Final Hidden Weights\n[ ");
	for (int j=0; j < n.numInputs; j++) {
		printf("[ ");
		for(int k=0; k < n.numHiddenNodes; k++) {
			printf("%f ", n.hiddenWeights[k].weights[j]);
		}
		printf("]\n  ");
	}
	printf("]\n");
	
	
	printf("Final Hidden Biases\n[ ");
	for (int j=0; j < n.numHiddenNodes; j++) {
		printf("%f ", n.hiddenLayerBias[j]);
	}
	
	printf("]\n");
	printf("Final Output Weights\n[ ");
	for (int j=0; j < n.numHiddenNodes; j++) {
		printf("[ ");
		for (int k=0; k < n.numOutputs; k++) {
			printf("%f ", n.outputWeights[j].weights[k]);
		}
		printf("]\n  ");
	}
	printf("\n");
	
	
	printf("Final Output Biases\n[ ");
	for (int j=0; j < n.numOutputs; j++) {
		printf("%f ", n.outputLayerBias[j]);
	}
	printf("]\n\n");
}

/*
 * Save hidden/output weights/biases of a network to a directory.
 * The directory path is defined in the NETWORK_PATH preproc constant
 *
 * Params:
 *	MMNetwork : The network to save
 */
void SaveNetwork(const MMNetwork n, const char *path) {
	
	mkdir(path, 0700);
	
	// Open files
	FILE *hwfile = fopen(concat(path, "/hweights"), "w+");
	FILE *hbfile = fopen(concat(path, "/hbiases"), "w+");
	FILE *owfile = fopen(concat(path, "/oweights"), "w+");
	FILE *obfile = fopen(concat(path, "/obiases"), "w+");
	FILE *paramsFile = fopen(concat(path, "/params"), "w+");
	
	// Write hidden weights
	for (int j=0; j < n.numInputs; j++) {
		for(int k=0; k < n.numHiddenNodes; k++) {
			fprintf(hwfile, "%f\n", n.hiddenWeights[k].weights[j]);
		}
		fprintf(hwfile, "\n");
	}
	
	// Write hidden biases
	for (int j=0; j < n.numHiddenNodes; j++) {
		fprintf(hbfile, "%f\n", n.hiddenLayerBias[j]);
	}
	
	// Write output weigths
	for (int j=0; j < n.numHiddenNodes; j++) {
		for (int k=0; k < n.numOutputs; k++) {
			fprintf(owfile, "%f\n", n.outputWeights[j].weights[k]);
		}
		fprintf(owfile, "\n");
	}
	
	// Write output layer
	for (int j=0; j < n.numOutputs; j++) {
		fprintf(obfile, "%f\n", n.outputLayerBias[j]);
	}
	
	
	// Write parameters
	fprintf(paramsFile, "%d\n", n.numInputs);
	fprintf(paramsFile, "%d\n", n.numHiddenNodes);
	fprintf(paramsFile, "%d\n", n.numOutputs);
	
	// Close files
	fclose(hwfile);
	fclose(owfile);
	fclose(hbfile);
	fclose(obfile);
	fclose(paramsFile);
}

/*
 * Load a network from its files.
 *
 * Params:
 *	char* : Path of network files directory (not ending with a /!)
 */
MMNetwork LoadNetwork(const char* path) {
	
	// Load network parameters
	FILE* paramsFile = fopen(concat(path, "/params"), "r+");
	
	if (paramsFile == NULL) {
		printf("Incorrect file structure (missing params)");
		exit(EXIT_FAILURE);
	}
	
	char *ptrP = "";
	char* lineP = calloc(64, sizeof(char));
	
	// If it crashes here: ensure path is correct and "params" file exists
	fgets(lineP, 64, paramsFile);
	double numInputs = strtod(lineP,&ptrP);
	
	fgets(lineP, 64, paramsFile);
	double numHiddenNodes = strtod(lineP,&ptrP);
	
	fgets(lineP, 64, paramsFile);
	double numOutputs = strtod(lineP,&ptrP);
	
	MMNetwork network = InitNetwork(numInputs, numHiddenNodes, numOutputs);
	
	fclose(paramsFile);
	
	
	// Load hidden weights
	FILE* hwfile = fopen(concat(path, "/hweights"), "r+");

	if (hwfile == NULL) {
		printf("Incorrect file structure (missing hweights)\n");
		exit(EXIT_FAILURE);
	}

	char *ptr = "";
	char* line = calloc(64, sizeof(char));
	
	//
	for (int j=0; j < network.numInputs; j++) {
		for(int k=0; k < network.numHiddenNodes; k++) {
			fgets(line, 64, hwfile);
			double value = strtod(line,&ptr);
			network.hiddenWeights[k].weights[j] = value;
		}
		fgets(line, 64, hwfile);
	}
	
	fclose(hwfile);
	
	
	
	// Load hidden biases
	FILE* hbfile = fopen(concat(path, "/hbiases"), "r+");
	
	if (hbfile == NULL) {
		printf("Incorrect file structure (missing hbiases)\n");
		exit(EXIT_FAILURE);
	}

	char *ptr2 = "";
	char* line2 = calloc(64, sizeof(char));
	
	for (int j=0; j < network.numHiddenNodes; j++) {
		fgets(line2, 64, hbfile);
		double value2 = strtod(line2,&ptr2);
		network.hiddenLayerBias[j] = value2;
	}
	
	fclose(hbfile);
	
	
	// Load output weights
	FILE* owfile = fopen(concat(path, "/oweights"), "r+");
	
	if (owfile == NULL) {
		printf("Incorrect file structure (missing oweights)\n");
		exit(EXIT_FAILURE);
	}
	
	char *ptr3 = "";
	char* line3 = calloc(64, sizeof(char));
	
	//
	
	
	for (int j=0; j < network.numHiddenNodes; j++) {
		for (int k=0; k < network.numOutputs; k++) {
			fgets(line3, 64, owfile);
			double value3 = strtod(line3,&ptr3);
			network.outputWeights[j].weights[k] = value3;
		}
		fgets(line3, 64, owfile);

	}

	fclose(owfile);
	
	
	
	// Load output biases
	FILE* obfile = fopen(concat(path, "/obiases"), "r+");
	
	if (obfile == NULL) {
		printf("Incorrect file structure (missing obiases)\n");
		exit(EXIT_FAILURE);
	}
	
	char *ptr4 = "";
	char* line4 = calloc(64, sizeof(char));
	
	for (int j=0; j < network.numOutputs; j++) {
		fgets(line4, 64, obfile);
		double value4 = strtod(line4,&ptr4);
		network.outputLayerBias[j] = value4;
	}
	
	fclose(obfile);
	
	// Free
	free(lineP);
	free(line);
	free(line2);
	free(line3);
	free(line4);
	
	return network;
}
