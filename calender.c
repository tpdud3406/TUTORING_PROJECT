#include "calender.h"
#include <stdlib.h> // 메모리 할당 (malloc, free), sleep
#include <string.h> // strcmp, strcat
#define MAX_INDEX 400
//스케줄 관리 프로그램의 작동 로직은 calender.c에서 구현한다.

int ch_cnt = 0;

/************** 일정 관리 실행 함수 *****************/
void calender(void){
    LinkedList *p = (LinkedList *)malloc(sizeof(LinkedList)); // 헤더 포인터 
    p->head = NULL;

    printf("it is calender.c\n");
    int n;

    while (1) {
        printf("1.스케줄 입력\n2.스케줄 삭제\n3.스케줄 보기\n4.Main menu\n5.프로그램 종료\n");
        printf("메뉴: ");
        scanf(" %d", &n);

        if (n == 5) {
            system("clear");
            break;
        }
        else {
            switch (n) {
            case 1:
                input_schedule(p);
                break;
            case 2:
                delete_schedule(p);
                break;   
            /*
            case 3:
                view_schedule();
                break;
            */
            case 4:
                system("clear");
                break;
            }
        }
    }
    // 갯수 확인 test
    printf("%d\n", ch_cnt);
    return;
}

/***************** 일정 입력 함수 ********************/
/* 입력한 날에 일정이 있으면 추가할 것인지 덮어쓸 것인지 확인
추가할 경우 문자열을 연결, 덮어쓸 경우 해당 일정 삭제 후 덮어쓰기
입력 시 자동으로 정렬되어있음
이후 화면 clear */
void input_schedule(LinkedList *p){
    Node *newNode = (Node *)malloc(sizeof(Node));
    char str1[] = "Yes";

    printf("입력: ");
    scanf(" %d %d %d %s", &newNode->year, &newNode->month, &newNode->day, newNode->content);
    printf("출력: %d 년 %d 월 %d 일 %s \n", newNode->year, newNode->month, newNode->day, newNode->content);

    if (schedule_day_check(p, newNode)){ // 일정이 있으면
        char n[5];
        printf("출력: %d 년 %d 월 %d 일에 일정이 있습니다.\n", newNode->year, newNode->month, newNode->day);
        printf("일정을 추가하려면 Yes를, 덮어쓰려면 No를 입력하세요: ");
        scanf(" %s", n);

        // 비교한 두 문자가 같으면 0 반환 -> else(일정 추가), 다르면 1 반환 -> if(덮어 쓰기)
        if (strcmp(n, str1)){ // 덮어 쓰기
            Delete_Node(p, newNode);
            Append_Node(p, newNode);
            printf("일정을 추가하였습니다.\n");
        }
        else{ // 일정 추가
            Append_Node(p, newNode);
            ch_cnt++;
            printf("일정을 추가하였습니다.\n");
        }
        printf("아무 키나 입력하세요...\n");
        getchar();
        return;
    }
    else{ // 일정이 없으면
        Append_Node(p, newNode);
        ch_cnt++;
        printf("일정을 추가하였습니다.\n");
        printf("아무 키나 입력하세요...\n");
        getchar();
        return;
    }
}

/********** 해당일에 일정이 있는지 없는지 확인하는 함수(1) - 날짜만 확인 *********/
// 일정이 있으면 1 출력, 없으면 0 출력
int schedule_day_check(LinkedList *p, Node *newNode){
    Node *cur;
    cur = p->head;
    while(cur != NULL){
        // 일정이 있으면
        printf("%d %d \n", cur->day, newNode->day);
        if((cur->year == newNode->year) &&(cur->month == newNode->month) && (cur->day == newNode->day)) return 1; 
        cur = cur->next;
    }
    return 0;
}

/********** 해당일에 일정이 있는지 없는지 확인하는 함수(2) - 날짜 && 내용 확인 *********/
// 일정이 있으면 1 출력, 없으면 0 출력
int schedule_content_check(LinkedList *p, Node *newNode){
    Node *cur;
    cur = p->head;
    while(cur->next != NULL){
        // 일정이 있으면
        if((cur->year == newNode->year) &&(cur->month == newNode->month) &&(cur->day == newNode->day) && (strcmp(cur->content, newNode->content) == 0)) return 1; 
        cur = cur->next;
    }
    return 0;
}

