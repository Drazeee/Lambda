//
//  MMNetwork Struct.h
//  DigitsLearning
//
//  Created by Maxime on 04/10/2020.
//

#ifndef MMNetwork_Struct_h
#define MMNetwork_Struct_h

typedef struct MMNode
{
	double  *weights;
}
MMNode;

typedef struct MMNetwork
{
	int     numInputs;
	int     numHiddenNodes;
	int     numOutputs;
	
	double  *hiddenLayerBias;
	double  *outputLayerBias;
	
	MMNode  *hiddenWeights;
	MMNode  *outputWeights;
}   MMNetwork;


#endif /* MMNetwork_Struct_h */
