#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include "FileManager.c"


int main() {
	char c;
    char word[100];
    int Menu;
    char Leitura[100];
 	 int i, count = 0;
    int pos;
	 char str[200];
    double Contador1;
	double Contador2;
	double Contador3;
	double Contador4;
	double Contador5;
	double PContadorN1;
	double PContadorN2;
	double PContadorN3;
	double PContadorN4;
	double PContadorN5;
    double nDocWithWord;
    double TF_IDF1;
	double TF_IDF2;
	  double TF_IDF3;
	  double TF_IDF4;
	  double TF_IDF5;
	   double IDF;
		double TF1;
		 double TF2;
		  double TF3;
		  double  TF4;
			double TF5;
			  double x;
			  
			  
FILE *Reviews = NULL;
    FILE *Nota1 = NULL;
    FILE *Nota2 = NULL;
    FILE *Nota3 = NULL;
    FILE *Nota4 = NULL;
    FILE *Nota5 = NULL;
    FILE *voc = NULL;
    FILE *allTFIDF = NULL;
    do {
    
    printf("1.LEITURA DE ARQUIVO\n");
    printf("2.GERACAO DE VOCABULARIO\n");
    printf("3.GERACAO TF-ID \n");
    printf("4.VIZUALIZAR TF-ID \n");
    printf("5.SAIR");
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

                PContadorN1 = numberOfWordsInFile(Nota1);
                PContadorN2 = numberOfWordsInFile(Nota2);
                PContadorN3 = numberOfWordsInFile(Nota3);
                PContadorN4 = numberOfWordsInFile(Nota4);
                PContadorN5 = numberOfWordsInFile(Nota5);

               
                fputs("Vocabulario,Nota1,Nota2,Nota3,Nota4,Nota5\n", allTFIDF);
                while((c = fgetc(voc)) != EOF) {
                    i = 0;
                    nDocWithWord = 0;

          
                    while(!isEndWord(c)) {
                        word[i] = c;
                        c = fgetc(voc);
                        i++;
                    }
                   
                    Contador1 = wordCountInFile(word, Nota1);  
                    Contador2 = wordCountInFile(word, Nota2);  
                    Contador3 = wordCountInFile(word, Nota3);  
                    Contador4 = wordCountInFile(word, Nota4);  
                    Contador5 = wordCountInFile(word, Nota5);

                    if(Contador1)
                        nDocWithWord++;
                    if(Contador2)
                        nDocWithWord++;
                    if(Contador3)
                        nDocWithWord++;
                    if(Contador4)
                        nDocWithWord++;
                    if(Contador5)
                        nDocWithWord++;
                    
                    if(nDocWithWord == 0)
                        nDocWithWord = 1;
                    

                    x = 5.0/nDocWithWord; 
                    IDF = log10(x); 
                    TF1 = Contador1/PContadorN1;
                    TF2 = Contador2/PContadorN2;
                    TF3 = Contador3/PContadorN3;
                    TF4 = Contador4/PContadorN4;
                    TF5 = Contador5/PContadorN5;

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
               
               
                printf("QUAL TF-IDF SERÁ SELECIONADO? ");
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
