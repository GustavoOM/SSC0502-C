#include <stdio.h>
int main(){
    void divisores(int *vet, int n);

    int vet[20]={0}, n;
    scanf("%d",&n);
    divisores(vet, n);
    for(int i = 0; i < 20; i++)
        if(vet[i]!=0)
            printf("%d ", vet[i]);
    printf("\n");
}

void divisores(int *vet, int n){
    int elements = 0;
    for(int i = n/2;i > 0; i--){
        if(elements > 19)
            break;
        if(n%i==0){
            vet[elements] = i;
            elements++;
        }
    }
}