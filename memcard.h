#pragma once

// 복습 완료 여부를 추적하는 전역 변수
int reviewCompleted;

void startMemoryCardGame(LinkedList* head, const int mode);

LinkedList* memoryCardRecursion(const int mode, const int count, int remaining,
    LinkedList** nodes, LinkedList* current, LinkedList* reviewListHead, LinkedList* reviewListTail);

const int countReviewList(LinkedList* reviewListHead);

void checkIfReview(LinkedList* reviewListHead, const int mode);
