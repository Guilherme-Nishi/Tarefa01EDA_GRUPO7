#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include "FileManager.c"


int main() {
    int Menu;
    char Leitura[50];

    FILE *Reviews = NULL;
    FILE *Nota1 = NULL;
    FILE *Nota2 = NULL;
    FILE *Nota3 = NULL;
    FILE *Nota4 = NULL;
    FILE *Nota5 = NULL;
    FILE *voc = NULL;
    FILE *allTFIDF = NULL;

    
    char c;
    char word[100];
    int i, count = 0;
    long int pos;

   
    
    char str[200];
    double wordCountN1, wordCountN2, wordCountN3, wordCountN4, wordCountN5, nWordsN1, nWordsN2, nWordsN3, nWordsN4, nWordsN5;
    double nDocWithWord;
    double TF_IDF1, TF_IDF2, TF_IDF3, TF_IDF4, TF_IDF5, IDF, TF1, TF2, TF3, TF4, TF5, x;

    do {
    
    printf("1.LEITURA DE ARQUIVO");
    printf("2.GERACAO DE VOCABULARIO\n");
    printf("3.GERACAO TF-ID \n");
    printf("4.VIZUALIZAR TF-ID \n");
    printf("5.SAIR")
  		scanf("%d", &Menu);
        switch (Menu) {
            case 1:
                printf("-> ./files/reviews.csv\n");
                printf("Digite o nome do arquivo: ");
                scanf("%s", Leitura); 

                Reviews = openFile(Leitura);

                if(Reviews == NULL) {
                    printf("Arquivo não gerados\n");
                    break;
                }
               
                Nota1 = fopen("./files/Nota1.txt", "w");
                Nota2 = fopen("./files/Nota2.txt", "w");
                Nota3 = fopen("./files/Nota3.txt", "w");
                Nota4 = fopen("./files/Nota4.txt", "w");
                Nota5 = fopen("./files/Nota5.txt", "w");



                printf("Arquivos gerados com sucesso");
                break;
            case 2:

                printf("Adicionando o vocabulario no arquivo voc.txt");
                if(Reviews != NULL) 
                    fclose(Reviews);
                
                if(voc != NULL)
                    fclose(voc);

                Reviews = fopen("./files/reviews.csv", "r");
                voc = fopen("./files/voc.txt", "w+");

                while((c = fgetc(Reviews)) != EOF) {
            if(c == '"') {
                while((c = fgetc(Reviews)) != '"') {
                i = 0;
                pos = ftell(voc);
                           
                while(!isEndWord(c)) {
                         
                                word[i] = c;
                                c = fgetc(Reviews); 
                                i++;
                            }
                  
                            word[i] = '\n';
                    
                            if(i > 3) {
                 
                                if(!checkForRepeatedWords2(word, voc)){
                                  
                                    fputs(word, voc);
                                
                                    count ++;
                                 
                                }
                            }

                            memset(word, 0, 100); 
                        }
                        
                    }
                } 
              
                break;
            case 3:
                if(voc != NULL)
                    fclose(voc);

                if(Nota1 != NULL) {
                    fclose(Nota1);
                    fclose(Nota2);
                    fclose(Nota3);
                    fclose(Nota4);
                    fclose(Nota5);
                }
                
                voc = fopen("files/voc.txt", "r");
                Nota1 = fopen("files/Nota1.txt", "r");
                Nota2 = fopen("files/Nota2.txt", "r");
                Nota3 = fopen("files/Nota3.txt", "r");
                Nota4 = fopen("files/Nota4.txt", "r");
                Nota5 = fopen("files/Nota5.txt", "r");
                allTFIDF = fopen("files/allTFIDF.csv", "w");

                nWordsN1 = numberOfWordsInFile(Nota1);
                nWordsN2 = numberOfWordsInFile(Nota2);
                nWordsN3 = numberOfWordsInFile(Nota3);
                nWordsN4 = numberOfWordsInFile(Nota4);
                nWordsN5 = numberOfWordsInFile(Nota5);

                printf("Gerando o arquivo dos TF-IDFs...\n"); 
                fputs("Vocabulario,Nota1,Nota2,Nota3,Nota4,Nota5\n", allTFIDF);
                while((c = fgetc(voc)) != EOF) {
                    i = 0;
                    nDocWithWord = 0;

          
                    while(!isEndWord(c)) {
                        word[i] = c;
                        c = fgetc(voc);
                        i++;
                    }
                   
                    wordCountN1 = wordCountInFile(word, Nota1);  
                    wordCountN2 = wordCountInFile(word, Nota2);  
                    wordCountN3 = wordCountInFile(word, Nota3);  
                    wordCountN4 = wordCountInFile(word, Nota4);  
                    wordCountN5 = wordCountInFile(word, Nota5);

                    if(wordCountN1)
                        nDocWithWord++;
                    if(wordCountN2)
                        nDocWithWord++;
                    if(wordCountN3)
                        nDocWithWord++;
                    if(wordCountN4)
                        nDocWithWord++;
                    if(wordCountN5)
                        nDocWithWord++;
                    
                    if(nDocWithWord == 0)
                        nDocWithWord = 1;
                    
                    //calcula o TF-IDF
                    x = 5.0/nDocWithWord; 
                    IDF = log10(x); 
                    TF1 = wordCountN1/nWordsN1;
                    TF2 = wordCountN2/nWordsN2;
                    TF3 = wordCountN3/nWordsN3;
                    TF4 = wordCountN4/nWordsN4;
                    TF5 = wordCountN5/nWordsN5;

                    TF_IDF1 = TF1 * IDF; 
                    TF_IDF2 = TF2 * IDF;
                    TF_IDF3 = TF3 * IDF;
                    TF_IDF4 = TF4 * IDF;
                    TF_IDF5 = TF5 * IDF;

                    sprintf(str, "\"%s\",%.10lf,%.10lf,%.10lf,%.10lf,%.10lf\n", word, TF_IDF1, TF_IDF2, TF_IDF3, TF_IDF4, TF_IDF5);

                    fputs(str, allTFIDF);
     

                    memset(word, 0, 100);
                }

                break;
            case 4:

                if(allTFIDF != NULL)
                    fclose(allTFIDF);

                allTFIDF = fopen("./files/allTFIDF.csv", "r");
               
                printf("-> nota1, nota2, nota3, nota4 ou nota5\n");
                printf("Digite o TF-IDF a ser visualizado: ");
                scanf("%s", Leitura);
                if(strcmp(Leitura, "nota1") == 0) { 
                    sortTFIDF(allTFIDF, 1);
                    break;
                } else if(strcmp(Leitura, "nota2") == 0) {
                    sortTFIDF(allTFIDF, 2);
                    break;
                } else if(strcmp(Leitura, "nota3") == 0) {
                    sortTFIDF(allTFIDF, 3);
                    break;
                } else if(strcmp(Leitura, "nota4") == 0) {
                    sortTFIDF(allTFIDF, 4);
                    break;
                } else if(strcmp(Leitura, "nota5") == 0) {
                    sortTFIDF(allTFIDF, 5);
                    break;
                } else
                    printf("Entrada inválida\n"); 

                break;
            case 0:
                break;
            default:
                printf("Digite um numero valido!\n");
                break;
        }
    } while (Menu != 5);

    fclose(Reviews);
    fclose(Nota1);
    fclose(Nota2);
    fclose(Nota3);
    fclose(Nota4);
    fclose(Nota5);
    fclose(voc);
    fclose(allTFIDF);
    return 0;
}
}
