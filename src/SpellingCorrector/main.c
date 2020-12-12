#include "distance.h"

int main(int argc,char* argv[])
{
    if (argc == 2){
        FILE* dico = fopen("dico.txt","r");
        char* dictionnary[336524];
        int min = 10;
        char* motFinal;

        for (int i = 0; i < 336524; i++)
        {
            char* pointer;

            pointer = calloc(MAX_SIZE,sizeof(char));
            pointer = fgets(pointer,MAX_SIZE,dico);
            dictionnary[i] = pointer;
            strtok(dictionnary[i], "\n");
        }

        for (size_t i = 0; i < 336524; i++)
        {
            int result = distance(argv[1],dictionnary[i]);
            if (abs(result) < 2) {
                printf("%s\n", dictionnary[i]);
            }
            if (min > result){
                min = result;
                motFinal = dictionnary[i];
            }
        }
        printf("%i\n",min);
        printf("%s\n",motFinal);
    }
    return 0;
}
