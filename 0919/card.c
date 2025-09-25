#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "card.h"

// 카드 생성 함수
void make_card(struct trump m_card[])
{
    int i, j;
    char shape[4][3] = {"♠", "◆", "♥", "♣"};

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 13; j++)
        {
            int idx = i * 13 + j;
            m_card[idx].order = i;
            strcpy(m_card[idx].shape, shape[i]);

            // 숫자 / 문자 구분
            switch (j + 1)
            {
            case 1:
                strcpy(m_card[idx].number, "A");
                break;
            case 11:
                strcpy(m_card[idx].number, "J");
                break;
            case 12:
                strcpy(m_card[idx].number, "Q");
                break;
            case 13:
                strcpy(m_card[idx].number, "K");
                break;
            default:
                sprintf(m_card[idx].number, "%d", j + 1);
            }
        }
    }
}

// 카드 출력 함수
void display_card(struct trump m_card[])
{
    int i, count = 0;

    for (i = 0; i < 52; i++)
    {
        printf("%s%2s ", m_card[i].shape, m_card[i].number);

        count++;
        if (count == 13)
        {
            printf("\n");
            count = 0;
        }
    }
}

// 카드 섞기 함수
void shuffle_card(struct trump m_card[])
{
    int i, rnd;
    struct trump temp;

    srand(time(NULL)); // 난수 초기화

    for (i = 0; i < 52; i++)
    {
        rnd = rand() % 52;
        temp = m_card[rnd];
        m_card[rnd] = m_card[i];
        m_card[i] = temp;
    }
}