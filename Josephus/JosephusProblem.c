#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20
#pragma warning(disable : 4996)

typedef struct node {
	int num;
	char c[N];
	struct node* after;
	struct node* before;
}list;

void insertList(list** first, char player[]);
list* deleteList(list** first, int num, int* length);
list* searchPlayer(list* first, char player[]);

int main(void) {

	list* first = NULL, * temp, * next; //처음 노드
	int length = 0, gap, del, num, round = 0;
	char c[N], start[N];
	FILE* fp;

	fp = fopen("data.in", "r");
	while (fscanf(fp, "%s ", c) != EOF) {
		insertList(&first, c);
		length++;
	}
	fclose(fp);

	printf("요세푸스 문제 참가자\n\n");
	temp = first;
	for (int i = 0; i < length; i++) {
		printf("%s ", temp->c);
		temp = temp->after;
	}
	printf("\n%d명이 게임에 참가하였습니다.\n", length);
	while (1) {
		printf("\n시작할 플레이어를 골라주세요: ");
		scanf("%s", start);
		temp = searchPlayer(first, start);
		if (!strcmp(start, temp->c)) {
			printf("시작은 %s부터고, 번호는 %d번입니다.\n", start, temp->num);
			break;
		}
		else {
			printf("잘못된 입력입니다. 다시 입력하세요.\n");
			while (getchar() != '\n'); //버퍼를 비움
		}
	}

	while (1) {
		printf("\n갭(m)을 입력해주세요: ");
		scanf("%d", &gap);
		if (gap > 0) {
			printf("%d(m-1)번째까지 순서를 건너뛰고, 마지막 %d(m)번째 위치한 플레이어가 제거됩니다.\n", gap - 1, gap);
			break;

		}
		else {
			printf("잘못된 입력입니다. 다시 입력하세요.\n");
			while (getchar() != '\n');
		}
	}
	printf("\n그러면 게임을 시작합니다.\n");

	next = temp; //시작 위치

	while (length != 1) {

		for (int i = 0; i < gap; i++) { next = next->after; }

		if (round == 0) del = next->num;
		else del = next->before->num; //next가 다음 노드를 연결하므로, 이미 이동한 한 칸을 뺌

		temp = deleteList(&first, del, &length);
		num = temp->num; strcpy(c, temp->c);
		next = temp->after; //다음 노드
		round++;
		free(temp);
		printf("\n%s(n=%d)가 제거되었습니다. 아래는 남은 인원입니다.\n", c, num);
		temp = first;
		for (int i = 0; i < length; i++) {
			printf("%s ", temp->c);
			temp = temp->after;
		}
		printf("\n");
	}

	printf("\n최종 승리자는 %s(n=%d)입니다!!\n", first->c, first->num);

	return 0;
}

void insertList(list** first, char player[]) {
	list* temp, * current;
	int count = 1;

	temp = (list*)malloc(sizeof(list));
	temp->num = 0;
	strcpy(temp->c, player);
	temp->after = NULL;
	temp->before = NULL;

	current = *first; //직전노드

	if (*first == NULL) {
		*first = temp; //첫 노드의 경우, 자기 자신을 가리키도록 포인터를 설정
		temp->num = count;
		temp->after = *first;
		temp->before = *first;
	}
	else {
		while (current->after != *first) {
			count++;
			current = current->after;
		}
		count++;
		temp->num = count;
		current->after = temp;
		temp->before = current;
		temp->after = *first;
		(*first)->before = temp;
	}
}

list* deleteList(list** first, int num, int* length) {
	list* temp = NULL, * current = *first;

	if ((*first)->num == num) { //첫 노드
		temp = *first;
		temp->before->after = temp->after;
		temp->after->before = (*first)->before;
		*first = temp->after;
		*length = *length - 1;

	}
	else if ((*first)->before->num == num) { //마지막 노드
		temp = (*first)->before;
		(*first)->before = temp->before;
		temp->before->after = *first;
		*length = *length - 1;
	}
	else {
		while (current->num != num) {
			current = current->after;
		}
		temp = current;
		temp->after->before = temp->before;
		temp->before->after = temp->after;
		*length = *length - 1;
	}
	return temp;
}

list* searchPlayer(list* first, char player[]) {
	list* current;
	current = first;
	if (!strcmp(first->c, player)) return first; //첫번째 노드
	else if (!strcmp(first->before->c, player)) return first->before; //마지막 노드
	//첫번째 노드와 마지막 노드를 탐색할 수 없음
	while (current->after != first) {
		if (!strcmp(current->c, player)) return current;
		current = current->after;
	}
	return;
}