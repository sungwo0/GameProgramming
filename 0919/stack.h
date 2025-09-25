#ifndef STACK_H
#define STACK_H

// 스택 노드 구조체 정의
struct stack_node
{
    char data;
    struct stack_node *link;
};

// 전역 변수 (스택 top 포인터)
extern struct stack_node *top;

// 스택 연산 함수 원형
void push(char data);
char pop(void);

#endif