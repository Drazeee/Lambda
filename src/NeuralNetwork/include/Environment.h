//
//  Environment.h
//  DigitsLearning
//
//  Created by Maxime on 11/11/2020.
//

#ifndef Environment_h
#define Environment_h

#include <stdio.h>
#include "../Network/Network.h"

typedef struct MMTrainingEnvironment {
	MMNetwork network;
	double* hiddenLayer;
	double* outputLayer;
	double learningRate;
	int trainingSetSize;
	int* trainingSetOrder;
	
} MMTrainingEnvironment;

MMTrainingEnvironment TrainingEnvironment(MMNetwork network, int trainingSetSize, double learningRate);

#endif /* Environment_h */
