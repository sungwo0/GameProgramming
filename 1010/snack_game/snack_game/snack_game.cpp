#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>   
#pragma comment(lib, "winmm.lib")

#ifndef getch
#define getch _getch
#endif

#define CAKE_NUMBER 30  // ���� �� ����

#define COL_DEFAULT  (FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
#define COL_BLUE     (FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define COL_GREEN    (FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define COL_RED      (FOREGROUND_RED|FOREGROUND_INTENSITY)
#define COL_YELLOW   (FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY)

void intro_game(void);
void input_participant(char user_name[][8]);
int  game_control(char name[][8], int condition[], int bomb[], int* left, int user, int* start, int* end);
void cake_display(char name[][8], int condition[], int left, int start, int end);
void gotoxy(int x, int y);
void draw_cookie_ascii(int x, int y);
void countdown_start(int seconds);
void place_bombs_random(int bomb[], int n, int count);
void set_color(WORD attr);
void mci_play_mp3(const char* path);
void mci_stop_mp3(void);

int main(void)
{
    int i, start, end, cake_left = CAKE_NUMBER;
    int winner = 0, gameOver = 0;
    int cake_condition[CAKE_NUMBER] = { 0 };
    int bomb_hidden[CAKE_NUMBER] = { 0 };
    char user_name[2][8];

    srand((unsigned)time(NULL));

    // ��ź �� 1~2�� ���� ��ġ(����)
    int bomb_count = 1 + (rand() % 2);
    place_bombs_random(bomb_hidden, CAKE_NUMBER, bomb_count);

    intro_game();
    input_participant(user_name);

    start = 0;
    end = CAKE_NUMBER - 1;

    system("cls");
    (void)game_control(user_name, cake_condition, bomb_hidden, &cake_left, 2, &start, &end); // �ʱ� ǥ�ø�

    gotoxy(10, 12);
    set_color(COL_DEFAULT);
    printf("�ƹ� Ű�� ������ ���� ������ �����մϴ�. ");
    getch();

    // ���� ���� ����
    do {
        for (i = 0; i < 2; i++) {
            system("cls");
            int ret = game_control(user_name, cake_condition, bomb_hidden, &cake_left, i, &start, &end);
            if (ret == 1) {
                gameOver = 1;
                break;
            }
            if (cake_left <= 0) {
                winner = i;
                gameOver = 1;
                break;
            }
            gotoxy(10, 12);
            set_color(COL_DEFAULT);
            printf("�ƹ� Ű�� ������ ���� ������ �����մϴ�. ");
            getch();
        }
    } while (!gameOver && cake_left > 0);

    // ���� ȭ��
    mci_stop_mp3();
    gotoxy(10, 12);
    set_color(COL_YELLOW);
    printf("%s���� �̰���ϴ�.\n", user_name[winner]);
    gotoxy(10, 13);
    set_color(COL_DEFAULT);
    printf("������ �����մϴ�.\n");
    return 0;
}

// ��Ʈ��
void intro_game(void)
{
    system("cls");
    set_color(COL_DEFAULT);
    printf("�ֻ����� ���ڸԱ� ���� \n\n");
    printf("�� ����� ���� �糡�� �ֻ��� ���ڸ�ŭ ���ڸ� �Դ� �����Դϴ�.\n");
    printf("��ź ���ڸ� ������ ��� �й��մϴ�!\n\n");

    draw_cookie_ascii(20, 8);
    countdown_start(3);

    // MP3 ���
    mci_play_mp3("bgm.mp3");
    Sleep(500);
}

// ������ �̸� �Է�
void input_participant(char user_name[][8])
{
    system("cls");
    set_color(COL_DEFAULT);
    printf("1�� ������ �̸�(�ִ� 7��) �Է� �� Enter> ");
    scanf("%7s", user_name[0]);
    printf("2�� ������ �̸�(�ִ� 7��) �Է� �� Enter> ");
    scanf("%7s", user_name[1]);
    printf("�ƹ� Ű�� ������ ������ �����մϴ�...");
    getch();
}

// ���� ����(�� ��)
int game_control(char name[][8], int condition[], int bomb[], int* left, int user, int* s, int* e)
{
    int i, dice_number, available;

    cake_display(name, condition, *left, *s, *e);
    if (user == 2) return 0; // �ʱ� ǥ�ÿ�

    dice_number = rand() % 6 + 1;
    available = (*e - *s + 1);
    if (available < 1) available = 1;
    if (dice_number > available) dice_number = available;

    gotoxy(10, 11);
    set_color(COL_DEFAULT);
    printf("%s���� �ֻ��� ���ڴ� %d�Դϴ�.", name[user], dice_number);

    if (user == 0) { // ���ʺ��� �Ա�
        for (i = 0; i < dice_number && *s <= *e; i++) {
            if (bomb[*s]) { // ��ź�̸� ��� �й� ó��
                bomb[*s] = 0;
                condition[*s] = 2; // ��ź ����(ǥ��)
                (*left)--; if (*left < 0) *left = 0;
                cake_display(name, condition, *left, *s, *e);
                gotoxy(10, 13);
                set_color(COL_YELLOW);
                printf("[!] %s���� ��ź ���ڸ� �Ծ����ϴ�! (�й�)", name[user]);
                return 1;
            }
            if (condition[*s] == 0) {
                condition[*s] = 1;     // �Ϲ� ���� ����
                (*left)--; if (*left < 0) *left = 0;
            }
            (*s)++;
        }
    }
    else { // �����ʺ��� �Ա�
        for (i = 0; i < dice_number && *s <= *e; i++) {
            if (bomb[*e]) {
                bomb[*e] = 0;
                condition[*e] = 2;
                (*left)--; if (*left < 0) *left = 0;
                cake_display(name, condition, *left, *s, *e);
                gotoxy(10, 13);
                set_color(COL_YELLOW);
                printf("[!] %s���� ��ź ���ڸ� �Ծ����ϴ�! (�й�)", name[user]);
                return 1;
            }
            if (condition[*e] == 0) {
                condition[*e] = 1;
                (*left)--; if (*left < 0) *left = 0;
            }
            (*e)--;
        }
    }

    cake_display(name, condition, *left, *s, *e);
    return 0;
}

