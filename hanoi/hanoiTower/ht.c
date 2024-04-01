//#include <stdio.h>
//#pragma warning(disable : 4996)
//
//int count;
//void hanoitower(int n, char start[], char end[], char temp[]);
//
//int main(void) {
//
//    int n;
//
//    printf("원반 개수 입력: ");
//    scanf("%d", &n);
//    printf("\n");
//    hanoitower(n, "start", "end", "temp");
//    printf("옮긴 횟수 : %d", count);
//
//    return 0;
//}
//
//void hanoitower(int n, char start[], char end[], char temp[]) {
//
//    if (n > 0) {
//        hanoitower(n - 1, start, temp, end);
//        printf("%d-원반 이동 : %s -> %s \n", n, start, end);
//        count++;
//        hanoitower(n - 1, temp, end, start);
//    }
//}
