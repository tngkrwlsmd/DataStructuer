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
//    printf("���� ���� �Է�: ");
//    scanf("%d", &n);
//    printf("\n");
//    hanoitower(n, "start", "end", "temp");
//    printf("�ű� Ƚ�� : %d", count);
//
//    return 0;
//}
//
//void hanoitower(int n, char start[], char end[], char temp[]) {
//
//    if (n > 0) {
//        hanoitower(n - 1, start, temp, end);
//        printf("%d-���� �̵� : %s -> %s \n", n, start, end);
//        count++;
//        hanoitower(n - 1, temp, end, start);
//    }
//}
