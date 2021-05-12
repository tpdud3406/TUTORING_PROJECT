#include<stdio.h>
/************************************************
 * calender.c에 필요한 헤더파일들은 현재 파일에 선언
 * calender.c에 구현될 함수들의 원형(proto type)은 현재 파일에 선언
 * 구조체 및 DEFINE 메크로도 현재 파일에 선언
 * ************************************************/

/**************** LinkedList ***************/
typedef struct{
    int year;
    int month;
    int day;
    char content[100];
    Node *next;
} Node;

//날짜순으로
void Append(Node *head, int year, int month, int day, char content[]); // list의 마지막에 새로운 data에 대한 Node 추가
void Delete(Node * head, int year, int month, int day, char content[]); // list의 처음에 새로운 data에 대한 Node 추가
int Length(Node *head); // list에 있는 Node의 수를 return
void Print(Node *head); // 앞에서부터 출력


/*************** 달력 프로그램 **************/
/*
typedef struct Calender {
    int year;
    int month;
    int day;
    char content[100];
} Calender;
*/
void calender(void);
void input_schedule(void);
void delete_schedule(void);
void view_schedule(void);
int schedule_bool(Node *input);
void schedule_sub_delete(Node *input);
int year_check(int i);