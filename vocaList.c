#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "vocaList.h"
#include "memcard.h"
#include "ui.h"


// ���ο� ��带 �����ϴ� �Լ�
LinkedList* createNode(const char* voca, const char* mean)
{
    LinkedList* newNode = (LinkedList*)malloc(sizeof(LinkedList));

    if (!newNode)
    {
        printf("ERROR: Failed to allocate the memory\n");
        return NULL;
    }

    newNode->pVocaData = (VocaStruct*)malloc(sizeof(VocaStruct));
    if (!(newNode->pVocaData))
    {
        printf("ERROR: Failed to allocate the memory\n");
        free(newNode);
        return NULL;
    }

    // voca�� mean�� ���� ����
    strncpy(newNode->pVocaData->voca, voca, LEN);
    strncpy(newNode->pVocaData->mean, mean, LEN);

    newNode->pPrev = NULL;
    newNode->pNext = NULL;

    return newNode;
}

// ���Ͽ��� �ܾ�� �ǹ̸� �о� LinkedList�� �����ϴ� �Լ�
LinkedList* createLinkedListFromFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("ERROR: Failed to open the file\n");
        return NULL;
    }

    LinkedList* head = NULL;  // ����Ʈ�� ������ ��Ÿ���� ������
    LinkedList* tail = NULL;  // ����Ʈ�� ���� ��Ÿ���� ������

    char voca[LEN];
    char mean[LEN];

    while (fscanf(file, "%s %[^\n]", voca, mean) != EOF) // file���� �ܾ�� �ǹ� �б�
    {
        LinkedList* newNode = createNode(voca, mean);  // �� ��� ����

        if (newNode == NULL)
        {
            fclose(file);
            return NULL;
        }

        // ù ��° ����� ���
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        // ù ��° ������ ����� ���
        else
        {
            tail->pNext = newNode;
            newNode->pPrev = tail;
            tail = newNode;
        }
    }

    fclose(file);
    return head;
}

// ����Ʈ�� ������ ����ϴ� �Լ� (��ü �ܾ�� �ǹ�)
void printLinkedList(LinkedList* head, const int option)
{
    LinkedList* current = head;
    while (current != NULL)
    {
        if (option == 1)  // ��ü �ܾ�� �ǹ� ���
        {
            printf("%s : %s\n", current->pVocaData->voca, current->pVocaData->mean);
        }
        else if (option == 2)  // ���ܾ ���
        {
            printf("%s\n", current->pVocaData->voca);
        }
        else if (option == 3)  // �ǹ̸� ���
        {
            printf("%s\n", current->pVocaData->mean);
        }
        current = current->pNext;
    }
}

// ����Ʈ�� �������� ��� ����ϴ� �Լ�
void printShuffledLinkedList(LinkedList* head, const int option)
{
    // ����� ������ ���
    int count = 0;
    LinkedList* current = head;
    while (current != NULL)
    {
        count++;
        current = current->pNext;
    }

    // �������� ���� �迭 �����
    if (count < 2) return;  // ��尡 �ϳ����̸� ���� �ʿ� ����

    LinkedList** nodes = (LinkedList**)malloc(count * sizeof(LinkedList*));
    current = head;
    for (int i = 0; i < count; i++)
    {
        nodes[i] = current;
        current = current->pNext;
    }

    // �����ϰ� ����
    srand((unsigned int)time(NULL));  // ���� �õ� ����
    for (int i = 0; i < count; i++)
    {
        int j = rand() % count;
        LinkedList* temp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = temp;
    }

    // ���� ������ �������� ���
    for (int i = 0; i < count; i++)
    {

        if (option == 1)  // ��ü �ܾ�� �ǹ� ���
        {
            printf("%s : %s\n", nodes[i]->pVocaData->voca, nodes[i]->pVocaData->mean);
        }
        else if (option == 2)  // ���ܾ ���
        {
            printf("%s\n", nodes[i]->pVocaData->voca);
        }
        else if (option == 3)  // �ǹ̸� ���
        {
            printf("%s\n", nodes[i]->pVocaData->mean);
        }
    }

    // �޸� ����
    free(nodes);
}

// LinkedList �޸� ���� �Լ�
void freeLinkedList(LinkedList* head)
{
    LinkedList* current = head;
    LinkedList* temp;

    while (current != NULL)
    {
        temp = current;
        current = current->pNext;
        free(temp->pVocaData);
        free(temp);
    }
}

// �� �Լ� (qsort�� ���)
int compareVoca(const void* a, const void* b)
{
    LinkedList* nodeA = *((LinkedList**)a);
    LinkedList* nodeB = *((LinkedList**)b);
    return strcmpi(nodeA->pVocaData->voca, nodeB->pVocaData->voca);
}

// ���α׷� ���� �� ����Ǵ� List �ʱ�ȭ �Լ�
void initList()
{
    // ���Ϸκ��� ���� LinkedList ����
    head = createLinkedListFromFile(filename);
    if (head == NULL)
    {
        puts("ERROR: Head is NULL");
        return;
    }

    // ���ĵ� LinkedList ���� (qsort ���)
    sortedHead = createLinkedListFromFile(filename);
    LinkedList* current = sortedHead;
    int nodeCount = 0;

    // ����Ʈ�� ��带 �迭�� ����
    LinkedList* nodes[100]; // �ִ� 100�� ��带 ������ �迭 (�������� ũ�⿡ �°� ����)
    while (current != NULL)
    {
        nodes[nodeCount++] = current;
        current = current->pNext;
    }

    // qsort�� ����Ͽ� �ܾ� ������ ����
    qsort(nodes, nodeCount, sizeof(LinkedList*), compareVoca);

    // ���ĵ� ����� ���ο� ��ũ�� ����Ʈ ����
    for (int i = 0; i < nodeCount - 1; i++)
    {
        nodes[i]->pNext = nodes[i + 1];
        nodes[i + 1]->pPrev = nodes[i];
    }
    nodes[nodeCount - 1]->pNext = NULL;
    nodes[0]->pPrev = NULL;

    sortedHead = nodes[0];  // ���ĵ� ����Ʈ�� ���
}
