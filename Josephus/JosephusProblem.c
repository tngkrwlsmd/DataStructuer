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

	list* first = NULL, * temp, * next; //ó�� ���
	int length = 0, gap, del, num, round = 0;
	char c[N], start[N];
	FILE* fp;

	fp = fopen("data.in", "r");
	while (fscanf(fp, "%s ", c) != EOF) {
		insertList(&first, c);
		length++;
	}
	fclose(fp);

	printf("�似Ǫ�� ���� ������\n\n");
	temp = first;
	for (int i = 0; i < length; i++) {
		printf("%s ", temp->c);
		temp = temp->after;
	}
	printf("\n%d���� ���ӿ� �����Ͽ����ϴ�.\n", length);
	while (1) {
		printf("\n������ �÷��̾ ����ּ���: ");
		scanf("%s", start);
		temp = searchPlayer(first, start);
		if (!strcmp(start, temp->c)) {
			printf("������ %s���Ͱ�, ��ȣ�� %d���Դϴ�.\n", start, temp->num);
			break;
		}
		else {
			printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
			while (getchar() != '\n'); //���۸� ���
		}
	}

	while (1) {
		printf("\n��(m)�� �Է����ּ���: ");
		scanf("%d", &gap);
		if (gap > 0) {
			printf("%d(m-1)��°���� ������ �ǳʶٰ�, ������ %d(m)��° ��ġ�� �÷��̾ ���ŵ˴ϴ�.\n", gap - 1, gap);
			break;

		}
		else {
			printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
			while (getchar() != '\n');
		}
	}
	printf("\n�׷��� ������ �����մϴ�.\n");

	next = temp; //���� ��ġ

	while (length != 1) {

		for (int i = 0; i < gap; i++) { next = next->after; }

		if (round == 0) del = next->num;
		else del = next->before->num; //next�� ���� ��带 �����ϹǷ�, �̹� �̵��� �� ĭ�� ��

		temp = deleteList(&first, del, &length);
		num = temp->num; strcpy(c, temp->c);
		next = temp->after; //���� ���
		round++;
		free(temp);
		printf("\n%s(n=%d)�� ���ŵǾ����ϴ�. �Ʒ��� ���� �ο��Դϴ�.\n", c, num);
		temp = first;
		for (int i = 0; i < length; i++) {
			printf("%s ", temp->c);
			temp = temp->after;
		}
		printf("\n");
	}

	printf("\n���� �¸��ڴ� %s(n=%d)�Դϴ�!!\n", first->c, first->num);

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

	current = *first; //�������

	if (*first == NULL) {
		*first = temp; //ù ����� ���, �ڱ� �ڽ��� ����Ű���� �����͸� ����
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

	if ((*first)->num == num) { //ù ���
		temp = *first;
		temp->before->after = temp->after;
		temp->after->before = (*first)->before;
		*first = temp->after;
		*length = *length - 1;

	}
	else if ((*first)->before->num == num) { //������ ���
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
	if (!strcmp(first->c, player)) return first; //ù��° ���
	else if (!strcmp(first->before->c, player)) return first->before; //������ ���
	//ù��° ���� ������ ��带 Ž���� �� ����
	while (current->after != first) {
		if (!strcmp(current->c, player)) return current;
		current = current->after;
	}
	return;
}