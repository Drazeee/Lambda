//
//  Train.h
//  Learning
//
//  Created by Maxime on 26/10/2020.
//

#ifndef Train_h
#define Train_h

#include <stdio.h>
#include "Network.h"
#include "Dataset.h"
#include "Macros.h"
#include "Predict.h"


typedef struct MMTrainingStats {
	int total;
	
	int success;
	int fails;
	double rate;
} MMTrainingStats;

MMTrainingStats Train(MMNetwork network, int* trainingSetOrder, int numTrainingSets, MMImage* dataSet, double* hiddenLayer, double* outputLayer);

#endif /* Train_h */
