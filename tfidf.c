#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct 
{
    char word[100];
    int score;
} WordTFIDF;

int wordCounterAndVectorFiller(FILE *arc, char *wordVector)
{
    int i = 0, wordCounter = 0;
    int aux = 0;
    char newWord[100], c;
    while ((c = fgetc(arc)) != EOF)
    {
        if (c >= 65 && c <= 90) 
        {
            c += 32;
        } 
        if (c >= 97 && c <= 122) 
        {
            newWord[i] = c;
            ++i;
        }
        else
        {
            aux = 1;
        }
        if (aux)
        {
            if (i > 3)
            {
                for (int j = 0; j < i; j++) {
                    *wordVector[wordCounter][j] = newWord[j];
                }
            }
            ++wordCounter;
            i = 0;
        }
    }
    return wordCounter;
}