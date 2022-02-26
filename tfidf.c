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

void tfIDFer(FILE *arc, WordTFIDF *wordTFIDFVector)
{
    //wordVector -- vetor das palavras contidas no arquivo
    //wordTFIDF vector -- vetor usando a struct TFIDF sobre as notas das palavras
    int wordCounter = wordCounterAndVectorFiller(arc, &wordVector);
    for (int i = 0; i < wordCounter; i++)
    {
        if (*wordTFIDFVector[i].word == "") continue;
        for (int j = 0; j < wordCounter; j++)
        {
            if (!strcmp(*wordVector[i], *wordVector[j]))
            {
                *wordTFIDFVector[i].score++;
                *wordVector[j] = "";
            }    
        }
        if (*wordTFIDFVector[i].word != "")
        {
            strcpy(*wordTFIDFVector[i].word, *wordVector[i]);
        }
    }
}