#include <stdio.h>
int main(){
    int vet[5][5], b, s;
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            scanf("%d", &vet[i][j]);
    b = vet[0][0];
    s = vet[0][0];
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            if(vet[i][j] > b)
                b = vet[i][j];
            else if(vet[i][j] < s)
                s = vet[i][j];
    printf("%d %d\n", s, b);
}