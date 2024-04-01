#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)
#define N 100

void Search(int data[], int key);

int main() {

	int data[N];
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

	int key;

	printf("\n\nã���÷��� �����͸� �Է����ּ���. : ");
	scanf("%d", &key);
	Search(data, key);

	int temp;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (data[i] < data[j]) {
				temp = data[j];
				data[j] = data[i];
				data[i] = temp;
			}
		}
	}

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
		if (key == data[i]) {
			printf("\nã���÷��� �����Ͱ� �����մϴ�!\n");
			break;
		}
		else if (i == N - 1) {
			printf("\n�����Ͱ� �������� �ʽ��ϴ�.\n");
		}
	}

}