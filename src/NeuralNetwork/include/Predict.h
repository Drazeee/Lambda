//
//  Predict.h
//  DigitsLearning
//
//  Created by Maxime on 10/10/2020.
//

#ifndef Predict_h
#define Predict_h

#include "Network.h"
#include "Dataset.h"
#include "Macros.h"

typedef struct MMGuess {
	char	character;
	double	score;
	double 	rate;
} MMGuess;

int compareGuess(const void* a, const void* b);
char OutputChar(double* outputLayer, MMContext* ctx);
MMGuess* PredictionDetails(double* outputLayer, MMContext* ctx);
double*	Predict(MMNetwork network, const MMImage* image);
double* PredictRaw(MMNetwork network, double* inputs);


#endif /* Predict_h */
