#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#pragma warning(disable : 4996)

typedef struct node {
	int key;
	char name[20];
	char address[50];
	int score;
	struct node* parent;
	struct node* left;
	struct node* right;
}Student;

Student* current = NULL;
Student* retrival(Student* tree, int key, char name[]);
void update(void);
void insert(Student** tree, int key, char name[], char address[], int score);
void delete(Student** tree, int key, char name[]);
void retrivelAll(Student* tree);
void quit(FILE* fp, Student* tree);
void dataLoading(Student* tree);
void freeTree(Student* tree);

int main(void) {

	int key, score, length = 0;
	char ch, name[20], address[50];
	Student* tree = NULL, * temp;
	FILE* f1, * f2;

	f1 = fopen("student-1.dat", "r");
	f2 = fopen("student-2.dat", "w");
	while (fscanf(f1, "%d %s %s %d", &key, name, address, &score) != EOF) {
		insert(&tree, key, name, address, score);
		length++;
	}
	fclose(f1);

	dataLoading(tree);
	do {
		system("cls");
		printf("\n----------------------------------------\n");
		printf(" ���� ���� �ý��� \n");
		printf("----------------------------------------\n");
		printf(" 1. �˻�(Retrieval) ('1')\n");
		printf(" 2. ����(update)) ('2')\n");
		printf(" 3. �߰�(Insert)('3')\n");
		printf(" 4. ����(Delete) ('4')\n");
		printf(" 5. ��ü��ȸ(Sort List)('5')\n");
		printf(" 6. ����(Quit) ('q') \n");
		printf("----------------------------------------\n");
		printf("\n\n ���Ͻô� ���񽺸� �����ϼ���. ");
		ch = getche();
		switch (ch) {
		case '1': system("cls"); {
			printf("�л��� �й�, �̸��� �Է����ּ���.\n\n");
			printf("�й�: "); scanf("%d", &key);
			printf("�̸�: "); scanf("%s", name); printf("\n");
			temp = retrival(tree, key, name);
			if (temp != NULL) {
				printf("�ش� �л��� �����մϴ�.\n\n");
				printf("�й� : %d\n�̸� : %s\n�ּ� : %s\n���� : %d\n",
					temp->key, temp->name, temp->address, temp->score);
				printf("�ƹ� Ű�� ������ ó������ ���ư��ϴ�.");
				break;
			}
			else {
				printf("�������� �ʴ� �л��Դϴ�. �ƹ� Ű�� ������ ó������ ���ư��ϴ�.");
				break;
			}
		}
		case '2': system("cls"); update();
			printf("�����Ͱ� ���ŵǾ����ϴ�. �ƹ� Ű�� ������ ó������ ���ư��ϴ�.");
			break;
		case '3': system("cls"); {
			printf("�л��� �й�, �̸�, �ּ�, ������ �Է����ּ���.\n\n");
			printf("�й�: "); scanf("%d", &key);
			printf("�̸�: "); scanf("%s", name);
			printf("�ּ�: "); scanf("%s", address);
			printf("����: "); scanf("%d", &score); printf("\n");
			temp = retrival(tree, key, name);
			if (temp != NULL) { //�й��� �̹� �����ϴ� ���� ����
				if (temp->key == key && !strcmp(temp->name, name)) {
					printf("�̹� �����ϴ� �л��Դϴ�. �ƹ� Ű�� ������ ó������ ���ư��ϴ�.");
					break;
				}
				else { //�й��� �����鼭 �̸��� �����ϴ� ���� �����Ƿ� ����
					insert(&tree, key, name, address, score);
					printf("�����Ͱ� �ԷµǾ����ϴ�. �ƹ� Ű�� ������ ó������ ���ư��ϴ�.");
					break;
				}
			}
			else { //�����Ͱ� �������� ����
				insert(&tree, key, name, address, score);
				printf("�����Ͱ� �ԷµǾ����ϴ�.�ƹ� Ű�� ������ ó������ ���ư��ϴ�.");
				break;
			}
		}
		case '4': system("cls"); {
			printf("������ �л��� �й��� �̸��� �Է����ּ���.\n\n");
			printf("�й�: "); scanf("%d", &key);
			printf("�̸�: "); scanf("%s", name); printf("\n");
			temp = retrival(tree, key, name);
			if (temp != NULL) {
				delete(&tree, key, name);
				printf("�����Ͱ� �����Ǿ����ϴ�. �ƹ� Ű�� ������ ó������ ���ư��ϴ�.");
				break;
			}
			else {
				printf("�������� �ʴ� �л��Դϴ�. �ƹ� Ű�� ������ ó������ ���ư��ϴ�.");
				break;
			}
		}
		case '5': system("cls"); {
			retrivelAll(tree);
			dataLoading(tree); printf("\n\n");
			printf("�ƹ� Ű�� ������ ó������ ���ư��ϴ�.");
			break;
		}
		case 'q': system("cls"); quit(f2, tree); fclose(f2); freeTree(tree); return 0;
		default: system("cls");
			printf("\n\n Ű�� �߸� �Է��߽��ϴ�.\n");
			printf(" ȭ���� ������ ���� ��, ");
			printf("'1'~'4' �Ǵ� 'q'�� �Է��� �ּ��� \n\n");
		}
		getche();
	} while (ch != 'q');

	return 0;
}

