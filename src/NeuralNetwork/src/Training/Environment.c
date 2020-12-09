//
//  Environment.c
//  DigitsLearning
//
//  Created by Maxime on 11/11/2020.
//

#include "Environment.h"

/*
 * Init a MMTrainingEnvironment from the training environment parameters.
 *
 * Params:
 *	MMNetwork : The network that will be trained
 *	int : Size of the training set
 *	double : Learning rate
 *
 * Returns:
 *	MMTrainingEnvironment : The training environment that could be used in
 *			the Train function
 */
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

void DestroyTrainingEnvironment(MMTrainingEnvironment* env) {
	free(env->hiddenLayer);
	free(env->outputLayer);
	free(env->trainingSetOrder);
	free(env);
}
