#include <stdio.h>
#include <windows.h>
#include "sound.h"

int main(void)
{
    // 도레미파솔라시도 (C D E F G A B C) → 반음 간격
    int index[8] = {0, 2, 4, 5, 7, 9, 11, 12};
    int freq[8];
    int i;

    // 4옥타브 기준 음계 주파수 계산
    for (i = 0; i < 8; i++)
    {
        freq[i] = calc_frequency(4, index[i]);
    }

    // 도레미파솔라시도 순서대로 출력
    for (i = 0; i < 8; i++)
    {
        Beep(freq[i], 500);
    }

    Sleep(1000); // 1초 대기

    // 역순으로 도시라솔파미레도 출력
    for (i = 7; i >= 0; i--)
    {
        Beep(freq[i], 500);
    }

    return 0;
}