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
	fprintf(fp, "정렬 전 배열\n\n");
	for (int i = 0; i < N; i++) {
		data[i] = rand() % 1000;
		fprintf(fp, "%3d ", data[i]);
		if ((i + 1) % 10 == 0) fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
	fclose(fp);

	printf("정렬 전 배열\n\n");
	for (int i = 0; i < N; i++) {
		printf("%3d ", data[i]);
		if ((i + 1) % 15 == 0) printf("\n");
	}

	int key;

	printf("\n\n찾으시려는 데이터를 입력해주세요. : ");
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
	printf("\n\n정렬 후 배열\n\n");

	for (int i = 0; i < N; i++) {
		printf("%3d ", data[i]);
		if ((i + 1) % 15 == 0) printf("\n");
	}
	printf("\n");

	fp = fopen("data.in", "a");
	fprintf(fp, "정렬 후 배열\n\n");
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
			printf("\n찾으시려는 데이터가 존재합니다!\n");
			break;
		}
		else if (i == N - 1) {
			printf("\n데이터가 존재하지 않습니다.\n");
		}
	}

}