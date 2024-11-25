#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "vocaList.h"
#include "memcard.h"
#include "ui.h"


// 새로운 노드를 생성하는 함수
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

    // voca와 mean에 값을 복사
    strncpy(newNode->pVocaData->voca, voca, LEN);
    strncpy(newNode->pVocaData->mean, mean, LEN);

    newNode->pPrev = NULL;
    newNode->pNext = NULL;

    return newNode;
}

// 파일에서 단어와 의미를 읽어 LinkedList를 생성하는 함수
LinkedList* createLinkedListFromFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("ERROR: Failed to open the file\n");
        return NULL;
    }

    LinkedList* head = NULL;  // 리스트의 시작을 나타내는 포인터
    LinkedList* tail = NULL;  // 리스트의 끝을 나타내는 포인터

    char voca[LEN];
    char mean[LEN];

    while (fscanf(file, "%s %[^\n]", voca, mean) != EOF) // file에서 단어와 의미 읽기
    {
        LinkedList* newNode = createNode(voca, mean);  // 새 노드 생성

        if (newNode == NULL)
        {
            fclose(file);
            return NULL;
        }

        // 첫 번째 노드일 경우
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        // 첫 번째 이후의 노드일 경우
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

// 리스트의 내용을 출력하는 함수 (전체 단어와 의미)
void printLinkedList(LinkedList* head, const int option)
{
    LinkedList* current = head;
    while (current != NULL)
    {
        if (option == 1)  // 전체 단어와 의미 출력
        {
            printf("%s : %s\n", current->pVocaData->voca, current->pVocaData->mean);
        }
        else if (option == 2)  // 영단어만 출력
        {
            printf("%s\n", current->pVocaData->voca);
        }
        else if (option == 3)  // 의미만 출력
        {
            printf("%s\n", current->pVocaData->mean);
        }
        current = current->pNext;
    }
}

// 리스트를 무작위로 섞어서 출력하는 함수
void printShuffledLinkedList(LinkedList* head, const int option)
{
    // 노드의 개수를 계산
    int count = 0;
    LinkedList* current = head;
    while (current != NULL)
    {
        count++;
        current = current->pNext;
    }

    // 무작위로 섞을 배열 만들기
    if (count < 2) return;  // 노드가 하나뿐이면 섞을 필요 없음

    LinkedList** nodes = (LinkedList**)malloc(count * sizeof(LinkedList*));
    current = head;
    for (int i = 0; i < count; i++)
    {
        nodes[i] = current;
        current = current->pNext;
    }

    // 랜덤하게 섞기
    srand((unsigned int)time(NULL));  // 랜덤 시드 설정
    for (int i = 0; i < count; i++)
    {
        int j = rand() % count;
        LinkedList* temp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = temp;
    }

    // 섞인 노드들을 무작위로 출력
    for (int i = 0; i < count; i++)
    {

        if (option == 1)  // 전체 단어와 의미 출력
        {
            printf("%s : %s\n", nodes[i]->pVocaData->voca, nodes[i]->pVocaData->mean);
        }
        else if (option == 2)  // 영단어만 출력
        {
            printf("%s\n", nodes[i]->pVocaData->voca);
        }
        else if (option == 3)  // 의미만 출력
        {
            printf("%s\n", nodes[i]->pVocaData->mean);
        }
    }

    // 메모리 해제
    free(nodes);
}

// LinkedList 메모리 해제 함수
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

// 비교 함수 (qsort에 사용)
int compareVoca(const void* a, const void* b)
{
    LinkedList* nodeA = *((LinkedList**)a);
    LinkedList* nodeB = *((LinkedList**)b);
    return strcmpi(nodeA->pVocaData->voca, nodeB->pVocaData->voca);
}

// 프로그램 시작 시 실행되는 List 초기화 함수
void initList()
{
    // 파일로부터 원본 LinkedList 생성
    head = createLinkedListFromFile(filename);
    if (head == NULL)
    {
        puts("ERROR: Head is NULL");
        return;
    }

    // 정렬된 LinkedList 생성 (qsort 사용)
    sortedHead = createLinkedListFromFile(filename);
    LinkedList* current = sortedHead;
    int nodeCount = 0;

    // 리스트의 노드를 배열로 저장
    LinkedList* nodes[100]; // 최대 100개 노드를 저장할 배열 (데이터의 크기에 맞게 수정)
    while (current != NULL)
    {
        nodes[nodeCount++] = current;
        current = current->pNext;
    }

    // qsort를 사용하여 단어 순으로 정렬
    qsort(nodes, nodeCount, sizeof(LinkedList*), compareVoca);

    // 정렬된 결과로 새로운 링크드 리스트 생성
    for (int i = 0; i < nodeCount - 1; i++)
    {
        nodes[i]->pNext = nodes[i + 1];
        nodes[i + 1]->pPrev = nodes[i];
    }
    nodes[nodeCount - 1]->pNext = NULL;
    nodes[0]->pPrev = NULL;

    sortedHead = nodes[0];  // 정렬된 리스트의 헤드
}
