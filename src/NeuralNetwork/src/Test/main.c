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
    
    MMNetwork n = LoadNetwork("/Users/maxime/OCR/IA-WC-1200/");
    for (int i = 0; i < 23; i++) {
        char path[70];
        sprintf(path, "/Users/maxime/resultChar/%d.bmp", i);
        MMImage i = LoadImage(path);
        
        double* output = Predict(n, &i);
        
        char c = OutputChar(output);
        
        printf("Output: %c\n", c);
    }
    
    
    return 0;
}
