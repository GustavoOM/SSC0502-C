#include <stdio.h>

float newton(float e, float n);

int main(){
    float e, n, raiz;
    scanf("%f %f", &e, &n);
    raiz = newton(e, n);
    printf("%f\n", raiz);
    return 0;
}
float newton(float e, float n){
    float r = e/2;
    for(int i = 1; i < n; i++)
        r = (r + (e/r))/2;
    return r;
}
