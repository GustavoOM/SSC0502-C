#include <stdio.h>
int main()
{
    int iteraction;
    float number;
    float square;

    scanf("%d %f", &iteraction, &number);

    square = number / 2;

    for (int i = 1; i < iteraction; i++)
    {
        square = (square + (number / square)) / 2;
    }

    printf("%f", square);
}