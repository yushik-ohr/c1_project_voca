#pragma once

#define LEN 64 // �ܾ�� �ǹ��� �ִ� ����

// �ܾ� ����ü
typedef struct VocaStruct
{
    char voca[LEN];
    char mean[LEN];
} VocaStruct;

// ���� ���� ����Ʈ ��� ����ü
typedef struct LinkedList
{
    VocaStruct* pVocaData;
    struct LinkedList* pPrev;
    struct LinkedList* pNext;
} LinkedList;

extern LinkedList* head;         // ���� ����Ʈ
extern LinkedList* sortedHead;   // ���ĵ� ����Ʈ

extern const char* filename;

LinkedList* createNode(const char* voca, const char* mean);

LinkedList* createLinkedListFromFile(const char* filename);

void printLinkedList(LinkedList* head, const int option);

void printShuffledLinkedList(LinkedList* head, const int option);

void freeLinkedList(LinkedList* head);

int compareVoca(const void* a, const void* b);

void initList();
