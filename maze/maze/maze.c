#include <stdio.h>
#pragma warning(disable : 4996)
#define MAX 100
#define ROW 11
#define COL 15

int maze[ROW + 2][COL + 2]; //+2�� �ϴ� ������ �̷��� ���κ��� ǥ���ϱ� ����
int mark[ROW + 2][COL + 2]; //������ ���� 1�� �ʱ�ȭ

int move[8][2] = { //�ð���� ������ �̵�
	{-1, 0},{-1, 1}, //��, �ϵ�
	{0, 1}, {1, 1}, //��, ���� 
	{1, 0}, {1, -1}, //��, ����
	{0, -1}, {1, -1} }; //��, �ϼ�

typedef struct {
	int row; //��
	int col; //��
	int dir; //���� ����
}vertexType;

vertexType stack[MAX];
int top;

vertexType pop();
void push(vertexType s);
void path(void);

int main() {

	FILE* fp;

	fp = fopen("maze.data", "r");
	for (int i = 0; i < ROW + 2; i++) {
		for (int j = 0; j < COL + 2; j++) {
			fscanf(fp, "%d", &maze[i][j]);
		}
	}

	path();
	return 0;
}

vertexType pop() {
	return stack[top--];
}

void push(vertexType s) {
	stack[++top] = s;
}

void path(void) {
	int row, col, next_row, next_col, dir, found = 0;
	vertexType position;
	mark[1][1] = 1; //�̷� ����, �ⱸ�� mark[ROW + 1][COL + 1]��
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 0;
	while (top > -1 && found == 0) {
		position = pop(); //���� ��ġ
		row = position.row; col = position.col; dir = position.dir;
		while (dir < 8 && found == 0) {
			next_row = row + move[dir][0];
			next_col = col + move[dir][1];
			if (next_row == ROW + 1 && next_col == COL + 1) {
				found = 1;
			}
			else if (maze[next_row][next_col] == 0 && mark[next_row][next_col] == 0) { //�湮���� ���� ��
				mark[next_row][next_col] = 1;
				position.row = row; position.col = col; position.dir = ++dir;
				push(position);
				row = next_row; col = next_col; dir = 0;
			}
			else ++dir;
		}
	}

	int k;

	if (found == 1) {
		printf("������ �湮�� ����\n\n");
		for (k = 0; k <= top; k++) {
			printf("%2d ��° : %2d �� %2d ��\n", k + 1, stack[k].row, stack[k].col);
		}
		printf("%2d ��° : %2d �� %2d ��(���� �ⱸ)\n", k + 1, row, col);
	}
	else {
		printf("�Ա����� �ⱸ���� ��ΰ� ����\n");
	}
}