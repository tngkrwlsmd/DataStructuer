#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data, height;
	struct node* left, * right;
}AVL;

void freeTree(AVL* node); //�޸� ����
int height(AVL* node); //���̸� ��ȯ
int maxReturn(int a, int b); //�� �μ� �� ū ���� ��ȯ
AVL* newNode(int data); //���ο� ��带 ����
void updateHeight(AVL* node); //Ʈ���� ���̸� ������Ʈ

//�μ��� ȸ���� �߽��� �Ǵ� ���, ��ȯ���� ��ġ�� ���
AVL* leftRotate(AVL* x);
AVL* rightRotate(AVL* x);

int getBalance(AVL* node); //������ �������� Ȯ���ϴ� �Լ�
AVL* insert(AVL* node, int data);
AVL* delete(AVL* node, int data);
AVL* currentNode(AVL* node); //���� ��带 ��ȯ�ϴ� �Լ�

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
	temp->height = 1; //���ο� ����� ���̴� 1
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
	else return node; //�ߺ�x

	updateHeight(node);
	int balance = getBalance(node); //������ �������� Ȯ��

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

AVL* currentNode(AVL* node) { //������ ��ȯ
	AVL* current = node;
	while (current->left != NULL) current = current->left;
	return current;
}

AVL* delete(AVL* node, int data) {
	if (node == NULL) return node;

	if (data < node->data) node->left = delete(node->left, data);
	else if (data > node->data) node->right = delete(node->right, data);
	else {
		//������ ��带 ã�� ���
		if ((node->left == NULL) || (node->right == NULL)) {
			AVL* temp;
			if (node->left != NULL) temp = node->left;
			else if (node->right != NULL) temp = node->right;
			else temp = NULL;

			if (temp == NULL) { //�ڽ� ��尡 ���� ���
				temp = node;
				node = NULL;
			}
			else *node = *temp; //�ڽ��� �� ���� ��� ���� ����(�ּҰ� �ٲ�� ���� �ƴ�)
			free(temp);
		}
		else { //�ڽ��� �� ���� ���
			AVL* temp = currentNode(node->right); //�����ڸ� ��ü�Ͽ� ������
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