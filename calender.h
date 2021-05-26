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
    struct Node *prev;
} Node;


//날짜순으로
void Append_Node(Node *newNode); // list의 마지막에 새로운 data에 대한 Node 추가
void Delete_Node(Node *newNode); // 노드 삭제
void Print(void); // 앞에서부터 출력
int total_days(Node *newNode, Node *cur);

/*************** 달력 프로그램 **************/
void calender(void);
void input_schedule(void);
void delete_schedule(void);
int schedule_day_check(Node *newNode);
int schedule_content_check( Node *newNode);
int year_check(int i);