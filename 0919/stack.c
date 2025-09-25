#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct stack_node *top = NULL; // 스택의 top 초기화

// push 함수 (데이터 삽입)
void push(char data)
{
    struct stack_node *new_node;
    new_node = (struct stack_node *)malloc(sizeof(struct stack_node));
    new_node->data = data;
    new_node->link = top;
    top = new_node;
}

// pop 함수 (데이터 삭제 + 반환)
char pop(void)
{
    struct stack_node *temp;
    char data;

    if (top == NULL)
    {
        printf("스택이 비었습니다!\n");
        return '\0'; // 빈 스택이면 NULL 문자 반환
    }

    data = top->data; // 현재 top의 데이터 저장
    temp = top;       // 현재 top 저장
    top = top->link;  // top을 다음 노드로 이동
    free(temp);       // 기존 top 해제

    return data; // 데이터 반환
}