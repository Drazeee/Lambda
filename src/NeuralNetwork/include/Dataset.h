//
//  Dataset.h
//  Predicate
//
//  Created by Maxime on 19/09/2020.
//

#ifndef Dataset_h
#define Dataset_h

#include "../Globals/Functions.h"
#include "Structs.h"
#include "../Macros.h"

MMImage		LoadImage(const char* path);
MMImage*	LoadDataset(
					const char* path,
					const int noDigits,
					const int imagesPerDigit
				);

MMImage TrainingData(int noInputs, double* inputs, int noOutputs, double* expectedOutput);

MMImage MakeFakeData(int noInputs, double* inputs, int noOutputs, double* outputs);
#endif /* Dataset_h */