Student* retrival(Student* tree, int key, char name[]) {
	if (tree == NULL) return NULL;
	else if (tree->key = key && !strcmp(tree->name, name)) return tree;
	else if (key < tree->key) return retrival(tree->left, key, name);
	else if (key > tree->key) return retrival(tree->right, key, name);
	else return NULL;
}

void update(void) {

}

void insert(Student** tree, int key, char name[], char address[], int score) {

	Student* temp = NULL, * current = NULL;

	temp = (Student*)malloc(sizeof(Student));
	temp->key = key; temp->score = score;
	strcpy(temp->name, name); strcpy(temp->address, address);
	temp->parent = NULL; temp->left = NULL; temp->right = NULL;

	if (*tree == NULL) {
		*tree = temp;
		if (current != NULL) (*tree)->parent = current;
	}
	else if (key < (*tree)->key) {
		current = *tree;
		insert(&(*tree)->left, key, name, address, score);
	}
	else {
		current = *tree;
		insert(&(*tree)->right, key, name, address, score);
	}
}

void delete(Student** tree, int key, char name[]) {
	Student* temp;
	if (*tree == NULL) return;
	else if (key < (*tree)->key) delete(&(*tree)->left, key, name);
	else if (key > (*tree)->key) delete(&(*tree)->right, key, name);
	else {
		if ((*tree)->parent == NULL) { //��Ʈ ��带 ������ ���
			if ((*tree)->left == NULL && (*tree)->right == NULL) {
				free(*tree);
				*tree = NULL;
			}
			else if ((*tree)->left == NULL) {
				temp = *tree;
				(*tree)->right->parent = NULL;
				*tree = (*tree)->right;
				free(temp);
			}
			else if ((*tree)->right == NULL) {
				temp = *tree;
				(*tree)->left->parent = NULL;
				*tree = (*tree)->left;
				free(temp);
			}
			else { //�� ���� �ڽ��� �ִ� ���, ������ or ������ �̿�
				temp = (*tree)->right;
				while (temp->left != NULL) temp = temp->left;
				(*tree)->key = temp->key;
				strcpy((*tree)->name, temp->name);
				strcpy((*tree)->address, temp->address);
				(*tree)->score = temp->score;
				delete(&temp, key, name);
			}
		}
		else {
			if ((*tree)->parent->left == *tree) { //�θ��� ���� �ڽ��� ���� ��
				if ((*tree)->left == NULL && (*tree)->right == NULL) { //�ڽ�x
					(*tree)->parent->left = NULL;
					free(*tree);
					*tree = NULL; //t�� �̻��� ���� ����Ű�� ���ϵ��� �ʱ�ȭ
				}
				else if ((*tree)->left == NULL) { //���� �ڽ�x
					temp = *tree;
					(*tree)->parent->left = (*tree)->right;
					(*tree)->right->parent = (*tree)->parent;
					*tree = (*tree)->right;
					free(temp);
				}
				else if ((*tree)->right == NULL) { //������ �ڽ�x
					temp = *tree;
					(*tree)->parent->left = (*tree)->left;
					(*tree)->left->parent = (*tree)->parent;
					*tree = (*tree)->left;
					free(temp);
				}
				else { //�� ���� �ڽ��� �ִ� ���, ������ or ������ �̿�
					temp = (*tree)->right;
					while ((temp->left) != NULL) temp = temp->left;
					(*tree)->key = temp->key;
					strcpy((*tree)->name, temp->name);
					strcpy((*tree)->address, temp->address);
					(*tree)->score = temp->score;
					delete(&temp, key, name);
				}
			}
			else if ((*tree)->parent->right == *tree) { //�θ��� ������ �ڽ��� ���� ��
				if ((*tree)->left == NULL && (*tree)->right == NULL) {
					(*tree)->parent->right = NULL;
					free(*tree);
					*tree = NULL;
				}
				else if ((*tree)->left == NULL) { //���� �ڽ�x
					temp = *tree;
					(*tree)->parent->right = (*tree)->right;
					(*tree)->right->parent = (*tree)->parent;
					*tree = (*tree)->right;
					free(temp);
				}
				else if ((*tree)->right == NULL) { //������ �ڽ�x
					temp = *tree;
					(*tree)->parent->right = (*tree)->left;
					(*tree)->left->parent = (*tree)->parent;
					*tree = (*tree)->left;
					free(temp);
				}
				else { //�� ���� �ڽ��� �ִ� ���, ������ or ������ �̿�
					temp = (*tree)->right;
					while ((temp->left) != NULL) temp = temp->left;
					(*tree)->key = temp->key;
					strcpy((*tree)->name, temp->name);
					strcpy((*tree)->address, temp->address);
					(*tree)->score = temp->score;
					delete(&temp, key, name);
				}
			}
		}
	}
}

void retrivelAll(Student* tree) {

}

void quit(FILE* fp, Student* tree) {
	if (tree == NULL) return;
	quit(fp, tree->left);
	fprintf(fp, "%d %s %s %d\n", tree->key, tree->name, tree->address, tree->score);
	quit(fp, tree->right);
}

void dataLoading(Student* tree) {
	if (tree == NULL) return;
	dataLoading(tree->left);
	printf("�й� : %2d �̸� : %3s �ּ� : %s ���� : %d\n", tree->key, tree->name, tree->address, tree->score);
	dataLoading(tree->right);
}

void freeTree(Student* tree) {
	if (tree == NULL) return;
	freeTree(tree->left);
	freeTree(tree->right);
	free(tree);
}