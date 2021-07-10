#include <stdio.h>
#include <stdlib.h>
int main(){
    void multiply(int n, int* v);
    int n, *vet;
    scanf("%d",&n);
    vet = (int*) calloc(n, sizeof(int));
    multiply(n, vet);
    for(int i = 0; i < n; i++){
        printf("%d ", vet[i]);
    }
    free(vet);
}

void multiply(int n, int* v){
    for(int i = 1; i <= n; i++)
        v[i-1] = n * i;
}