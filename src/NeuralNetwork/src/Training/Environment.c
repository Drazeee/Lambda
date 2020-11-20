//
//  Environment.c
//  DigitsLearning
//
//  Created by Maxime on 11/11/2020.
//

#include "Environment.h"

MMTrainingEnvironment TrainingEnvironment(MMNetwork network, int trainingSetSize, double learningRate) {
	MMTrainingEnvironment env;
	env.hiddenLayer = HiddenLayer(network);
	env.outputLayer = OutputLayer(network);
	env.learningRate = learningRate;
	env.trainingSetSize = trainingSetSize;
	
	env.trainingSetOrder = calloc(trainingSetSize, sizeof(int));
	
	
	for (int i = 0; i < trainingSetSize;i++) { // TODO: Could be improved
		env.trainingSetOrder[i] = i;
	}
	
	return env;
}
