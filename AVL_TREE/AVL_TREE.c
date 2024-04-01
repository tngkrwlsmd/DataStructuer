#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data, height;
	struct node* left, * right;
}AVL;

void freeTree(AVL* node); //메모리 해제
int height(AVL* node); //높이를 반환
int maxReturn(int a, int b); //두 인수 중 큰 값을 반환
AVL* newNode(int data); //새로운 노드를 생성
void updateHeight(AVL* node); //트리의 높이를 업데이트

//인수는 회전의 중심이 되는 노드, 반환값은 위치가 상승
AVL* leftRotate(AVL* x);
AVL* rightRotate(AVL* x);

int getBalance(AVL* node); //균형이 깨졌는지 확인하는 함수
AVL* insert(AVL* node, int data);
AVL* delete(AVL* node, int data);
AVL* currentNode(AVL* node); //직전 노드를 반환하는 함수

void inorder(AVL* root);

int main(void) {

	AVL* root = NULL;

	freeTree(root);
	return 0;
}

void freeTree(AVL* node) {
	if (node == NULL) return;
	free(node->left);
	free(node->right);
	free(node);
}

int height(AVL* node) {
	if (node == NULL) return 0;
	return node->height;
}

int maxReturn(int a, int b) {
	if (a > b) return a;
	else return b;
}

AVL* newNode(int data) {
	AVL* temp = (AVL*)malloc(sizeof(AVL));
	temp->data = data;
	temp->left = NULL; temp->right = NULL;
	temp->height = 1; //새로운 노드의 높이는 1
	return temp;
}

void updateHeight(AVL* node) {
	if (node != NULL) {
		node->height = 1 + maxReturn(height(node->left), height(node->right));
	}
	else return;
}

AVL* leftRotate(AVL* x) {
	AVL* y = x->right;
	AVL* z = y->left;

	y->left = x;
	x->right = z;
	updateHeight(x);
	updateHeight(y);

	return y;

}

AVL* rightRotate(AVL* x) {
	AVL* y = x->left;
	AVL* z = y->right;

	y->right = x;
	x->left = z;
	updateHeight(x);
	updateHeight(y);

	return y;
}

int getBalance(AVL* node) {
	if (node == NULL) return 0;
	return height(node->left) - height(node->right);
}

void inorder(AVL* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

AVL* insert(AVL* node, int data) {
	if (node == NULL) return newNode(data);

	if (data < node->data) node->left = insert(node->left, data);
	else if (data > node->data) node->right = insert(node->right, data);
	else return node; //중복x

	updateHeight(node);
	int balance = getBalance(node); //균형이 깨졌는지 확인

	//1. LL case
	if (balance > 1 && data < node->left->data) return rightRotate(node);
	//2. RR case
	if (balance < -1 && data > node->right->data) return leftRotate(node);
	//3. LR case
	if (balance > 1 && data > node->left->data) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	//4. RL case
	if (balance < -1 && data < node->right->data) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	
	return node;
}

AVL* currentNode(AVL* node) { //직후자 반환
	AVL* current = node;
	while (current->left != NULL) current = current->left;
	return current;
}

AVL* delete(AVL* node, int data) {
	if (node == NULL) return node;

	if (data < node->data) node->left = delete(node->left, data);
	else if (data > node->data) node->right = delete(node->right, data);
	else {
		//삭제할 노드를 찾은 경우
		if ((node->left == NULL) || (node->right == NULL)) {
			AVL* temp;
			if (node->left != NULL) temp = node->left;
			else if (node->right != NULL) temp = node->right;
			else temp = NULL;

			if (temp == NULL) { //자식 노드가 없는 경우
				temp = node;
				node = NULL;
			}
			else *node = *temp; //자식이 한 개인 경우 값을 복사(주소가 바뀌는 것이 아님)
			free(temp);
		}
		else { //자식이 두 개인 경우
			AVL* temp = currentNode(node->right); //직후자를 대체하여 삭제함
			node->data = temp->data;
			node->right = delete(node->right, temp->data);
		}
	}

	updateHeight(node);
	int balance = getBalance(node);

	//1. LL case
	if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
	//2. RR case
	if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
	//3. LR case
	if (balance > 1 && getBalance(node->left) < 0) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	//4. RL case
	if (balance < -1 && getBalance(node->right) > 0) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}