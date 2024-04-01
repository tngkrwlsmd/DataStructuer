#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)
#define N 10

typedef struct node {
    int id;
    char name[20];
    struct node* left; //자식
    struct node* right; //형제
    struct node* parnets; //부모
} tree;

tree* current = NULL; //직전노드를 가리키는 전역 변수

void file_store(tree* t, FILE* file); //데이터를 파일에 저장하는 함수, 중위순회 사용
void inorder(tree* t); //중위순회 탐색 -> 중위순회로 탐색해야 데이터 크기대로 출력됨
int search_tree(tree* t, int id);
void insert_tree(tree** t, int id, char name[]);
void delete_tree(tree** t, int id, char name[]);

int main()
{
    tree* tree_apply, * tree_drop;
    tree_apply = tree_drop = NULL; //각각의 루트 노드

    char ch, name[20];
    int length_apply = -1, length_drop = -1, id, n1, n2;
    FILE* f1, * f2;

    f1 = fopen("apply.dat", "r");
    while (fscanf(f1, "%d %s", &id, name) != EOF)
    {
        insert_tree(&tree_apply, id, name);
        length_apply++;
    }

    fclose(f1);

    f2 = fopen("drop.dat", "r");
    while (fscanf(f2, "%d %s", &id, name) != EOF)
    {
        insert_tree(&tree_drop, id, name);
        length_drop++;
    }
    fclose(f2);

    do
    {
        system("cls");
        printf("\n----------------------------------------\n");
        printf(" 수강 신청자 및 수강포기자 관리\n");
        printf("----------------------------------------\n");
        printf(" 1. 수강 신청 ('1')\n");
        printf(" 2. 수강철회 신청('2')\n");
        printf(" 3. 수강신청자 리스트 확인('3')\n");
        printf(" 4. 수강철회자 리스트 확인('4')\n");
        printf(" 5. 프로그램 종료('q')\n");
        printf("\n----------------------------------------\n");
        printf("\n\n 원하시는 서비스를 선택하세요.  ");

        ch = getche();

        switch (ch)
        {
        case '1':
            system("cls");
            printf("\n\n 요청하신 수강신청을 처리중입니다. \n");
            printf("\n 수강신청자 학번: ");
            scanf("%d", &id);
            printf("\n 수강신청자 이름: ");
            scanf("%s", name);

            n1 = search_tree(tree_apply, id); //신청 목록에 동일한 학생이 있는지 확인
            n2 = search_tree(tree_drop, id); //철회 목록에 동일한 학생이 있는지 확인
            if (n1 == 1) printf("\n\n 이미 수강신청을 한 학번입니다. \n\n");
            else if (length_apply + 1 == N) printf("\n\n 죄송합니다. 수강신청이 마감되었습니다. \n\n");
            else {
                if (n2 == 1) { //만약 철회 목록에 학생이 있다면 철회를 취소하고 다시 신청
                    delete_tree(&tree_drop, id, name);
                    length_drop--;
                }
                insert_tree(&tree_apply, id, name);
                length_apply++;
                printf("\n\n 요청하신 수강신청을 처리했습니다. \n\n");
            }
            break;
        case '2':
            system("cls");
            printf("\n\n 요청하신 수강철회을 처리중입니다. \n");
            if (length_drop == -1) printf("\n\n 수강철회할 인원이 없습니다. \n\n");
            printf("\n 수강철회자 학번: ");
            scanf("%d", &id);
            printf("\n 수강철회자 이름: ");
            scanf("%s", name);

            n1 = search_tree(tree_apply, id); //신청 목록에 동일한 학생이 있는지 확인
            n2 = search_tree(tree_drop, id); //철회 목록에 동일한 학생이 있는지 확인
            if (n2 == 1) printf("\n\n 이미 수강철회를 한 학생입니다. \n\n");
            else if (n1 == 1) {
                insert_tree(&tree_drop, id, name);
                delete_tree(&tree_apply, id, name);
                length_drop++;
                length_apply--;
                printf("\n\n 요청하신 수강철회를 처리했습니다. \n\n");
            }
            else printf("\n\n 존재하지 않는 학생입니다. \n\n");
            break;
        case '3':
            system("cls");
            if (length_apply == -1) printf("\n\n 수강신청자가 없습니다. \n\n");
            else {
                printf("\n\n 수강신청자 수: %d 명 \n", length_apply + 1);
                printf("\n\n 수강신청자 명단은 다음과 같습니다. \n\n");
                inorder(tree_apply);
            }
            break;
        case '4':
            system("cls");
            if (length_drop == -1) printf("\n\n 수강철회자가 없습니다. \n\n");
            else {
                printf("\n\n 수강철회자 수: %d 명 \n", length_drop + 1);
                printf("\n\n 수강철회자 명단은 다음과 같습니다. \n\n");
                inorder(tree_drop);
            }
            break;
        case 'q':
            system("cls");

            f1 = fopen("apply.dat", "w");
            file_store(tree_apply, f1);
            fclose(f1);

            f2 = fopen("drop.dat", "w");
            file_store(tree_drop, f2);
            fclose(f2);

            printf("\n\n 프로그램을 종료합니다. \n\n");
            break;
        default:
            system("cls");
            printf("키를 잘못 입력했습니다. \n");
            printf("화면의  설명을 보신 후, '1'~'4' 또는 'q'를 입력해주세요. \n\n");
        }
        printf("\n\n 임의의 키를 눌러주세요. ");
        getche();

    } while (ch != 'q');

    return 0;
}

