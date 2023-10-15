#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char data;
    struct Node* next;
} Node;

typedef struct Queue1 //loan
{
    struct Node* front1;
    struct Node* rear1;
    int count1; // 큐 안의 대출노드 개수
} Queue1;

typedef struct Queue2 //reception
{
    struct Node* front2;
    struct Node* rear2;
    int count2; // 큐 안의 수신노드 개수
} Queue2;

int isEmpty1(Queue1* queue1) //loan
{
    if (queue1->count1 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isEmpty2(Queue2* queue2) //reception
{
    if (queue2->count2 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char input()
{
    char input[10];
    printf("업무를 선택하세요(대출 / 수신): ");
    scanf_s("%s", input, 10);
    if (strcmp(input, "대출") == 0)
    {
        return 'L';
    }
    else if (strcmp(input, "수신") == 0)
    {
        return 'R';
    }
    else
    {
        return 'X';
    }
}

void enqueue1(Queue1* queue1)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = 'L';
    newNode->next = NULL;

    if (isEmpty1(queue1)) // 큐가 비어있을 때
    {
        queue1->front1 = newNode;
        queue1->rear1 = newNode;
    }
    else // 큐에 이미 노드가 있는 경우
    {
        queue1->rear1->next = newNode;
        queue1->rear1 = newNode;
    }
    queue1->count1++;
}

void enqueue2(Queue2* queue2)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = 'R';
    newNode->next = NULL;

    if (isEmpty2(queue2)) // 큐가 비어있을 때
    {
        queue2->front2 = newNode;
        queue2->rear2 = newNode;
    }
    else // 큐에 이미 노드가 있는 경우
    {
        queue2->rear2->next = newNode;
        queue2->rear2 = newNode;
    }
    queue2->count2++;
}

char output()
{
    char output[10];

    printf("호출할 대기 종류를 선택하세요(대출 / 수신): ");
    scanf_s("%s", output, 10);

    if (strcmp(output, "대출") == 0)
    {
        return 'L';
    }
    else if (strcmp(output, "수신") == 0)
    {
        return 'R';
    }
    else
    {
        return 'X';
    }
}

int dequeue1(Queue1* queue1)
{
    Node* p1;

    char outputData = 'L';
    if (isEmpty1(queue1) == 1)
    {
        return 0;
    }

    else
    {
        p1 = queue1->front1;
        outputData = p1->data;
        queue1->front1 = p1->next;
        free(p1);
        queue1->count1--;
        return 1;
    }
}

int dequeue2(Queue2* queue2)
{
    Node* p2;

    char outputData = 'R';
    if (isEmpty2(queue2) == 1)
    {
        return 0;
    }

    else
    {
        p2 = queue2->front2;
        outputData = p2->data;
        queue2->front2 = p2->next;
        free(p2);
        queue2->count2--;
        return 1;
    }
}

int main(void)
{
    Queue1* queue1 = (Queue1*)malloc(sizeof(Queue1));
    queue1->front1 = queue1->rear1 = NULL;
    queue1->count1 = 0;

    Queue2* queue2 = (Queue2*)malloc(sizeof(Queue2));
    queue2->front2 = queue2->rear2 = NULL;
    queue2->count2 = 0;


    int i;
    char inputResult;
    char outputResult;
    int dCount1 = 1;
    int dCount2 = 1;
    int eCount1 = 1;
    int eCount2 = 1;
    int dq1;
    int dq2;

    for (i = 0; i < 10; i++)
    {
        inputResult = input();
        if (inputResult == 'L')
        {
            enqueue1(queue1);
            printf("등록되었습니다. 대출 대기번호는 %d번 입니다.\n", eCount1);
            eCount1++;
        }
        else if (inputResult == 'R')
        {
            enqueue2(queue2);
            printf("등록되었습니다. 수신 대기번호는 %d번 입니다.\n", eCount2);
            eCount2++;
        }
        else if (inputResult == 'X')
        {
            printf("잘못 입력되었습니다. 다시 입력하세요.\n");
            i--;
        }
    }

    printf("================================================\n");
    for (i = 0; i < 10; i++)
    {
        outputResult = output();
        if (outputResult == 'L')
        {
            dq1 = dequeue1(queue1);
            if (dq1 == 0)
            {
                printf("대출 큐가 비었습니다.\n");
                i--;
            }
            else if (dq1 == 1)
            {
                printf("대출 %d번 고객님 호출\n", dCount1);
                dCount1++;
            }
        }
        else if (outputResult == 'R')
        {
            dq2 = dequeue2(queue2);
            if (dq2 == 0)
            {
                printf("수신 큐가 비었습니다.\n");
                i--;
            }
            else if (dq2 == 1)
            {
                printf("수신 %d번 고객님 호출\n", dCount2);
                dCount2++;
            }
        }
        else if (outputResult == 'X')
        {
            printf("잘못 입력되었습니다. 다시 입력하세요.\n");
            i--;
        }
    }
    printf("================================================\n");

    // 메모리 해제 
    Node* cur1 = queue1->front1;
    while (cur1 != NULL)
    {
        Node* temp = cur1;
        cur1 = cur1->next;
        free(temp);
    }
    free(queue1);

    Node* cur2 = queue2->front2;
    while (cur2 != NULL)
    {
        Node* temp = cur2;
        cur2 = cur2->next;
        free(temp);
    }
    free(queue2);

    return 0;
}

