#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "vocaList.h"
#include "memcard.h"
#include "ui.h"


// 화면 지우기 함수
void clearScreen()
{
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Linux/macOS
#endif
}

// 입력을 유효하게 받기 위한 함수
int getValidInput()
{
    int choice;
    char buffer[100];  // 입력을 받을 버퍼

    while (1)
    {

        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';

            if (buffer[0] == '\0')
            {
                putchar('\n');
                break;
            }

            if (sscanf(buffer, "%d", &choice) == 1)
            {
                putchar('\n');
                return choice;  // 정수 변환 성공 시 값 반환
            }
            else
            {
                // 왜인지는 모르겠는데 여기서 뭐라도 출력 안 하면
                // invalid한 값 입력 시 반복 없이 exit 처리됨
                // 그래서 그냥 \n 넣음
                putchar('\n');
                break;
            }
        }
        else
        {
            // fgets에서 오류 발생 시
            printf("Error reading input. Please try again.\n");
            break;
        }
    }
}

void printMenu()
{
    clearScreen();

    const char* menu[] =
    {
        "Welcome to Voca!",
        "",
        "---[RANDOM]---",
        "1. Whole",
        "2. Voca Only",
        "3. Meaning Only",
        "",
        "---[ALPHABET]---",
        "4. Whole",
        "5. Voca Only",
        "6. Meaning Only",
        "",
        "---[CUSTOM]---",
        "7. Whole",
        "8. Voca Only",
        "9. Meaning Only",
        "",
        "100. Memory Card game [RANDOM]",
        "101. Memory Card game [ALPHABET]",
        "102. Memory Card game [CUSTOM]",
        "",
        "0. EXIT",
    };

    // 메뉴의 크기 (줄 수와 최대 길이)
    int menuHeight = sizeof(menu) / sizeof(menu[0]);
    int menuWidth = 0;

    for (int i = 0; i < menuHeight; i++)
    {
        int len = strlen(menu[i]);

        if (len > menuWidth)
        {
            menuWidth = len;
        }
    }

    // 화면 크기를 고려하여 중앙에 배치
    int screenWidth = 80; // 콘솔 화면 너비 (보통 80 이상)
    int screenHeight = 25; // 콘솔 화면 높이 (보통 25 이상)

    // 메뉴가 중앙에 오도록 계산
    int startX = (screenWidth - menuWidth) / 2;
    int startY = (screenHeight - menuHeight) / 2;

    // 상단 경계 출력
    for (int i = 0; i < screenWidth; i++)
    {
        printf("-");
    }

    printf("\n");

    // 메뉴 내용 출력 (중앙 정렬)
    for (int i = 0; i < menuHeight; i++)
    {
        // 왼쪽 여백 계산
        int leftPadding = (screenWidth - menuWidth) / 2;

        // 왼쪽 여백을 추가하여 직사각형 안에 텍스트 출력
        for (int j = 0; j < leftPadding; j++)
        {
            printf(" ");
        }

        printf("| %s", menu[i]);

        // 오른쪽 여백을 추가하여 직사각형 형태로 맞추기
        int rightPadding = screenWidth - leftPadding - strlen(menu[i]) - 2; // 양 옆 '|' 제외
        for (int j = 0; j < rightPadding; j++)
        {
            printf(" ");
        }

        printf("|\n");
    }

    // 하단 경계 출력
    for (int i = 0; i < screenWidth; i++)
    {
        printf("-");
    }

    printf("\n");

    printf("\nEnter the number (1~9, 100~102, or 0 to Exit): ");
}

// 메뉴 출력 함수
//void printMenu()
//{
//    // 화면을 초기화하고 메뉴 출력
//    clearScreen();
//    printf("\n---[Welome to Voca]---\n");
//
//    printf("\n---[RANDOM]---\n");
//    printf("1. Whole\n");
//    printf("2. Voca Only\n");
//    printf("3. Meaning Only\n");
//
//    printf("\n---[ALPHABET]---\n");
//    printf("4. Whole\n");
//    printf("5. Voca Only\n");
//    printf("6. Meaning Only\n");
//
//    printf("\n---[CUSTOM]---\n");
//    printf("7. Whole\n");
//    printf("8. Voca Only\n");
//    printf("9. Meaning Only\n");
//
//    printf("\n100. Memory Card game [RANDOM]\n");
//    printf("101. Memory Card game [ALPHABET]\n");
//    printf("102. Memory Card game [CUSTOM]\n");
//    printf("\n0. EXIT\n");
//    printf("\nEnter the number (1~9, 100~102, or 0): ");
//}

// 메뉴 선택 함수
void selectMenu()
{
    int choice;
    do
    {
        printMenu();

        // 유효한 입력을 받을 때까지 반복
        choice = getValidInput();

        switch (choice)
        {
        case 1:
            clearScreen();
            printShuffledLinkedList(head, 1);  // 무작위로 정렬된 전체 보기
            printf("\nEnter any key to return to menu...");
            getch();  // 키 입력 대기
            break;
        case 2:
            clearScreen();
            printShuffledLinkedList(head, 2);  // 무작위로 정렬된 영단어 보기
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 3:
            clearScreen();
            printShuffledLinkedList(head, 3);  // 무작위로 정렬된 의미 보기
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 4:
            clearScreen();
            printLinkedList(sortedHead, 1);  // 알파벳 순으로 정렬된 전체 보기
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 5:
            clearScreen();
            printLinkedList(sortedHead, 2);  // 알파벳 순으로 정렬된 영단어 보기
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 6:
            clearScreen();
            printLinkedList(sortedHead, 3);  // 알파벳 순으로 정렬된 의미 보기
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 7:
            clearScreen();
            printLinkedList(head, 1);  // 전체 단어와 의미 보기
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 8:
            clearScreen();
            printLinkedList(head, 2);  // 영단어만 보기
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 9:
            clearScreen();
            printLinkedList(head, 3);  // 의미만 보기
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 100:
            startMemoryCardGame(head, 1);  // 무작위 순 모드
            break;
        case 101:
            startMemoryCardGame(head, 2);  // 알파벳 순 모드
            break;
        case 102:
            startMemoryCardGame(head, 3);  // 사용자 정의 순 모드
            break;
        case 0:
            printf("Exit!\n");
            break;
        default:
            printf("Invalid input. Press any key to try again...\n");
            getch();
            break;
        }
    } while (choice != 0);
}
