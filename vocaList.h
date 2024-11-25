#pragma once

#define LEN 64 // 단어와 의미의 최대 길이

// 단어 구조체
typedef struct VocaStruct
{
    char voca[LEN];
    char mean[LEN];
} VocaStruct;

// 이중 연결 리스트 노드 구조체
typedef struct LinkedList
{
    VocaStruct* pVocaData;
    struct LinkedList* pPrev;
    struct LinkedList* pNext;
} LinkedList;

extern LinkedList* head;         // 원본 리스트
extern LinkedList* sortedHead;   // 정렬된 리스트

extern const char* filename;

LinkedList* createNode(const char* voca, const char* mean);

LinkedList* createLinkedListFromFile(const char* filename);

void printLinkedList(LinkedList* head, const int option);

void printShuffledLinkedList(LinkedList* head, const int option);

void freeLinkedList(LinkedList* head);

int compareVoca(const void* a, const void* b);

void initList();
