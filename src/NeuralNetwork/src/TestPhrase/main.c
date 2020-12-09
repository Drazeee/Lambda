//
//  main.c
//  Test
//
//  Created by Maxime on 14/11/2020.
//

#include <stdio.h>
#include "Macros.h"
#include "Network.h"
#include "Dataset.h"
#include "Train.h"
#include "Predict.h"

int main(int argc, const char * argv[]) {
	// insert code here...
	
	MMNetwork n = LoadNetwork("/Users/maxime/IAPYCHAR9/");
	for (int i = 0; i < 23; i++) {
		char path[70];
		sprintf(path, "/Users/maxime/Documents/resultChar/%d.bmp", i);
		MMImage i = LoadImage(path);
		
		double* output = Predict(n, &i);
		//char c = OutputChar(output, &CHARS_CTX);
		MMGuess *c = PredictionDetails(output, &CHARS_CTX);
		
		
		
		//        if (c == 'Q') {
		//            c = 'E';
		//        }
		//printf("Output: %c\n", c);
		//printf("Output: %c ; %c ; %c ; %c ; %c ; %c ; %c ; %c ; %c ; %c \n", c[0].character, c[1].character, c[2].character, c[3].character, c[4].character, c[5].character, c[6].character, c[7].character, c[8].character, c[9].character);
		printf("Outout: %c (%.2f%%)\n", c[0].character, c[0].rate);
	}
	
	scanf( "-", NULL);
	
	return 0;
}
