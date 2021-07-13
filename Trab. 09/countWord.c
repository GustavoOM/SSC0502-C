#include <stdio.h>
#include <string.h>

int xContemY (char x[], char y[]);
int countChars(char word[]);

int main(){
    FILE *arq;
    char palavra[500], fraseLida[500];

    if((arq=fopen("arquivo.txt","r+"))==NULL)
        return 0;
    
    char auxEspaco[500] = " ";
    char auxLinha[500];
    while (!feof(arq)){
        fgets(auxLinha, 499, arq);
        auxLinha[strcspn(auxLinha, "\n")] = 0;
        strcat(auxEspaco, auxLinha);
        strcpy(fraseLida,auxEspaco);
        strcat(fraseLida, " ");
        strcat(auxEspaco, " ");
    }

    setbuf(stdin, 0);
    fgets(palavra,499,stdin);
    palavra[strcspn(palavra, "\n")] = 0;

    printf("%d\n",(xContemY(fraseLida,palavra)));

    fclose(arq);
    return 0;
}

int countChars(char word[]){
    int count = 0;
    while(1){
        if(word[count] == '\0')
            return count;
        count++;
    }
}

int xContemY (char x[], char y[]){
    int contWords = 0;
    for(int i = 0; i <= countChars(x)-countChars(y);i++){
        for(int j = 0; j <= countChars(y); j++){
            if(y[j] == '\0'){
                if(x[i-1] == ' ' && x[i+j] == ' '){
                    contWords++;
                }
            }
            if(y[j] != x[i+j])
                break;
        }
    }
    return contWords;
}