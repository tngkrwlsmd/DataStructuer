#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void constructHeap(int data[], int n);
void heapSort(int data[], int n);

int main(void) {

	int data[20];

	srand((unsigned int)time(NULL));
	printf("정렬 전 배열\n\n");
	for (int i = 0; i < 20; i++) {
		data[i] = rand() % 100;
		printf("%2d ", data[i]);
		if ((i + 1) % 10 == 0) printf("\n");
	}

	heapSort(data, 20);

	printf("\n정렬 후 배열\n\n");
	for (int i = 0; i < 20; i++) {
		printf("%2d ", data[i]);
		if ((i + 1) % 10 == 0) printf("\n");
	}

	return 0;
}

void constructHeap(int data[], int n) {

	int i, j, temp, left, right, imsi;
	for (i = n / 2; i >= 0; i--) {
		temp = data[i]; j = i;
		left = 2 * j + 1; right = 2 * j + 2;
		while (left < n) {
			if (right < n && data[left] < data[right]) imsi = right;
			else imsi = left;
			if (temp < data[imsi]) {
				data[j] = data[imsi]; j = imsi;
				left = 2 * j + 1; right = 2 * j + 2;
			}
			else break;
		}
		data[j] = temp;
	}
}

void heapSort(int data[], int n) {

	int temp, i;
	constructHeap(data, n);
	for (i = n - 1; i > 0; i--) {
		temp = data[0]; data[0] = data[i]; data[i] = temp;
		constructHeap(data, i);
	}
}