// ���� �׷���(�÷�)
void cake_display(char name[][8], int condition[], int left, int s, int e)
{
    int i;
    const char* EAT = "[X]";  // ���� ����(�ʷ�)
    const char* NORM = "[ ]";  // ���� ����(�⺻)
    const char* BOOM = "[!]";  // ��ź ���� ����(����)

    gotoxy(30, 5);
    set_color(COL_BLUE);
    if (left < 0) left = 0;
    printf("���� ������ �� : %2d �� ", left);

    set_color(COL_DEFAULT);
    for (i = 0; i < 2; i++) {
        gotoxy(i * 50 + 10, 6);
        printf("%s", name[i]);
    }

    gotoxy(10, 7);
    set_color(COL_GREEN); printf("%s", EAT);
    set_color(COL_DEFAULT); printf("=����  ");
    set_color(COL_RED); printf("%s", BOOM);
    set_color(COL_DEFAULT); printf("=��ź(����)  ");
    printf("%s=����", NORM);

    // ����
    for (i = 0; i < CAKE_NUMBER; i++) {
        gotoxy(10 + i * 3, 9);
        if (condition[i] == 1) {
            set_color(COL_GREEN);
            printf("%s", EAT);
        }
        else if (condition[i] == 2) {
            set_color(COL_RED);
            printf("%s", BOOM);
        }
        else {
            set_color(COL_DEFAULT);
            printf("%s", NORM);
        }
    }

    // ���� ���� ǥ��
    set_color(COL_DEFAULT);
    gotoxy(10, 10);
    printf("���� ���� ��(����): %2d", s);
    gotoxy(52, 10);
    printf("���� ���� ��(������): %2d", (CAKE_NUMBER - 1) - e >= 0 ? (CAKE_NUMBER - 1) - e : 0);
}

// Ŀ�� �̵�
void gotoxy(int x, int y)
{
    COORD Pos = { (SHORT)(x - 1), (SHORT)(y - 1) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// ��Ʈ�� ��Ű ȭ��
void draw_cookie_ascii(int x, int y)
{
    const char* art[] = {
        "        .-\"\"\"\"\"-.        ",
        "      .'  .-\"\"-.  '.      ",
        "     /   /  ..  \\   \\     ",
        "    ;   ;  (..)  ;   ;    ",
        "    |   |   ..   |   |    ",
        "    ;   ;  (  )  ;   ;    ",
        "     \\   \\  ''  /   /     ",
        "      '.  '-..-'  .'      ",
        "        '-.____.-'        ",
    };
    int lines = (int)(sizeof(art) / sizeof(art[0]));
    for (int i = 0; i < lines; i++) {
        gotoxy(x, y + i);
        printf("%s", art[i]);
    }
    gotoxy(x, y + lines + 1);
    set_color(COL_YELLOW);
    printf("���ִ� ��Ű�� �غ�ƾ��!");
    set_color(COL_DEFAULT);
}

// ī��Ʈ�ٿ�
void countdown_start(int seconds)
{
    for (int s = seconds; s > 0; s--) {
        int freq;
        if (s >= 3)      freq = 261;   // C4
        else if (s == 2) freq = 329;   // E4
        else             freq = 392;   // G4

        gotoxy(10, 20);
        set_color(COL_YELLOW);
        printf("�� �����մϴ�... %d  ", s);

        Beep(freq, 180);   // 180ms ���� �︲
        Sleep(820);        // ���� 1�� ���� ���
    }

    gotoxy(10, 20);
    set_color(COL_DEFAULT);
    printf("������ �����մϴ�!     ");
    Beep(523, 200); // C5
    Sleep(500);
}

// ��ź ��ġ(����)
void place_bombs_random(int bomb[], int n, int count)
{
    int placed = 0;
    while (placed < count) {
        int idx = rand() % n;
        if (!bomb[idx]) { bomb[idx] = 1; placed++; }
    }
}

// ���� ����
void set_color(WORD attr)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
}

// bgm ���
void mci_play_mp3(const char* path)
{
    char cmd[512];


    mciSendStringA("stop bgm", NULL, 0, NULL);
    mciSendStringA("close bgm", NULL, 0, NULL);


    _snprintf(cmd, sizeof(cmd), "open \"%s\" type mpegvideo alias bgm", path);
    if (mciSendStringA(cmd, NULL, 0, NULL) != 0) {
        // ���� �� �׳� ����(�Ǵ� Beep �� ���� ����)
        return;
    }

    mciSendStringA("play bgm from 0", NULL, 0, NULL);
}

void mci_stop_mp3(void)
{
    mciSendStringA("stop bgm", NULL, 0, NULL);
    mciSendStringA("close bgm", NULL, 0, NULL);
}
