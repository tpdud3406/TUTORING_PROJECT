#include<stdio.h>
/************************************************
 * calender.c에 필요한 헤더파일들은 현재 파일에 선언
 * calender.c에 구현될 함수들의 원형(proto type)은 현재 파일에 선언
 * 구조체 및 DEFINE 메크로도 현재 파일에 선언
 * ************************************************/

typedef struct Calender {
    int year;
    int month;
    int day;
    char content[100];
} Calender;

void calender(void);
void input_schedule(void);
void delete_schedule(void);
void view_schedule(void);
int schedule_bool(void);
void schedule_sub_delete(Calender input);