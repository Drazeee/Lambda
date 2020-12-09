//
//  main.c
//  Test
//
//  Created by Maxime on 04/12/2020.
//

#include <stdio.h>
#include "Predict.h"

int main(int argc, const char * argv[]) {
//	MMImage i = LoadImage("/Users/maxime/datasetXFIXWACC/0/1502.bmp");
   MMImage i = LoadImage("/Users/maxime/Documents/u.bmp");
	 PrintImage(i);

	
	MMNetwork accentNetwork = LoadNetwork("/Users/maxime/IAACC");
	 
	double* accOutput = Predict(accentNetwork, &i);
	//char outputAccent = OutputChar(accOutput, &ACC_CTX);
	 
	 MMGuess pred = PredictionDetails(accOutput, &ACC_CTX)[0];
	 //char* outputAccent;
	
	MMNetwork charNetwork = LoadNetwork("/Users/maxime/IACHAR");
	double* charOutput = Predict(charNetwork, &i);
	char character = OutputChar(charOutput, &CHARS_CTX);

		
	char* s = "sans accent";
	 if (pred.rate > 50) {
		 switch (pred.character) {
			 case 0:
				 s = "cedil";
				 break;
				 
			 case 1:
				 s = "accent grave";
				 break;
			 
			 case 2:
				 s = "accent aigu";
				 break;
			 
			 case 3:
				 s = "accent circonflexe";
				 break;
				 
			 case 4:
				 s = "trema";
				 break;
				 
			 default:
				 break;
		 }
	 }
	
	printf("Output: \"%c\" %s\n", character, s);
}
