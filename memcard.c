#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "vocaList.h"
#include "memcard.h"
#include "ui.h"


void startMemoryCardGame(LinkedList* head, const int mode)
{
    reviewCompleted = 0;
    
    if (head == NULL)
    {
        printf("\nNo more words to study.\n");
        return;
    }

    int remaining = 0;
    LinkedList* current = head;

    // 단어 수 계산
    while (current != NULL)
    {
        remaining++;
        current = current->pNext;
    }

    current = head;

    // 'Don't Know'를 선택한 단어들을 담을 리스트
    LinkedList* reviewListHead = NULL;
    LinkedList* reviewListTail = NULL;

    int count = remaining;
    LinkedList** nodes = (LinkedList**)malloc(count * sizeof(LinkedList*));
    int listSize = 0;

    while (current != NULL)
    {
        nodes[listSize++] = current;
        current = current->pNext;
    }

    if (mode == 1)
    {
        // 무작위 순
        srand((unsigned int)time(NULL));
        for (int i = 0; i < count; i++)
        {
            int j = rand() % count;
            LinkedList* temp = nodes[i];
            nodes[i] = nodes[j];
            nodes[j] = temp;
        }
    }
    else if (mode == 2)
    {
        // 알파벳 순
        qsort(nodes, count, sizeof(LinkedList*), compareVoca);
    }

    current = nodes[0];
    reviewListHead = memoryCardRecursion(mode, count, remaining, nodes, current, reviewListHead, reviewListTail);
    free(nodes);

    // 한 게임이 끝났을 때 메시지 출력
    printf("\nYou have been checked all words.\n");

    // 'Don't Know'를 선택한 단어가 있을 경우 복습 여부 확인
    if (reviewCompleted == 0)  // 복습이 완료되지 않았을 때만 물어보기
    {
        checkIfReview(reviewListHead, mode);
    }
}

LinkedList* memoryCardRecursion(const int mode, const int count, int remaining,
    LinkedList** nodes, LinkedList* current, LinkedList* reviewListHead, LinkedList* reviewListTail)
{
    int i = 0;
    const char* modeText = 0;
    if (mode == 1)
    {
        modeText = "RANDOM";
    }
    else if (mode == 2)
    {
        modeText = "ALPHABET";
    }
    else
    {
        modeText = "CUSTOM";
    }

    while (i < count)
    {
        clearScreen();
        printf("---Memory Card game [%s]---\n", modeText);
        printf("Remaining: [ %d ]\n\n", remaining);

        printf("%s\n", nodes[i]->pVocaData->voca);
        printf("\n1. Know\n");
        printf("2. Don't Know\n\n");
        printf("Enter 1/2: ");

        const int choice = getValidInput();

        if (choice == 1)
        {
            printf("\nMeaning: %s\n", nodes[i]->pVocaData->mean);
        }
        else if (choice == 2)
        {
            printf("\nMeaning: %s\n", nodes[i]->pVocaData->mean);

            // 'Don't Know'를 선택한 단어를 복습 리스트에 추가
            LinkedList* newNode = createNode(nodes[i]->pVocaData->voca, nodes[i]->pVocaData->mean);
            if (reviewListHead == NULL)
            {
                reviewListHead = reviewListTail = newNode;
            }
            else
            {
                reviewListTail->pNext = newNode;
                newNode->pPrev = reviewListTail;
                reviewListTail = newNode;
            }
        }
        else
        {
            printf("Invalid input. Please enter a vaild number.\n");
            getch();
            continue;
        }
        remaining--;  // 남은 단어 수를 감소

        // 사용자 입력을 기다리고 다음 카드로 넘어가기
        printf("\nEnter any key to next!");
        getch();
        i++;
    }
    
    return reviewListHead;
}

const int countReviewList(LinkedList* reviewListHead)
{
    int count = 0;
    while (reviewListHead != NULL)
    {
        count++;
        reviewListHead = reviewListHead->pNext;
    }
    return count;
}

void checkIfReview(LinkedList* reviewListHead, const int mode)
{
    if (reviewListHead != NULL)  // 'Don't Know' 리스트에 단어가 있으면 복습 여부 확인
    {
        const int cntDontKnow = countReviewList(reviewListHead);

        while (1)
        {
            clearScreen();
            printf("[ %d ] words you select 'Don't Know'.\n\n", cntDontKnow);
            printf("Do you want to review 'Don't Know' words?\n\n");
            printf("YES:\tEnter '1'\n");
            printf("NO:\tEnter '2'\n\n");
            printf("Enter 1/2: ");

            const int reviewChoice = getValidInput();

            if (reviewChoice == 1)
            {
                // 재복습 게임 시작
                startMemoryCardGame(reviewListHead, mode);  // 재귀적으로 복습 진행
                break;
            }
            else if (reviewChoice == 2)
            {
                printf("\nReview Over!");
                reviewCompleted = 1;  // 복습을 하지 않으므로 플래그 설정
                getch();
                break;
            }
            else
            {
                printf("Invalid input. Press any key to try again...\n");
                getch();
                continue;
            }
        }
    }
    else
    {
        printf("\nNo words to review.\n");
        reviewCompleted = 1;  // 복습할 단어가 없으므로 플래그 설정
        getch();
    }
}