/***************** 일정 삭제 Main 함수 ********************/
/* 일정이 있을 경우 해당 일정 삭제, 일정이 없을 경우 일정이 없다고 출력*/
// 해당 일정만 삭제 해야함. 
void delete_schedule(LinkedList *p){
    Node *newNode = (Node *)malloc(sizeof(Node));

    Node *cur;
    cur = p->head;

    printf("입력: ");
    scanf(" %d %d %d %s", &newNode->year, &newNode->month, &newNode->day, newNode->content);
    
    // 일정이 있으면 해당 일정 삭제
    while(cur->next != NULL){
        if(schedule_content_check(p, newNode)){ 
            printf("%d 년 %d 월 %d 일에 일정이 있습니다.\n", newNode->year, newNode->month, newNode->day);
            Delete_Node(p, newNode);
            printf("일정을 삭제하였습니다.\n");
            ch_cnt--;
            break;
        }
        cur = cur->next;
    }
    // 일정이 없으면(끝까지 다 돌았다면)
    if(cur == NULL){
        printf("%d 년 %d 월 %d 일에 일정이 없습니다.\n", newNode->year, newNode->month, newNode->day);
    }

    printf("아무 키나 입력하세요...\n");
    getchar();
    return;
}

/***************** 윤년 check 함수 ********************/
/*
int year_check(int year){
    if((year % 4 == 0) && (year % 100 != 0) && (year % 400 == 0)) return 1;
    else return 0;
}
/*****************************************************************/
/************************** LinkedList ***************************/
/*****************************************************************/

/**** List의 마지막에 새로운 Node 추가 ****/
// 입력시 자동으로 정렬되어 있음
void Append_Node(LinkedList *p, Node *newNode){
    // 처음 삽입되는 노드라면 (더미노드 없기때문에 조건 달리 지정)
    if(p->head ==  NULL){
        p->head = newNode;
    }
    else { // 처음 삽입되는 노드가 아니라면
        Node *cur;
        cur = p->head;


        //////////////////////////////////////// 오류 !!!!!!!!!!!!!!!!
        // 정렬하면서 연결
        while(cur->next != NULL){
            // 년도 비교    
            if(cur->next->year > newNode->year) { // 년도 다름
                printf("%d %d\n", cur->day, newNode->day);
                cur->next = newNode;
                newNode->next = cur->next;
                break;
            }
            else if(cur->year == newNode->year && cur->next->month > newNode->month){ // 년도 동일, 달 다름
                printf("%d %d\n", cur->day, newNode->day);
                newNode->next = cur->next;
                cur->next = newNode;
                break;
            }
            else if(cur->year == newNode->year &&cur->month == newNode->month &&cur->day == newNode->day && cur->next->day > newNode->day){ // 년도 동일, 달 동일, 일 다름
                printf("%d %d\n", cur->day, newNode->day);
                cur->next = newNode;
                newNode->next = cur->next->next;
                break;
            }
            else cur = cur->next;
        }
        // 새로 저장할 노드의 날짜가 가장 크다면 연결리스트 마지막에 연결
        if(cur->next == NULL)
            cur->next = newNode;

    }
    return;
} 

/************** Node 삭제 *********************/
void Delete_Node(LinkedList *p, Node *newNode){
    Node *cur; 
    cur = p->head;

    while(cur->next->next != NULL){
        // 노드를 찾으면
        if((cur->year == newNode->year) &&(cur->month == newNode->month) &&(cur->day == newNode->day) && (strcmp(cur->next->content, newNode->content) == 0)){ 
            cur->next = cur->next->next;
            return;
        }
        cur = cur->next;
    }
    return;
}

/**** List에 있는 모든 Node를 head부터 순서대로 출력
ex) 4,3,5 => "4 3 5"  ****/
/*
void Print(Node *head){
    if(head == NULL){
        printf("노드가 존재하지 않습니다.\n");
        return;
    }
    Node *cur = (Node *)mallloc(sizeof(Node));
    cur = head;
    while(cur->next != NULL){
        printf("%5s", cur->content);
        cur = cur->next;
    }
    printf("\n");
    return;
}
*/