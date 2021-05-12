#include<stdio.h>

typedef struct Node {
    int data;
    Node *next;
    Node *prev;
} Node;

typedef struct LinkedList {
    Node *head;
    Node *tail;
    int numofData;
} List;

void Append(int data); // list의 마지막에 새로운 data에 대한 Node 추가
void Prepend(int data); // list의 처음에 새로운 data에 대한 Node 추가
int Length(void); // list에 있는 Node의 수를 return
void Print(void); // 앞에서부터 출력
void PrintReverse(void); // 뒤에서부터 출력