#include <stdio.h>
#pragma warning(disable : 4996)
#define N 50

//아래 두 함수는 사용하지 않음. 공부 목적으로 제작
void insert_heap(int t[], int* length, int x);
void delete_heap(int t[], int* length);

void construct_heap(int t[], int length, int i);
void sort_heap(int t[], int length);

int main() {
    
    int data[N], length = 0, x, i;
    FILE* f1, * f2;

    f1 = fopen("data.in", "r");
    while (fscanf(f1, "%d", &x) != EOF) {
        data[length] = x; //원래 상태의 배열
        length++;
    }
    fclose(f1);

    printf("정렬 전 배열:"); 
    for (i = 0; i < length; i++) {
        if (i%10 == 0) printf("\n"); //가독성을 위해 한 줄에 10개씩 출력
        printf("%2d ", data[i]);
    }

    printf("\n\n");

    sort_heap(data, length);

    printf("정렬 후 배열:");
    for (i = 0; i < length; i++) {
        if (i%10 == 0) printf("\n"); //가독성을 위해 한 줄에 10개씩 출력
        printf("%2d ", data[i]);
    }

    printf("\n\n");

    f2 = fopen("result.out", "w");
    for (i = 0; i < length; i++) fprintf(f2, "%d\n", data[i]);
    fclose(f2);

    return 0;
}

void insert_heap(int t[], int *length, int x)
{
    int current, parent;
    if (*length == N) return;
    current = *length;
    *length = *length + 1;
    parent = (current - 1) / 2;
    while (t[parent] < x) {
        t[current] = t[parent];
        current = parent;
        parent = (current - 1) / 2;
    }
    t[current] = x;
}

void delete_heap(int t[], int* length)
{
    int current, left, right, maxchild, temp;

    if (*length == 0) return;
    current = 0;
    *length = *length - 1;
    temp = t[*length];

    if (*length ==1) t[current] = temp; 

    left = 2 * current + 1;
    right = 2 * current + 2;
    while (left < *length) {
        if (right < *length && t[left] < t[right]) maxchild = right;
        else maxchild = left;

        if (temp < t[maxchild]) {
            t[current] = t[maxchild];
            current = maxchild;
            left = 2 * current + 1;
            right = 2 * current + 2;
        }
        else break;
    }
    t[current] = temp;
}

void construct_heap(int t[], int length, int i)
{
    int min = i, left, right, temp; //min = 나와 자식 노드 중 작은 값을 가진 노드의 인덱스를 저장하는 변수, 지금은 나 자신으로 초기화
    left = 2 * i + 1;
    right = 2 * i + 2;

    if (left < length && t[left] < t[min]) min = left; //왼쪽 값이 작은 경우
    if (right < length && t[right] < t[min]) min = right; //오른쪽 값이 작은 경우

    if (min != i) { //작은 수가 위로 올라오도록 정렬
        temp = t[i];
        t[i] = t[min];
        t[min] = temp;

        construct_heap(t, length , min); //자식 노드와 값을 바꾸고, 아래로 내려가면서 정렬
    }
}

void sort_heap(int t[], int length)
{
    int temp, i;

    for (i = length / 2 - 1; i >= 0; i--) construct_heap(t, length, i); //힙 구성
	//length/2를 하는 이유는 construct_heap 함수에서 left, right 변수를 사용하기 위함

    for (i = length - 1; i > 0; i--) {
        temp = t[0];
        t[0] = t[i];
        t[i] = temp;
        construct_heap(t, i, 0); //루트 노드와 값을 바꾸고, 아래로 내려가면서 정렬
    }
}