#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> //�ο� �ڷ����� �̿��� ���������� ������û�� �����ϰ� �۾��ϵ��� ����� �߰���
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
    struct node *next;
} std_node;

// ���Ḯ��Ʈ�� �ۼ��� ��, ��������� ��ġ�� ���� �ʴ� ���, �����͸��� �̿��� ����� ��ġ�� ����ϴ� ����� �̿���

int search_list(std list[], int length, int id);
int search_node(std_node *first, int id, char *name); // �й�(id)�� �̿��Ͽ� �����Ͱ� ���Ḯ��Ʈ ���� �����ϴ��� �Ǻ��ϴ� �Լ�
void insert_list(std list[], int *length, int pos, int id, char *name);
void delete_list(std list[], int *length, int *length_node, int id);
void insert_node(std_node **first, int id, char *name); // ������������ ��带 �߰���
void delete_node(std_node **first, int id);             // ���� ������û�� �� ��, ����öȸ ��Ͽ� ������û�� �� �л��� ���� ��츦 �����Ͽ� ����

int main()
{

    std student[N];
    std_node *first = NULL, *temp, *current; // ���⼭ first�� ��� ����� ������ ��

    int length = -1, length_node = -1, id, i, pos, n; // pos = �迭�� �ε����� ������
    char ch, name[20];
    FILE *f1, *f2;

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
        printf(" ���� ��û�� �� ���������� ����\n");
        printf("----------------------------------------\n");
        printf(" 1. ���� ��û ('1')\n");
        printf(" 2. ����öȸ ��û('2')\n");
        printf(" 3. ������û�� ����Ʈ Ȯ��('3')\n");
        printf(" 4. ����öȸ�� ����Ʈ Ȯ��('4')\n");
        printf(" 5. ���α׷� ����('q')\n");
        printf("\n----------------------------------------\n");
        printf("\n\n ���Ͻô� ���񽺸� �����ϼ���.  ");

        ch = getche(); // getchar�� �޸� enterŰ�� �ʿ����

        switch (ch)
        {
        case '1':
            system("cls");
            printf("\n\n ��û�Ͻ� ������û�� ó�����Դϴ�. \n");
            printf("\n ������û�� �й�: ");
            scanf("%d", &id);
            printf("\n ������û�� �̸�: ");
            scanf("%s", name);
            pos = search_list(student, length, id); // ������û�Ϸ��� �л��� �ε��� ��ġ�� ����ΰ�?
            n = search_node(first, id, name);       // ������û�Ϸ��� �л��� ����öȸ ��Ͽ� �����ϴ°�?

            if (pos >= N)
                printf("\n\n �˼��մϴ�. ������û�� �����Ǿ����ϴ�. \n\n");

            else
            {
                for (i = 0; i <= length; i++)
                {
                    if ((student[i].id == id) && !strcmp(student[i].name, name))
                    {
                        printf("\n\n �̹� ������û�� �� �л��Դϴ�. \n\n");
                        goto not_insert; // �̹� ��û�� �л��� �迭�� �߰��� �ʿ䰡 ����(not_insert ���̺�� �ǳʶ�)
                    }
                    else if ((student[i].id == id))
                    {
                        printf("\n\n �й��� �̸��� ���� ��ġ���� �ʽ��ϴ�. \n\n");
                        goto not_insert; //������û�� �Էµ� �л��� �����Ϳ� Ʋ�� ��, ���������� ������
                    }
                }
                if (n == 1) // �����Ѵٸ�, öȸ��Ͽ��� ����� �ٽ� ������û�� ����
                {
                    delete_node(&first, id);
                    length_node--; // öȸ ��Ͽ��� �������Ƿ� ����
                }
                else if (n == 2)
                {
                    printf("\n\n �й��� �̸��� ���� ��ġ���� �ʽ��ϴ�. \n\n");
                    goto not_insert; // ����öȸ�� ���� �л��� �����Ϳ� ��ġ���� �ʱ� ����(not_insert ���̺�� �ǳʶ�)
                }
                // �� ���� ���� ��忡 �л� �����Ͱ� �����Ƿ� �ű� �л��� �ǹ���
                insert_list(student, &length, pos, id, name);
                printf("\n\n ��û�Ͻ� ������û�� ó���߽��ϴ�. \n\n");
            }
        not_insert: // goto�� ����� ��������� ������, for, if���� ��ø�Ǹ鼭 �ڵ尡 ���������� ������ ���� ũ�ٰ� �ǴܵǾ� �����
            break;
        case '2': // ������û�� ��� ���� �� öȸ�� ��Ͽ� �߰�
            system("cls");
            printf("\n\n ��û�Ͻ� ����öȸ�� ó�����Դϴ�. \n");
            if (length == -1)
                printf("\n\n ����öȸ�� �ο��� �����ϴ�. \n\n");
            printf("\n ����öȸ�� �й�: ");
            scanf("%d", &id);
            for (i = 0; i <= length; i++)
            {
                if (student[i].id == id) // ������ �л��� ���� �ִ��� Ȯ��
                {
                    insert_node(&first, student[i].id, student[i].name); // ���Ḯ��Ʈ ��忡 �߰�
                    break;
                }
            }
            delete_list(student, &length, &length_node, id);
            break;
        case '3':
            system("cls");
            if (length == -1)
                printf("\n\n ������û�ڰ� �����ϴ�. \n\n");
            else
            {
                printf("\n\n ������û�� ��: %d �� \n", length + 1);
                printf("\n\n ������û�� ����� ������ �����ϴ�. \n\n");
                for (i = 0; i <= length; i++)
                {
                    printf(" [%d] �й�: %d, �̸�: %s\n", i, student[i].id, student[i].name);
                }
            }
            break;
        case '4':
            system("cls");
            current = first;

            if (length_node == -1)
            {
                printf("\n\n ����öȸ�ڰ� �����ϴ�. \n\n");
            }
            else
            {
                printf("\n\n ����öȸ�� ��: %d �� \n", length_node + 1);
                printf("\n\n ����öȸ�� ����� ������ �����ϴ�. \n\n");

                while (current != NULL)
                {
                    printf(" �й� : %d, �̸� : %s\n", current->id, current->name);
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
            printf("\n\n ���α׷��� �����մϴ�. \n\n");
            break;
        default:
            system("cls");
            printf("Ű�� �߸� �Է��߽��ϴ�. \n");
            printf("ȭ����  ������ ���� ��, '1'~'4' �Ǵ� 'q'�� �Է����ּ���. \n\n");
        }
        printf("\n\n ������ Ű�� �����ּ���. ");
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
        if (id < list[i].id) // �й� �� ����
            return i;
    }
    return i;
}

int search_node(std_node *first, int id, char *name)
{
    std_node *current;
    current = first;

    bool n1, n2;

    while (current != NULL)
    {
        n1 = (current->id == id);          // �й��� ������ 1, �ٸ��� 0
        n2 = !strcmp(current->name, name); // �̸��� ������ 1, �ٸ��� 0

        if (n1 && n2) // �й��� �̸��� ���� ��ġ�� ���(AND ����)
        {
            return 1;
        }
        else if (n1 ^ n2) // �й��� �̸��� ���� ��ġ���� ����(XOR ����)
        {
            return 2;
        }
        current = current->next;
    };
}

void insert_list(std list[], int *length, int pos, int id, char *name)
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

void delete_list(std list[], int *length, int *length_node, int id) // �ش� �й��� ���� �ִ��� Ȯ���ϰ�, ������ ������
{

    int found = 0, i, j;

    for (i = 0; i <= *length; i++)
    {
        if (list[i].id == id)
        {
            found = 1;
            for (j = i; j <= *length; j++)
            {
                list[j] = list[j + 1]; // ������ �̵�
                strcpy(list[j].name, list[j + 1].name);
            }
            *length = *length - 1;
            *length_node = *length_node + 1;
            printf("\n\n ��û�Ͻ� ����öȸ�� ó���߽��ϴ�. \n\n");
            break;
        }
    }
    if (found == 0)
        printf("\n\n �������� �ʴ� �л��Դϴ�. \n\n");
}

void insert_node(std_node **first, int id, char *name)
{
    std_node *temp, *current;
    temp = (std_node *)malloc(sizeof(std_node));
    temp->id = id;
    strcpy(temp->name, name);
    temp->next = NULL;
    if (*first == NULL) // ����ִ� ���
    {
        *first = temp;
    }
    else if (id <= (*first)->id) // �߰��� ��尡 ù ��° ��庸�� �۰ų� ���� ���
    {
        temp->next = *first;
        *first = temp;
    }
    else
    {
        current = *first;
        while (current->next != NULL && current->next->id < id) // ���� ��尡 ������� �ʰ�, ���� ����� �����Ͱ� �Է��� �����ͺ��� ���� ������ �ݺ�
        {
            current = current->next;
        }
        temp->next = current->next; // temp�� ���� current�� ����Ű�� ���� ����
        current->next = temp;       // current�� temp�� ����Ű���� ��
    }
}

void delete_node(std_node **first, int id)
{
    std_node *temp = NULL, *current = *first;

    while (current != NULL && current->id != id) // �����Ϸ��� �����ͱ��� ��� �̵�
    {
        temp = current;
        current = current->next;
    }

    if (temp == NULL) // ù ��° ���
    {
        *first = (*first)->next; // ���� first�� ����Ű�� ���� ����Ű���� ����
    }
    else
    {                               // �߰� ������ ���
        temp->next = current->next; // temp�� current�� ����Ű�� ���� �����ϹǷ� current�� ������
    }
    free(current);
}