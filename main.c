#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "vocaList.h"
#include "memcard.h"
#include "ui.h"

LinkedList* head = NULL;         // 원본 리스트
LinkedList* sortedHead = NULL;   // 정렬된 리스트

// 단어와 의미가 저장된 파일 이름
const char* filename = "vocabulary.txt";

int main(void)
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    initList();
    selectMenu();

    // LinkedList 메모리 해제
    freeLinkedList(head);
    freeLinkedList(sortedHead);

    return 0;
}
