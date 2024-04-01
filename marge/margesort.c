#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)
#define N 50

void insertionSort(int x[], int n, int m); //삽입 정렬
void margeTwo(int L1[], int L2[], int L[], int m1, int m2);

int main() {

	int data1[N], data2[N], sorted[2 * N];
	FILE* fp;

	srand(time(NULL));

	fp = fopen("data.in", "w");
	fprintf(fp, "정렬 전 배열1\n\n");
	for (int i = 0; i < N; i++) {
		data1[i] = rand() % 1000;
		fprintf(fp, "%3d ", data1[i]);
		if ((i + 1) % 10 == 0) fprintf(fp, "\n");
	}
	fprintf(fp, "\n");

	fprintf(fp, "정렬 전 배열2\n\n");
	for (int i = 0; i < N; i++) {
		data2[i] = rand() % 1000;
		fprintf(fp, "%3d ", data2[i]);
		if ((i + 1) % 10 == 0) fprintf(fp, "\n");
	}
	fprintf(fp, "\n");

	fclose(fp);

	printf("정렬 전 배열1\n\n");
	for (int i = 0; i < N; i++) {
		printf("%3d ", data1[i]);
		if ((i + 1) % 10 == 0) printf("\n");
	}

	printf("\n");

	printf("정렬 전 배열2\n\n");
	for (int i = 0; i < N; i++) {
		printf("%3d ", data2[i]);
		if ((i + 1) % 10 == 0) printf("\n");
	}

	insertionSort(data1, N, 0);
	insertionSort(data2, N, 0);
	margeTwo(data1, data2, sorted, N, N);

	printf("\n============================================================");
	printf("\n\n정렬 후 배열\n\n");

	for (int i = 0; i < 2 * N; i++) {
		printf("%3d ", sorted[i]);
		if ((i + 1) % 10 == 0) printf("\n");
	}
	printf("\n");

	fp = fopen("data.in", "a");
	fprintf(fp, "정렬 후 배열\n\n");
	for (int i = 0; i < 2 * N; i++) {
		fprintf(fp, "%3d ", sorted[i]);
		if ((i + 1) % 10 == 0) fprintf(fp, "\n");
	}
	fclose(fp);

	return 0;
}

void insertionSort(int x[], int n, int m) {

	int i, j, value;

	for (i = m; i < n; i++) {
		value = x[i]; j = i;
		while ((j > 0) && (x[j - 1] > value)) {
			x[j] = x[j - 1]; j--;
		}
		x[j] = value;
	}
}

void margeTwo(int L1[], int L2[], int L[], int m1, int m2) {

	int i, j, k, p;
	i = j = k = 0;

	while ((i >= 0 && i < m1) && (j >= 0 && j < m2)) {
		if (L1[i] <= L2[j]) L[k++] = L1[i++];
		else L[k++] = L2[j++];
	}
	if (i >= m1) {
		for (p = j; p < m2; p++) L[k++] = L2[p];
	}
	else {
		for (p = i; p < m1; p++) L[k++] = L1[p];
	}
}