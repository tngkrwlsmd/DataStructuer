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

// 함수 선언
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

// 숫자를 채울 수 있는지 확인하는 함수
int isSafe(int row, int col, int num) {
    // 행과 열을 검사
    for (int i = 0; i < N; i++) {
        if (sudoku[row][i] == num || sudoku[i][col] == num) {
            return 0;
        }
    }

    // 3x3 영역을 검사
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[i + startRow][j + startCol] == num) {
                return 0;
            }
        }
    }

    return 1; // 채울 수 있음
}

// 스도쿠를 해결하는 함수
int solveSudoku() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (sudoku[row][col] == 0) { // 빈 칸을 찾음
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(row, col, num)) {
                        sudoku[row][col] = num; // 가능한 경우 숫자를 채움

                        if (solveSudoku()) { // 재귀적으로 호출하여 다음 빈 칸을 채움
                            return 1; // 해를 찾음
                        }

                        sudoku[row][col] = 0; // 다음 숫자를 시도하기 위해 원래 상태로 복원
                    }
                }

                return 0; // 가능한 숫자를 찾을 수 없음
            }
        }
    }

    return 1; // 모든 칸이 채워져 있음
}

// 스도쿠를 출력하는 함수
void printSudoku() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
}
