#include <stdio.h>

void vetUnsigned(int *n);

int main(){
    int n[10];
    for(int i = 0; i < 10; i++)
        scanf("%d", &n[i]);
    vetUnsigned(n);
    for(int i = 0; i < 10; i++)
        printf("%d ", n[i]);
}

void vetUnsigned(int *n){
    for(int i = 0; i < 10; i++)
        if(n[i] < 0)
            n[i] *= -1;
}