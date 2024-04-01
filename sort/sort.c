#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)
#define N 100

void Search(int data[], int key); //���� Ž��
int BinarySearch(int x[], int left, int right, int key); //���� Ž��
void exchangeSort(int x[], int n); //��ȯ ����
void selectionSort(int x[], int n); //���� ����
void insertionSort(int x[], int n, int m); //���� ����
void shellSort(int x[], int n); //�� ����
void quickSort(int x[], int left, int right); //�� ����
int partitionList1(int x[], int left, int right); //����� ����
int partitionList2(int x[], int left, int right); //�ܹ��� ����

int count, search1, search2; //����,�� Ƚ��, Ž�� �� Ƚ��

int main() {

	int data[N], left = 0, right = N - 1;
	FILE* fp;

	srand(time(NULL));

	fp = fopen("data.in", "w");
	fprintf(fp, "���� �� �迭\n\n");
	for (int i = 0; i < N; i++) {
		data[i] = rand() % 1000;
		fprintf(fp, "%3d ", data[i]);
		if ((i + 1) % 10 == 0) fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
	fclose(fp);

	printf("���� �� �迭\n\n");
	for (int i = 0; i < N; i++) {
		printf("%3d ", data[i]);
		if ((i + 1) % 15 == 0) printf("\n");
	}

	quickSort(data, left, right);

	printf("\n============================================================");
	printf("\n\n���� �� �迭\n\n");

	for (int i = 0; i < N; i++) {
		printf("%3d ", data[i]);
		if ((i + 1) % 15 == 0) printf("\n");
	}
	printf("\n");

	fp = fopen("data.in", "a");
	fprintf(fp, "���� �� �迭\n\n");
	for (int i = 0; i < N; i++) {
		fprintf(fp, "%3d ", data[i]);
		if ((i + 1) % 10 == 0) fprintf(fp, "\n");
	}
	fclose(fp);

	return 0;
}

void Search(int data[], int key) {

	for (int i = 0; i < N; i++) {
		search1++;
		if (key == data[i]) {
			printf("ã���÷��� �����Ͱ� �����մϴ�!\n");
			break;
		}
		else if (i == N - 1) {
			printf("�����Ͱ� �������� �ʽ��ϴ�.\n");
		}
	}

}

void exchangeSort(int x[], int n) {
	int i, j, temp;

	for (i = n - 1; i > 0; i--) { //���������� ���ʷ�
		for (j = 0; j <= i; j++) {
			if (x[j] > x[j + 1]) {
				temp = x[j]; x[j] = x[j + 1]; x[j + 1] = temp;
			}
		}
	}
}

void selectionSort(int x[], int n) {

	int i, j, min, temp;

	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++) { //���õ� ��ġ���� �ϳ� �� ū ��ġ���� Ž��
			if (x[j] < x[min]) {
				min = j;
				temp = x[i]; x[i] = x[min]; x[min] = temp;
			}
		}
	}
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

int BinarySearch(int x[], int left, int right, int key) {

	int middle;

	if (left <= right) {
		search2++;
		middle = (left + right) / 2;
		if (x[middle] == key) return middle;
		else if (key > x[middle]) return BinarySearch(x, middle + 1, right, key);
		else return BinarySearch(x, left, middle - 1, key);
	}
	return -1;
}

void shellSort(int x[], int n) {

	int i, j, value, h = 1;

	while (h < n) h = 3 * h + 1;

	for (h = h / 3; h > 0; h = h / 3) {
		for (i = h; i < n; i++) {
			value = x[i]; j = i;
			while ((j - h >= 0) && (x[j - h] > value)) {
				x[j] = x[j - h]; j = j - h;
			}
			x[j] = value;
		}
	}
}

void quickSort(int x[], int left, int right) {

	int middle;

	if (left < right) {
		middle = partitionList1(x, left, right);
		//middle = partitionList2(x, left, right);
		// �κ� ����Ʈ�� ũ�Ⱑ 20���� ���� ��� ���� ����
		if (middle - left < 20 && right - middle < 20) {
			insertionSort(x, middle, left);
			insertionSort(x, right + 1, middle);
		}
		else if (middle - left < 20) {
			insertionSort(x, middle, left);
			quickSort(x, middle + 1, right);
		}
		else if (right - middle < 20) {
			//���� ���� ��, n�� �迭�� ũ�⸦ ����
			//��� right + 1 (right�� �迭�� ������ �ε�����)
			insertionSort(x, right + 1, middle);
			quickSort(x, left, middle - 1);
		}
		else {
			quickSort(x, left, middle - 1);
			quickSort(x, middle + 1, right);
		}
	}
}

int partitionList1(int x[], int left, int right) { //�瓇�� ����Ʈ ����
	int p, l, r, temp;

	p = x[left];
	l = left + 1; r = right;
	while (l <= r) {
		while (l <= right && x[l] <= p) l++;
		while (r > left && x[r] >= p) r--;
		if (l < r) {
			temp = x[l]; x[l] = x[r]; x[r] = temp;
		}
	}
	x[left] = x[r]; x[r] = p;
	return r;
}

int partitionList2(int x[], int left, int right) {

	int p, i, j, temp;

	p = x[left]; j = left;
	for (i = left + 1; i <= right; i++) {
		if (x[i] < p) {
			j++;
			temp = x[i]; x[i] = x[j]; x[j] = temp;
		}
	}
	x[left] = x[j]; x[j] = p;
	return j;
}