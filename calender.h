#include<stdio.h>
/************************************************
 * calender.c에 필요한 헤더파일들은 현재 파일에 선언
 * calender.c에 구현될 함수들의 원형(proto type)은 현재 파일에 선언
 * 구조체 및 DEFINE 메크로도 현재 파일에 선언
 * ************************************************/

/**************** LinkedList ***************/
typedef struct Node{
    int year;
    int month;
    int day;
    char content[100];
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
} LinkedList;

//날짜순으로
void Append_Node(LinkedList *p, Node *newNode); // list의 마지막에 새로운 data에 대한 Node 추가
void Delete_Node(LinkedList *p, Node *newNode); // 노드 삭제
void Print(Node *head); // 앞에서부터 출력


/*************** 달력 프로그램 **************/
void calender(void);
void input_schedule(LinkedList *p);
void delete_schedule(LinkedList *p);
void view_schedule(void);
int schedule_day_check(LinkedList *p, Node *newNode);
int schedule_content_check(LinkedList *p, Node *newNode);
int year_check(int i);