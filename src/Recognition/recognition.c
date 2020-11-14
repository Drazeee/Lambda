#include "recognition.h"

char recognition(MMImage img, MMNetwork n) {
    double *output = Predict(n, &img);
    char character = OutputChar(output);
    return character;
}