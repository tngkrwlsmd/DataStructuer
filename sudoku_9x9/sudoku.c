#include <stdio.h>
#define N 9

int sudoku[N][N] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

// �Լ� ����
int isSafe(int row, int col, int num);
int solveSudoku();
void printSudoku();

int main() {
    if (solveSudoku()) {
        printf("Solution:\n");
        printSudoku();
    }
    else {
        printf("No solution exists.\n");
    }

    return 0;
}

// ���ڸ� ä�� �� �ִ��� Ȯ���ϴ� �Լ�
int isSafe(int row, int col, int num) {
    // ��� ���� �˻�
    for (int i = 0; i < N; i++) {
        if (sudoku[row][i] == num || sudoku[i][col] == num) {
            return 0;
        }
    }

    // 3x3 ������ �˻�
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[i + startRow][j + startCol] == num) {
                return 0;
            }
        }
    }

    return 1; // ä�� �� ����
}

// ������ �ذ��ϴ� �Լ�
int solveSudoku() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (sudoku[row][col] == 0) { // �� ĭ�� ã��
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(row, col, num)) {
                        sudoku[row][col] = num; // ������ ��� ���ڸ� ä��

                        if (solveSudoku()) { // ��������� ȣ���Ͽ� ���� �� ĭ�� ä��
                            return 1; // �ظ� ã��
                        }

                        sudoku[row][col] = 0; // ���� ���ڸ� �õ��ϱ� ���� ���� ���·� ����
                    }
                }

                return 0; // ������ ���ڸ� ã�� �� ����
            }
        }
    }

    return 1; // ��� ĭ�� ä���� ����
}

// ������ ����ϴ� �Լ�
void printSudoku() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
}
