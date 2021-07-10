#include <stdio.h>
int main(){
    float e, n, raiz;
    scanf("%f %f", &e, &n);
    raiz = e/2;
    for(int i = 1; i < n; i++)
        raiz = (raiz + (e/raiz))/2;
    printf("%f\n", raiz);
    return 0;
}
