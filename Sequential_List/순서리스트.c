#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)
#define N 10

typedef struct student
{
    int id;
    char name[20];
} std;

typedef struct node
{
    int id;
    char name[20];
    struct node* next;
} std_node;

// 연결리스트를 작성할 때, 직전노드의 위치를 받지 않는 대신, 데이터만을 이용해 노드의 위치를 계산하는 방법을 이용함

int search_list(std list[], int length, int id);
int search_node(std_node* first, int id, char* name); //학번(id)를 이용하여 데이터가 연결리스트 내에 존재하는지 판별하는 함수
void insert_list(std list[], int* length, int pos, int id, char* name);
void delete_list(std list[], int* length, int* length_node, int id);
void insert_node(std_node** first, int id, char* name); //오름차순으로 노드를 추가함
void delete_node(std_node** first, int id); //만약 수강신청을 할 때, 수강철회 목록에 수강신청을 할 학생이 있을 경우를 상정하여 만듦

int main()
{

    std student[N];
    std_node *first = NULL, *temp, *current; //여기서 first는 헤드 노드의 역할을 함

    int length = -1, length_node = -1, id, i, pos, n; // pos = 배열의 인덱스를 참조함
    char ch, name[20];
    FILE* f1, * f2;

    f1 = fopen("apply.dat", "r");
    while (fscanf(f1, "%d %s", &id, name) != EOF)
    {
        length++; 
        student[length].id = id;
        strcpy(student[length].name, name);
    };

    fclose(f1);

    f2 = fopen("drop.dat", "r");
    while (fscanf(f2, "%d %s", &id, name) != EOF)
    {
        insert_node(&first, id, name);
        length_node++;
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

        ch = getche(); // getchar와 달리 enter키가 필요없음

        switch (ch)
        {
        case '1':
            system("cls");
            printf("\n\n 요청하신 수강신청을 처리중입니다. \n");
            printf("\n 수강신청자 학번: ");
            scanf("%d", &id);
            printf("\n 수강신청자 이름: ");
            scanf("%s", name);
            pos = search_list(student, length, id); //수강신청하려는 학생의 인덱스 위치는 어디인가?
            n = search_node(first, id, name); //수강신청하려는 학생이 수강철회 목록에 존재하는가?

            if (pos >= N)
                printf("\n\n 죄송합니다. 수강신청이 마감되었습니다. \n\n");
            else
            {
                if (n == 1) // 존재한다면, 철회목록에서 지우고 다시 수강신청을 진행
                {
                    delete_node(&first, id);
                    length_node--; //철회 목록에서 빠졌으므로 감소
                }
                insert_list(student, &length, pos, id, name);
                printf("\n\n 요청하신 수강신청을 처리했습니다. \n\n");
            }

            break;
        case '2': //수강신청자 목록 삭제 후 철회자 목록에 추가
            system("cls");
            printf("\n\n 요청하신 수강철회를 처리중입니다. \n");
            if (length == -1)
                printf("\n\n 수강철회할 인원이 없습니다. \n\n");
            printf("\n 수강철회자 학번: ");
            scanf("%d", &id);
            for (i = 0; i <= length; i++)
            {
                if (student[i].id == id) //삭제할 학생이 먼저 있는지 확인
                {
                    insert_node(&first, student[i].id, student[i].name); //연결리스트 노드에 추가
                    break;
                }
            }
            delete_list(student, &length, &length_node, id);
            break;
        case '3':
            system("cls");
            if (length == -1)
                printf("\n\n 수강신청자가 없습니다. \n\n");
            else
            {
                printf("\n\n 수강신청자 수: %d 명 \n", length + 1);
                printf("\n\n 수강신청자 명단은 다음과 같습니다. \n\n");
                for (i = 0; i <= length; i++)
                {
                    printf(" [%d] 학번: %d, 이름: %s\n", i, student[i].id, student[i].name);
                }
            }
            break;
        case '4':
            system("cls");
            current = first;

            if (length_node == -1)
            {
                printf("\n\n 수강철회자가 없습니다. \n\n");
            }
            else
            {
                printf("\n\n 수강철회자 수: %d 명 \n", length_node + 1);
                printf("\n\n 수강철회자 명단은 다음과 같습니다. \n\n");

                while (current != NULL)
                {
                    printf(" 학번 : %d, 이름 : %s\n", current->id, current->name);
                    current = current->next;
                }
            }
            break;
        case 'q':
            system("cls");
            f1 = fopen("apply.dat", "w");
            for (i = 0; i <= length; i++)
            {
                fprintf(f1, "%d %s\n", student[i].id, student[i].name);
            }
            fclose(f1);

            f2 = fopen("drop.dat", "w");
            temp = first;
            while (temp != NULL)
            {
                fprintf(f2, "%d %s\n", temp->id, temp->name);
                temp = temp->next;
            }
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

int search_list(std list[], int length, int id)
{

    int i;

    if (length < 0)
        return 0;

    for (i = 0; i <= length; i++)
    {
        if (id < list[i].id) // 학번 순 정렬
            return i;
    }
    return i;
}

int search_node(std_node *first, int id, char* name)
{
    std_node* current;
    current = first;

    while (current != NULL)
    {
        if (current->id == id)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        current = current->next;
    }
}

void insert_list(std list[], int* length, int pos, int id, char* name)
{

    int i;

    for (i = *length; i >= pos; i--)
    {
        list[i + 1].id = list[i].id;
        strcpy(list[i + 1].name, list[i].name);
    }

    list[pos].id = id;
    strcpy(list[pos].name, name);
    *length = *length + 1;
}

void delete_list(std list[], int* length, int* length_node, int id) // 해당 학번이 먼저 있는지 확인하고, 삭제를 실행함
{

    int found = 0, i, j;

    for (i = 0; i <= *length; i++) 
    {
        if (list[i].id == id)
        {
            found = 1;
            for (j = i; j <= *length; j++) 
            {
                list[j] = list[j + 1]; //앞으로 이동
                strcpy(list[j].name, list[j + 1].name);
            }
            *length = *length - 1;
            *length_node = *length_node + 1;
            printf("\n\n 요청하신 수강철회를 처리했습니다. \n\n");
            break;
        }
    }
    if (found == 0)
        printf("\n\n 존재하지 않는 학생입니다. \n\n");
}

void insert_node(std_node **first, int id, char *name)
{
    std_node* temp, * current;
    temp = (std_node*)malloc(sizeof(std_node));
    temp->id = id;
    strcpy(temp->name, name);
    temp->next = NULL;
    if (*first == NULL) //비어있는 경우
    {
        *first = temp;
    }
    else if (id <= (*first)->id) //추가할 노드가 첫 번째 노드보다 작거나 같을 경우
    {
        temp->next = *first;
        *first = temp;
    }
    else
    {
        current = *first;
        while (current->next != NULL && current->next->id < id) //다음 노드가 비어있지 않고, 다음 노드의 데이터가 입력할 데이터보다 작을 때까지 반복
        {
            current = current->next;
        }
        temp->next = current->next; //temp를 원래 current가 가리키던 노드로 연결
        current->next = temp; //current가 temp를 가리키도록 함
    }
}

void delete_node(std_node** first, int id)
{
    std_node* temp = NULL, * current = *first;

    while (current != NULL && current->id != id) //삭제하려는 데이터까지 계속 이동
    {
        temp = current;
        current = current->next;
    }

    if (temp == NULL) //첫 번째 노드
    {
        *first = (*first)->next; //원래 first가 가리키던 곳을 가리키도록 대입
    }
    else { //중간 이후의 노드
        temp->next = current->next; //temp에 current가 가리키던 곳을 대입하므로 current가 삭제됨
    }

    free(current);
}