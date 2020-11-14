//
//  Network.h
//  DigitsLearning
//
//  Created by Maxime on 30/09/2020.
//

#ifndef Network_h
#define Network_h

#include "../Macros.h"
#include "MMNetwork Structs.h"
#include <stdio.h>


// Alloc functions
MMNetwork	InitNetwork(int numInputs, int numHiddenNodes, int numOutputs);
void		DestroyNetwork(struct MMNetwork n);
MMNetwork	CopyNetwork(MMNetwork *s);



// Management functions
void 		InitWeightsForNetwork(MMNetwork network);



// IONetwork
void 		PrintNetwork(const MMNetwork n);
void 		SaveNetwork(const MMNetwork n, const char* path);
MMNetwork	LoadNetwork(const char* path);

double* HiddenLayer(MMNetwork network);
double* OutputLayer(MMNetwork network);
#endif /* Network_h */