void file_store(tree* t, FILE* file) {
    if (t == NULL) return;
    file_store(t->left, file);
    fprintf(file, "%d %s\n", t->id, t->name);
    file_store(t->right, file);
}

int search_tree(tree* t, int id)
{
    if (t == NULL) return 0;
    else if (id == t->id) return 1;
    else if (id < t->id) return(search_tree(t->left, id));
    else return(search_tree(t->right, id));
}

void inorder(tree* t) {
    if (t == NULL) return;
    inorder(t->left);
    printf(" 학번 : %d, 이름 : %s\n", t->id, t->name);
    inorder(t->right);
}

void insert_tree(tree** t, int id, char name[])
{
    tree* temp;
    temp = (tree*)malloc(sizeof(tree));
    temp->id = id;
    strcpy(temp->name, name);
    temp->left = NULL;
    temp->right = NULL;
    temp->parnets = NULL;

    if (*t == NULL) {
        *t = temp;
        if (current != NULL) (*t)->parnets = current; //자식을 부모노드로 연결
    }
    else if (id < (*t)->id) {
        current = *t;
        return(insert_tree(&(*t)->left, id, name));
    }
    else {
        current = *t;
        return (insert_tree(&(*t)->right, id, name));
    }
}

void delete_tree(tree** t, int id, char name[])
{
    tree* temp;
    if (*t == NULL) return;
    else if (id < (*t)->id) return (delete_tree(&(*t)->left, id, name));
    else if (id > (*t)->id) return (delete_tree(&(*t)->right, id, name));
    else {
        if ((*t)->parnets->left == *t) { //부모의 왼쪽 자식이 나일 때
            if ((*t)->left == NULL && (*t)->right == NULL) { //자식x
                (*t)->parnets->left = NULL;
                free(*t);
                *t = NULL; //t가 이상한 곳을 가리키지 못하도록 NULL로 초기화
            }
            else if ((*t)->left == NULL) { //왼쪽 자식x
                temp = *t;
                (*t)->parnets->left = (*t)->right;
                (*t)->right->parnets = (*t)->parnets;
                *t = (*t)->right;
                free(temp);
            }
            else if ((*t)->right == NULL) { //오른쪽 자식x
                temp = *t;
                (*t)->parnets->left = (*t)->left;
                (*t)->left->parnets = (*t)->parnets;
                *t = (*t)->left;
                free(temp);
            }
            else {
                //두 개의 자식이 있는 경우, 직후자 이용
                temp = (*t)->right; //직전자의 경우 (*t)->left;
                while ((temp->left) != NULL) temp = temp->left;
                (*t)->id = temp->id;
                strcpy((*t)->name, temp->name);
                return (delete_tree((*t)->right, id, name)); //직후자의 경우, 왼쪽 자식이 없거나 모두 자식이 없음
            }
        }
        else if ((*t)->parnets->right == *t) { //부모의 오른쪽 자식이 나일 때
            if ((*t)->left == NULL && (*t)->right == NULL) { //자식x
                (*t)->parnets->right = NULL;
                free(*t);
                *t = NULL; //t가 이상한 곳을 가리키지 못하도록 NULL로 초기화
            }
            else if ((*t)->left == NULL) { //왼쪽 자식x
                temp = *t;
                (*t)->parnets->right = (*t)->right;
                (*t)->right->parnets = (*t)->parnets;
                *t = (*t)->right;
                free(temp);
            }
            else if ((*t)->right == NULL) { //오른쪽 자식x
                temp = *t;
                (*t)->parnets->right = (*t)->left;
                (*t)->left->parnets = (*t)->parnets;
                *t = (*t)->left;
                free(temp);
            }
            else {
                //두 개의 자식이 있는 경우, 직후자 이용
                temp = (*t)->right; //직전자의 경우 (*t)->left;
                while ((temp->left) != NULL) temp = temp->left;
                (*t)->id = temp->id;
                strcpy((*t)->name, temp->name);
                return (delete_tree((*t)->right, id, name)); //직후자의 경우, 왼쪽 자식이 없거나 모두 자식이 없음
            }
        }
    }
}