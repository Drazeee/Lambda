//
//  Dataset.h
//  Predicate
//
//  Created by Maxime on 19/09/2020.
//

#ifndef Dataset_h
#define Dataset_h

#include "Functions.h"
#include "Structs.h"
#include "Context.h"
#include "Macros.h"

MMImage		LoadImage(const char* path);
MMImage*	LoadDataset(
					const char* path,
					const int noDigits,
					const int imagesPerDigit,
					MMContext* ctx
				);

MMImage MakeFakeData(int noInputs, double* inputs, int noOutputs, double* outputs);
void PrintImage(MMImage* img);
void DestroyImage(MMImage* img);
void DestroyDataset(long noImages, MMImage* dataset);
#endif /* Dataset_h */

