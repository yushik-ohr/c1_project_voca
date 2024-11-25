#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "vocaList.h"
#include "memcard.h"
#include "ui.h"


// ȭ�� ����� �Լ�
void clearScreen()
{
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Linux/macOS
#endif
}

// �Է��� ��ȿ�ϰ� �ޱ� ���� �Լ�
int getValidInput()
{
    int choice;
    char buffer[100];  // �Է��� ���� ����

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
                return choice;  // ���� ��ȯ ���� �� �� ��ȯ
            }
            else
            {
                // �������� �𸣰ڴµ� ���⼭ ���� ��� �� �ϸ�
                // invalid�� �� �Է� �� �ݺ� ���� exit ó����
                // �׷��� �׳� \n ����
                putchar('\n');
                break;
            }
        }
        else
        {
            // fgets���� ���� �߻� ��
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

    // �޴��� ũ�� (�� ���� �ִ� ����)
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

    // ȭ�� ũ�⸦ ����Ͽ� �߾ӿ� ��ġ
    int screenWidth = 80; // �ܼ� ȭ�� �ʺ� (���� 80 �̻�)
    int screenHeight = 25; // �ܼ� ȭ�� ���� (���� 25 �̻�)

    // �޴��� �߾ӿ� ������ ���
    int startX = (screenWidth - menuWidth) / 2;
    int startY = (screenHeight - menuHeight) / 2;

    // ��� ��� ���
    for (int i = 0; i < screenWidth; i++)
    {
        printf("-");
    }

    printf("\n");

    // �޴� ���� ��� (�߾� ����)
    for (int i = 0; i < menuHeight; i++)
    {
        // ���� ���� ���
        int leftPadding = (screenWidth - menuWidth) / 2;

        // ���� ������ �߰��Ͽ� ���簢�� �ȿ� �ؽ�Ʈ ���
        for (int j = 0; j < leftPadding; j++)
        {
            printf(" ");
        }

        printf("| %s", menu[i]);

        // ������ ������ �߰��Ͽ� ���簢�� ���·� ���߱�
        int rightPadding = screenWidth - leftPadding - strlen(menu[i]) - 2; // �� �� '|' ����
        for (int j = 0; j < rightPadding; j++)
        {
            printf(" ");
        }

        printf("|\n");
    }

    // �ϴ� ��� ���
    for (int i = 0; i < screenWidth; i++)
    {
        printf("-");
    }

    printf("\n");

    printf("\nEnter the number (1~9, 100~102, or 0 to Exit): ");
}

// �޴� ��� �Լ�
//void printMenu()
//{
//    // ȭ���� �ʱ�ȭ�ϰ� �޴� ���
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

// �޴� ���� �Լ�
void selectMenu()
{
    int choice;
    do
    {
        printMenu();

        // ��ȿ�� �Է��� ���� ������ �ݺ�
        choice = getValidInput();

        switch (choice)
        {
        case 1:
            clearScreen();
            printShuffledLinkedList(head, 1);  // �������� ���ĵ� ��ü ����
            printf("\nEnter any key to return to menu...");
            getch();  // Ű �Է� ���
            break;
        case 2:
            clearScreen();
            printShuffledLinkedList(head, 2);  // �������� ���ĵ� ���ܾ� ����
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 3:
            clearScreen();
            printShuffledLinkedList(head, 3);  // �������� ���ĵ� �ǹ� ����
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 4:
            clearScreen();
            printLinkedList(sortedHead, 1);  // ���ĺ� ������ ���ĵ� ��ü ����
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 5:
            clearScreen();
            printLinkedList(sortedHead, 2);  // ���ĺ� ������ ���ĵ� ���ܾ� ����
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 6:
            clearScreen();
            printLinkedList(sortedHead, 3);  // ���ĺ� ������ ���ĵ� �ǹ� ����
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 7:
            clearScreen();
            printLinkedList(head, 1);  // ��ü �ܾ�� �ǹ� ����
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 8:
            clearScreen();
            printLinkedList(head, 2);  // ���ܾ ����
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 9:
            clearScreen();
            printLinkedList(head, 3);  // �ǹ̸� ����
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 100:
            startMemoryCardGame(head, 1);  // ������ �� ���
            break;
        case 101:
            startMemoryCardGame(head, 2);  // ���ĺ� �� ���
            break;
        case 102:
            startMemoryCardGame(head, 3);  // ����� ���� �� ���
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
