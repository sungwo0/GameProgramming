#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "sound.h"

// 옥타브와 음계 인덱스를 받아 주파수 계산하는 함수
int calc_frequency(int octave, int inx)
{
    double do_scale = 32.7032;           // C1 기준 주파수
    double ratio = pow(2.0, 1.0 / 12.0); // 12 평균율 비율
    double temp = do_scale * pow(2, octave - 1);
    int i;

    for (i = 0; i < inx; i++)
    {
        temp *= ratio; // 반음씩 증가
    }

    return (int)(temp + 0.5); // 반올림 후 정수 반환
}