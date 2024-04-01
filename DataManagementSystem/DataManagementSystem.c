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
		printf(" 정보 관리 시스템 \n");
		printf("----------------------------------------\n");
		printf(" 1. 검색(Retrieval) ('1')\n");
		printf(" 2. 갱신(update)) ('2')\n");
		printf(" 3. 추가(Insert)('3')\n");
		printf(" 4. 삭제(Delete) ('4')\n");
		printf(" 5. 전체조회(Sort List)('5')\n");
		printf(" 6. 종료(Quit) ('q') \n");
		printf("----------------------------------------\n");
		printf("\n\n 원하시는 서비스를 선택하세요. ");
		ch = getche();
		switch (ch) {
		case '1': system("cls"); {
			printf("학생의 학번, 이름을 입력해주세요.\n\n");
			printf("학번: "); scanf("%d", &key);
			printf("이름: "); scanf("%s", name); printf("\n");
			temp = retrival(tree, key, name);
			if (temp != NULL) {
				printf("해당 학생이 존재합니다.\n\n");
				printf("학번 : %d\n이름 : %s\n주소 : %s\n성적 : %d\n",
					temp->key, temp->name, temp->address, temp->score);
				printf("아무 키를 누르면 처음으로 돌아갑니다.");
				break;
			}
			else {
				printf("존재하지 않는 학생입니다. 아무 키를 누르면 처음으로 돌아갑니다.");
				break;
			}
		}
		case '2': system("cls"); update();
			printf("데이터가 갱신되었습니다. 아무 키를 누르면 처음으로 돌아갑니다.");
			break;
		case '3': system("cls"); {
			printf("학생의 학번, 이름, 주소, 성적을 입력해주세요.\n\n");
			printf("학번: "); scanf("%d", &key);
			printf("이름: "); scanf("%s", name);
			printf("주소: "); scanf("%s", address);
			printf("성적: "); scanf("%d", &score); printf("\n");
			temp = retrival(tree, key, name);
			if (temp != NULL) { //학번이 이미 존재하는 경우는 무시
				if (temp->key == key && !strcmp(temp->name, name)) {
					printf("이미 존재하는 학생입니다. 아무 키를 누르면 처음으로 돌아갑니다.");
					break;
				}
				else { //학번이 없으면서 이름이 존재하는 경우는 없으므로 무시
					insert(&tree, key, name, address, score);
					printf("데이터가 입력되었습니다. 아무 키를 누르면 처음으로 돌아갑니다.");
					break;
				}
			}
			else { //데이터가 존재하지 않음
				insert(&tree, key, name, address, score);
				printf("데이터가 입력되었습니다.아무 키를 누르면 처음으로 돌아갑니다.");
				break;
			}
		}
		case '4': system("cls"); {
			printf("삭제할 학생의 학번과 이름을 입력해주세요.\n\n");
			printf("학번: "); scanf("%d", &key);
			printf("이름: "); scanf("%s", name); printf("\n");
			temp = retrival(tree, key, name);
			if (temp != NULL) {
				delete(&tree, key, name);
				printf("데이터가 삭제되었습니다. 아무 키를 누르면 처음으로 돌아갑니다.");
				break;
			}
			else {
				printf("존재하지 않는 학생입니다. 아무 키를 누르면 처음으로 돌아갑니다.");
				break;
			}
		}
		case '5': system("cls"); {
			retrivelAll(tree);
			dataLoading(tree); printf("\n\n");
			printf("아무 키를 누르면 처음으로 돌아갑니다.");
			break;
		}
		case 'q': system("cls"); quit(f2, tree); fclose(f2); freeTree(tree); return 0;
		default: system("cls");
			printf("\n\n 키를 잘못 입력했습니다.\n");
			printf(" 화면의 설명을 보신 후, ");
			printf("'1'~'4' 또는 'q'를 입력해 주세요 \n\n");
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
		if ((*tree)->parent == NULL) { //루트 노드를 삭제할 경우
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
			else { //두 개의 자식이 있는 경우, 직후자 or 직전자 이용
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
			if ((*tree)->parent->left == *tree) { //부모의 왼쪽 자식이 나일 때
				if ((*tree)->left == NULL && (*tree)->right == NULL) { //자식x
					(*tree)->parent->left = NULL;
					free(*tree);
					*tree = NULL; //t가 이상한 곳을 가리키지 못하도록 초기화
				}
				else if ((*tree)->left == NULL) { //왼쪽 자식x
					temp = *tree;
					(*tree)->parent->left = (*tree)->right;
					(*tree)->right->parent = (*tree)->parent;
					*tree = (*tree)->right;
					free(temp);
				}
				else if ((*tree)->right == NULL) { //오른쪽 자식x
					temp = *tree;
					(*tree)->parent->left = (*tree)->left;
					(*tree)->left->parent = (*tree)->parent;
					*tree = (*tree)->left;
					free(temp);
				}
				else { //두 개의 자식이 있는 경우, 직후자 or 직전자 이용
					temp = (*tree)->right;
					while ((temp->left) != NULL) temp = temp->left;
					(*tree)->key = temp->key;
					strcpy((*tree)->name, temp->name);
					strcpy((*tree)->address, temp->address);
					(*tree)->score = temp->score;
					delete(&temp, key, name);
				}
			}
			else if ((*tree)->parent->right == *tree) { //부모의 오른쪽 자식이 나일 때
				if ((*tree)->left == NULL && (*tree)->right == NULL) {
					(*tree)->parent->right = NULL;
					free(*tree);
					*tree = NULL;
				}
				else if ((*tree)->left == NULL) { //왼쪽 자식x
					temp = *tree;
					(*tree)->parent->right = (*tree)->right;
					(*tree)->right->parent = (*tree)->parent;
					*tree = (*tree)->right;
					free(temp);
				}
				else if ((*tree)->right == NULL) { //오른쪽 자식x
					temp = *tree;
					(*tree)->parent->right = (*tree)->left;
					(*tree)->left->parent = (*tree)->parent;
					*tree = (*tree)->left;
					free(temp);
				}
				else { //두 개의 자식이 있는 경우, 직후자 or 직전자 이용
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
	printf("학번 : %2d 이름 : %3s 주소 : %s 성적 : %d\n", tree->key, tree->name, tree->address, tree->score);
	dataLoading(tree->right);
}

void freeTree(Student* tree) {
	if (tree == NULL) return;
	freeTree(tree->left);
	freeTree(tree->right);
	free(tree);
}