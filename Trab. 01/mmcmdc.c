#include <stdio.h>
int main(){
    int n1, n2, n3, mmc, mdc, maior, menor;
    scanf("%d %d %d", &n1, &n2, &n3);
    
    if(n1 <= n2 && n1 <= n3)
        menor = n1;
    else if(n2 <= n1 && n2 <= n3)
        menor = n2;
    else if(n3 <= n1 && n3 <= n2)
        menor = n3;
    
    if(n1 >= n2 && n1 >= n3)
        maior = n1;
    else if(n2 >= n1 && n2 >= n3)
        maior = n2;
    else if(n3 >= n1 && n3 >= n2)
        maior = n3;
    
    for(int i = 1; i <= menor; i++)
        if((n1 % i == 0) && (n2 % i == 0) && (n3 % i == 0))
            mdc = i;

    for(int i = n1*n2*n3; i >= maior; i--)
        if((i % n1 == 0) && (i % n2 == 0) && (i % n3 == 0))
            mmc = i;

    printf("%d %d\n", mmc, mdc);
    return 0;
}