#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)
#define N 100
#define NAME 10

typedef struct {
    int n; //원반 개수
    char start[NAME]; //시작폴대
    char end[NAME]; //도착폴대
    char temp[NAME]; //임시폴대
    char ra; //명령 시작 위치
}pole;

int count;
void hanoitower(int n, char start[], char end[], char temp[]);

int main(void) {

    int n;
    char start[] = "start", end[] = "end", temp[] = "temp";

    printf("원반 개수 입력: ");
    scanf("%d", &n);
    printf("\n");
    hanoitower(n, start, end, temp);
    printf("옮긴 횟수 : %d", count);

    return 0;

}

void hanoitower(int n, char start[], char end[], char temp[]) {

    int top = 0;
    char rAddress, imsi[NAME];
    pole Stack[N];

a:  if (n > 0) {
        Stack[top].n = n;
        strcpy(Stack[top].start, start);
        strcpy(Stack[top].end, end);
        strcpy(Stack[top].temp, temp);
        Stack[top].ra = 'b';
        top++;
        n--;
        strcpy(imsi, end); strcpy(end, temp); strcpy(temp, imsi);
        goto a;
    }

b:  printf("%d-원반이동 : %s -> %s\n", Stack[top].n, Stack[top].start, Stack[top].end);
    top++;
    Stack[top].n = n;
    strcpy(Stack[top].start, start);
    strcpy(Stack[top].end, end);
    strcpy(Stack[top].temp, temp);
    Stack[top].ra = 'c';
    n--;
    strcpy(imsi, start); strcpy(start, temp); strcpy(temp, imsi);
    goto a;

c:  if (top != -1) {
        n = Stack[top].n;
        strcpy(start, Stack[top].start);
        strcpy(end, Stack[top].end);
        strcpy(temp, Stack[top].temp);
        rAddress = Stack[top].ra;
        top--;
        switch (rAddress) {
            case 'b': goto b;
            case 'c': goto c;
        }
    }
}
