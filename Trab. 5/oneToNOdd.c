#include <stdio.h>

int isOdd(int n);

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 2; i <= n; i++)
        if(isOdd(i) == 1)
            printf("%d ",i);
}

int isOdd(int n){
    if(n == 1)
        return 0;
    if(n == 2)
        return 1;
    for(int i = 2; i <= n/2; i++)
        if(n%i==0)
            return 0;
    return 1;
}