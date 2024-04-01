#include <stdio.h>

int factorial(int n);

int main(void) {
    int n, result;

    printf("n!: ");
    scanf("%d", &n);
    result = factorial(n);
    printf("%d", result);
}

int factorial(int n) {

    if (n == 1) {
        return 1;
    }
    else return n * factorial(n-1);
}
