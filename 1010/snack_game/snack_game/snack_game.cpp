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

#define CAKE_NUMBER 30  // 과자 총 개수

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

    // 폭탄 수 1~2개 랜덤 배치(숨김)
    int bomb_count = 1 + (rand() % 2);
    place_bombs_random(bomb_hidden, CAKE_NUMBER, bomb_count);

    intro_game();
    input_participant(user_name);

    start = 0;
    end = CAKE_NUMBER - 1;

    system("cls");
    (void)game_control(user_name, cake_condition, bomb_hidden, &cake_left, 2, &start, &end); // 초기 표시만

    gotoxy(10, 12);
    set_color(COL_DEFAULT);
    printf("아무 키나 누르면 다음 순서를 진행합니다. ");
    getch();

    // 메인 게임 루프
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
            printf("아무 키나 누르면 다음 순서를 진행합니다. ");
            getch();
        }
    } while (!gameOver && cake_left > 0);

    // 종료 화면
    mci_stop_mp3();
    gotoxy(10, 12);
    set_color(COL_YELLOW);
    printf("%s님이 이겼습니다.\n", user_name[winner]);
    gotoxy(10, 13);
    set_color(COL_DEFAULT);
    printf("게임을 종료합니다.\n");
    return 0;
}

// 인트로
void intro_game(void)
{
    system("cls");
    set_color(COL_DEFAULT);
    printf("주사위로 과자먹기 게임 \n\n");
    printf("두 사람이 서로 양끝의 주사위 숫자만큼 과자를 먹는 게임입니다.\n");
    printf("폭탄 과자를 먹으면 즉시 패배합니다!\n\n");

    draw_cookie_ascii(20, 8);
    countdown_start(3);

    // MP3 재생
    mci_play_mp3("bgm.mp3");
    Sleep(500);
}

// 참가자 이름 입력
void input_participant(char user_name[][8])
{
    system("cls");
    set_color(COL_DEFAULT);
    printf("1번 참가자 이름(최대 7자) 입력 후 Enter> ");
    scanf("%7s", user_name[0]);
    printf("2번 참가자 이름(최대 7자) 입력 후 Enter> ");
    scanf("%7s", user_name[1]);
    printf("아무 키나 누르면 게임을 시작합니다...");
    getch();
}

// 게임 진행(한 턴)
int game_control(char name[][8], int condition[], int bomb[], int* left, int user, int* s, int* e)
{
    int i, dice_number, available;

    cake_display(name, condition, *left, *s, *e);
    if (user == 2) return 0; // 초기 표시용

    dice_number = rand() % 6 + 1;
    available = (*e - *s + 1);
    if (available < 1) available = 1;
    if (dice_number > available) dice_number = available;

    gotoxy(10, 11);
    set_color(COL_DEFAULT);
    printf("%s님의 주사위 숫자는 %d입니다.", name[user], dice_number);

    if (user == 0) { // 왼쪽부터 먹기
        for (i = 0; i < dice_number && *s <= *e; i++) {
            if (bomb[*s]) { // 폭탄이면 즉시 패배 처리
                bomb[*s] = 0;
                condition[*s] = 2; // 폭탄 먹힘(표시)
                (*left)--; if (*left < 0) *left = 0;
                cake_display(name, condition, *left, *s, *e);
                gotoxy(10, 13);
                set_color(COL_YELLOW);
                printf("[!] %s님이 폭탄 과자를 먹었습니다! (패배)", name[user]);
                return 1;
            }
            if (condition[*s] == 0) {
                condition[*s] = 1;     // 일반 과자 먹음
                (*left)--; if (*left < 0) *left = 0;
            }
            (*s)++;
        }
    }
    else { // 오른쪽부터 먹기
        for (i = 0; i < dice_number && *s <= *e; i++) {
            if (bomb[*e]) {
                bomb[*e] = 0;
                condition[*e] = 2;
                (*left)--; if (*left < 0) *left = 0;
                cake_display(name, condition, *left, *s, *e);
                gotoxy(10, 13);
                set_color(COL_YELLOW);
                printf("[!] %s님이 폭탄 과자를 먹었습니다! (패배)", name[user]);
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

// 과자 그래픽(컬러)
void cake_display(char name[][8], int condition[], int left, int s, int e)
{
    int i;
    const char* EAT = "[X]";  // 먹은 과자(초록)
    const char* NORM = "[ ]";  // 남은 과자(기본)
    const char* BOOM = "[!]";  // 폭탄 먹힌 과자(빨강)

    gotoxy(30, 5);
    set_color(COL_BLUE);
    if (left < 0) left = 0;
    printf("남은 과자의 수 : %2d 개 ", left);

    set_color(COL_DEFAULT);
    for (i = 0; i < 2; i++) {
        gotoxy(i * 50 + 10, 6);
        printf("%s", name[i]);
    }

    gotoxy(10, 7);
    set_color(COL_GREEN); printf("%s", EAT);
    set_color(COL_DEFAULT); printf("=먹음  ");
    set_color(COL_RED); printf("%s", BOOM);
    set_color(COL_DEFAULT); printf("=폭탄(먹힘)  ");
    printf("%s=남음", NORM);

    // 보드
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

    // 먹은 개수 표기
    set_color(COL_DEFAULT);
    gotoxy(10, 10);
    printf("먹은 과자 수(왼쪽): %2d", s);
    gotoxy(52, 10);
    printf("먹은 과자 수(오른쪽): %2d", (CAKE_NUMBER - 1) - e >= 0 ? (CAKE_NUMBER - 1) - e : 0);
}

// 커서 이동
void gotoxy(int x, int y)
{
    COORD Pos = { (SHORT)(x - 1), (SHORT)(y - 1) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 인트로 쿠키 화면
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
    printf("맛있는 쿠키가 준비됐어요!");
    set_color(COL_DEFAULT);
}

// 카운트다운
void countdown_start(int seconds)
{
    for (int s = seconds; s > 0; s--) {
        int freq;
        if (s >= 3)      freq = 261;   // C4
        else if (s == 2) freq = 329;   // E4
        else             freq = 392;   // G4

        gotoxy(10, 20);
        set_color(COL_YELLOW);
        printf("곧 시작합니다... %d  ", s);

        Beep(freq, 180);   // 180ms 동안 울림
        Sleep(820);        // 남은 1초 동안 대기
    }

    gotoxy(10, 20);
    set_color(COL_DEFAULT);
    printf("게임을 시작합니다!     ");
    Beep(523, 200); // C5
    Sleep(500);
}

// 폭탄 배치(숨김)
void place_bombs_random(int bomb[], int n, int count)
{
    int placed = 0;
    while (placed < count) {
        int idx = rand() % n;
        if (!bomb[idx]) { bomb[idx] = 1; placed++; }
    }
}

// 색상 설정
void set_color(WORD attr)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
}

// bgm 재생
void mci_play_mp3(const char* path)
{
    char cmd[512];


    mciSendStringA("stop bgm", NULL, 0, NULL);
    mciSendStringA("close bgm", NULL, 0, NULL);


    _snprintf(cmd, sizeof(cmd), "open \"%s\" type mpegvideo alias bgm", path);
    if (mciSendStringA(cmd, NULL, 0, NULL) != 0) {
        // 실패 시 그냥 무시(또는 Beep 등 폴백 가능)
        return;
    }

    mciSendStringA("play bgm from 0", NULL, 0, NULL);
}

void mci_stop_mp3(void)
{
    mciSendStringA("stop bgm", NULL, 0, NULL);
    mciSendStringA("close bgm", NULL, 0, NULL);
}
