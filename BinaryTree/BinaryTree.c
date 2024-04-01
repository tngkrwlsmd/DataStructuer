#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
}bt;

int search(bt* tree, int key);
void inorder(bt* tree);
void insert(bt** tree, int key);
void freeTree(bt* tree);
int inorderCount;

int main(void) {

	bt* tree = NULL;
	int count = 0, key;

	srand((unsigned int)time(NULL));
	while (count < 20) {
		key = rand() % 1000;
		if (key == search(tree, key)) continue;
		else {
			insert(&tree, key);
			count++;
		}
	}

	printf("이진트리 구성\n\n");
	inorder(tree);
	freeTree(tree);

	return 0;
}

int search(bt* tree, int key) {

	if (tree == NULL) return -1;
	else if (key == tree->key) return key;
	else if (key < tree->key) return search(tree->left, key);
	else if (key > tree->key) return search(tree->right, key);
	else return -1;
}

void inorder(bt* tree) {
	if (tree == NULL) return;
	inorder(tree->left);
	printf("%3d ", tree->key);
	inorderCount++;
	if (inorderCount % 10 == 0) printf("\n");
	inorder(tree->right);
}

void insert(bt** tree, int key) {

	bt* temp = NULL, * current = *tree;

	temp = (bt*)malloc(sizeof(bt));
	temp->key = key;
	temp->left = NULL; temp->right = NULL;

	if (*tree == NULL) *tree = temp;
	else if (key < (*tree)->key) insert(&(*tree)->left, key);
	else insert(&(*tree)->right, key);
}

void freeTree(bt* tree) {
	if (tree == NULL) return;
	freeTree(tree->left);
	freeTree(tree->right);
	free(tree);
}