#include <stdio.h>
#pragma warning(disable : 4996)
#define MAX 100
#define ROW 11
#define COL 15

int maze[ROW + 2][COL + 2]; //+2를 하는 이유는 미로의 경계부분을 표시하기 위함
int mark[ROW + 2][COL + 2]; //지나간 길은 1로 초기화

int move[8][2] = { //시계방향 순으로 이동
	{-1, 0},{-1, 1}, //북, 북동
	{0, 1}, {1, 1}, //동, 남동 
	{1, 0}, {1, -1}, //남, 남서
	{0, -1}, {1, -1} }; //서, 북서

typedef struct {
	int row; //행
	int col; //열
	int dir; //다음 방향
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
	mark[1][1] = 1; //미로 시작, 출구는 mark[ROW + 1][COL + 1]임
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 0;
	while (top > -1 && found == 0) {
		position = pop(); //현재 위치
		row = position.row; col = position.col; dir = position.dir;
		while (dir < 8 && found == 0) {
			next_row = row + move[dir][0];
			next_col = col + move[dir][1];
			if (next_row == ROW + 1 && next_col == COL + 1) {
				found = 1;
			}
			else if (maze[next_row][next_col] == 0 && mark[next_row][next_col] == 0) { //방문하지 않은 점
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
		printf("스택의 방문점 나열\n\n");
		for (k = 0; k <= top; k++) {
			printf("%2d 번째 : %2d 행 %2d 열\n", k + 1, stack[k].row, stack[k].col);
		}
		printf("%2d 번째 : %2d 행 %2d 열(최종 출구)\n", k + 1, row, col);
	}
	else {
		printf("입구에서 출구까지 경로가 없음\n");
	}
}