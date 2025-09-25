#include <stdio.h>
#include "stack.h"

int main(void)
{
    int count = 0;
    char key;

    // 데이터 입력
    do
    {
        count++;
        printf("%2d 번째 문자 입력 > ", count);
        key = getchar();
        getchar(); // 엔터 처리

        push(key);
        printf("%c 입력됨\n", key);

    } while (key != 27); // ESC(27) 입력 시 종료

    printf("\n데이터 pop 과정\n");

    // pop 하면서 출력
    while (top != NULL)
    {
        key = pop();
        printf("%c ", key);
    }

    printf("\n");
    return 0;
}