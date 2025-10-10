<!--
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define cake_number 30  //과자의 개수 

void intro_game(void);
void input_participant(char user_name[][8]);
void game_control(char name[][8], int condition[], int *left, int user, int *start, int *end);
void cake_display(char name[][8], int condition[], int left, int start, int end);
void gotoxy(int x, int y);

int main(void)
{
	int i, start, end, cake_left=cake_number, winner;
	int cake_condition[cake_number]={0};
	char user_name[2][8];
	srand(time(NULL));
   
	intro_game();
	input_participant(user_name);

	start=0;
	end=cake_number-1;

	system("cls");
	game_control(user_name, cake_condition, &cake_left, 2,  &start, &end);  //user의 값을 2로 하여 과자의 초기상태를 출력

	gotoxy(10, 12);
	printf("아무키나 누르면 다음 순서를 진행합니다. ");
	getch();
	do
	{
		for(i=0;i<2;i++)
		{
			system("cls");
			game_control(user_name, cake_condition, &cake_left, i, &start, &end);
			if (cake_left<2)
			{
				winner=i;
				break;
			}
			gotoxy(10, 12);
			printf("아무키나 누르면 다음 순서를 진행합니다. ");
			getch();
		}
	}while(cake_left>2);

	gotoxy(10, 12);
	printf("%s님이 이겼습니다. ", user_name[winner]);
	gotoxy(10, 13);
	printf("게임을 종료합니다. \n");
	return 0;
}

void intro_game(void)
{
	system("cls");
	printf("주사위로 과자먹기 게임 \n\n");
	printf("두사람이 서로 양끝의 주사위 숫자만큼\n");
	printf("과자를 먹는 게임입니다. \n");
	printf("마지막 남은 과자를 먹는 사람이 이깁니다. \n\n");
	printf("아무키나 누르면 게임참가자를\n");
	printf("입력합니다.\n");
	getch();

}

void input_participant(char user_name[][8])
{
	system("cls");
	printf("1번 참가자의 이름을 입력하고 Enter>");
	scanf("%s", user_name[0]);
	printf("2번 참가자의 이름을 입력하고 Enter>");
	scanf("%s", user_name[1]);
	printf("아무키나 누르면 게임을 시작합니다...");
	getch();

}
void game_control(char name[][8], int condition[],  int *left, int user, int *s, int *e)
{
	int i, dice_number;
	cake_display(name, condition, *left, *s, *e);

	if (user==2)
		return;  //user가 2가 되는 경우는 main으로 복귀 
	dice_number=rand()%6+1;  //주사위 난수 생성
	*left-=dice_number;
	gotoxy(10, 11);
        printf("%s님의 주사위 숫자는 %d입니다.",name[user],dice_number); 
			
	if (user==0)
	{
		for(i=*s;i<dice_number+*s;i++)
			condition[i]=1;
		*s+=dice_number;
	}
	else
	{
		for(i=*e;i>(*e-dice_number);i--)
			condition[i]=1;
		*e-=dice_number;
	}
	cake_display(name, condition, *left, *s, *e);
}
void cake_display(char name[][8], int condition[], int left, int s, int e)
{
	int i;
	char *eat_cake="■", *remain_cake="□";

	gotoxy(30,5);
	if (left<0)
		left=0;
	printf("남은 과자의 수 : %2d 개 ", left);

	for(i=0;i<2;i++)
	{
		gotoxy(i*50+10, 6);
		printf("%s", name[i]);
	}

	for(i=0;i<30;i++)
		if (condition[i]==1)
		{
			gotoxy(10+i*2, 8);
			printf("%s", eat_cake);
		}
		else
		{
			gotoxy(10+i*2, 8);
			printf("%s", remain_cake);
		}

	gotoxy(10, 9);
	printf("먹은 과자 수: %2d", s);
	gotoxy(52, 9);
	printf("먹은 과자 수: %2d", 29-e);
}

void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

인트로 화면 쿠키 이미지 표현 후 3초 뒤에 게임 자동 시작
이름 정할 때 픽창 소리 구현(?)
게임 시작 시 포켓몬 대결 소리 또는 인형뽑기 소리 구현
과자는 사용자들이 직접 입력(주사위 대신)
과자를 시각적 강화 / 컬러 출력(남은 과자 수는 파랑, 먹은 과자: 초록, 폭탄: 빨강 등)
폭탄 과자 추가(?)

소스에 대한 설명은 블락 단위로(function 단위)
기존의 소스 분석
인트로 화면에 이미지 표현, 오디오 넣기 등등의 자원을 활용할 것
기존의 텍스트 화면 이미지 화면을 띄운 뒤 3초 뒤에 사라지게 하던지
main 함수의 역활(?)은 이런것이다 이런 소스 분석
기존의 소스 실행한 화면, 내가 업그레이드한 소스 실행한 화면은 ppt에 꼭 있어야함
발표 시간 5분 이내

--!>
