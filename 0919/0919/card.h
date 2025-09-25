#ifndef CARD_H
#define CARD_H

struct trump
{
    int order;      // 카드 순서
    char shape[3];  // 카드 모양 (♠, ◆, ♥, ♣)
    char number[3]; // 카드 숫자 or 문자 (A, 2~10, J, Q, K)
};

// 카드 생성
void make_card(struct trump m_card[]);

// 카드 출력
void display_card(struct trump m_card[]);

// 카드 섞기
void shuffle_card(struct trump m_card[]);

#endif