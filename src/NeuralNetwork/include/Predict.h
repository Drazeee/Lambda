//
//  Predict.h
//  DigitsLearning
//
//  Created by Maxime on 10/10/2020.
//

#ifndef Predict_h
#define Predict_h

#include "../Network/Network.h"
#include "../Dataset/Dataset.h"
#include "../Macros.h"

typedef struct MMGuess {
	char	character;
	double	score;
	double 	rate;
} MMGuess;

char 	OutputChar(double* outputLayer);
MMGuess* PredictionDetails(double* outputLayer);
double*	Predict(MMNetwork network, const MMImage* image);
double* PredictRaw(MMNetwork network, double* inputs);


#endif /* Predict_h */
