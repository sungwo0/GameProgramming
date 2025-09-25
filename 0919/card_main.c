#include <stdio.h>
#include "card.h"

int main(void)
{
    struct trump card[52];

    make_card(card);
    printf("=== 카드 생성 후 출력 ===\n");
    display_card(card);

    shuffle_card(card);
    printf("\n=== 카드 섞은 후 출력 ===\n");
    display_card(card);

    return 0;
}