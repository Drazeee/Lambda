#include "recognition.h"
#include <stdio.h>

char recognition(MMImage img, MMNetwork n) {
    double *output = Predict(n, &img);
    char character = OutputChar(output);
    printf("%d\n", character);
    return character;
}