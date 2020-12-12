#include "distance.h"

/* Find the minimum of 3 int
 *
 * Params:
 *  int a: first int
 *  int b: second int
 *  int c: third int
 * 
 * Returns: the minimum.
 */

static int minimum (int a,int b, int c){
    int minimum = a;
    if (a > b){
        minimum = b;
    }
    if (minimum > c){
        minimum = c;
    }
    return minimum;
}

/*
 * Find the distance of levenshtein for 2 words A,B.
 *
 * Params:
 *  char* : word a.
 *  char* : word b.
 * 
 * Returns:
 *  int : returns the levenshtein distance with A and B.

*/

static void toLower(char *str) {
    int i = 0;
    while (str[i] != 0)
    {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            *(str + i) += 32;
        }
        i++;
    }
}

int distance(char* a,char* b){
    toLower(a);
    toLower(b);
    int lenA = strlen(a);
    int lenB = strlen(b);
    int matrice[lenA][lenB];
    int check;

    for (int i = 0; i < lenA; i++)
    {
        matrice[i][0] = i;
    }
    for (int j = 1; j < lenB; j++)
    {
        matrice[0][j] = j;
    }
    for (int i = 1; i < lenA; i++)
    {
        for (int j = 1; j < lenB; j++)
        {
            if (a[i] == b[j]){
                check = 0;
            }
            else
            {
                check = 1;
            }
            matrice[i][j] = minimum(1 + matrice[i][j - 1], 1 + matrice[i-1][j], check + matrice[i-1][j-1]);
        }
    }
    return matrice[lenA-1][lenB-1];
}

static int min(int a, int b) {
    return a < b ? a : b;
}