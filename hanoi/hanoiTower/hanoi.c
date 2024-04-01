#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)
#define N 100
#define NAME 10

typedef struct {
    int n; //���� ����
    char start[NAME]; //��������
    char end[NAME]; //��������
    char temp[NAME]; //�ӽ�����
    char ra; //��� ���� ��ġ
}pole;

int count;
void hanoitower(int n, char start[], char end[], char temp[]);

int main(void) {

    int n;
    char start[] = "start", end[] = "end", temp[] = "temp";

    printf("���� ���� �Է�: ");
    scanf("%d", &n);
    printf("\n");
    hanoitower(n, start, end, temp);
    printf("�ű� Ƚ�� : %d", count);

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

b:  printf("%d-�����̵� : %s -> %s\n", Stack[top].n, Stack[top].start, Stack[top].end);
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
