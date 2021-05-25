#include "calender.h"
#include <stdlib.h> // 메모리 할당 (malloc, free), sleep
#include <string.h> // strcmp, strcat
#define MAX_INDEX 400
//스케줄 관리 프로그램의 작동 로직은 calender.c에서 구현한다.

int ch_cnt = 0;
Node *head;

/************** 일정 관리 실행 함수 *****************/
void calender(void){

    printf("it is calender.c\n");
    int n;

    while (1) {
        printf("1.스케줄 입력\n2.스케줄 삭제\n3.스케줄 보기\n4.Main menu\n5.프로그램 종료\n");
        printf("메뉴: ");
        scanf(" %d", &n);
        getchar();

        if (n == 5) {
            system("clear");
            break;
        }
        else {
            switch (n) {
            case 1:
                input_schedule();
                break;
            case 2:
                delete_schedule();
                break;   
            case 3:
                Print();
                break;
            case 4:
                system("clear");
                break;
            }
        }
        Print();
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
void input_schedule(void){
    Node *newNode = (Node *)malloc(sizeof(Node));
    char str1[] = "Yes";

    printf("입력: ");
    scanf(" %d %d %d %s", &newNode->year, &newNode->month, &newNode->day, newNode->content);
    getchar();
    printf("출력: %d 년 %d 월 %d 일 %s \n", newNode->year, newNode->month, newNode->day, newNode->content);

    if (schedule_day_check(newNode)){ // 일정이 있으면
        char n[5];
        printf("출력: %d 년 %d 월 %d 일에 일정이 있습니다.\n", newNode->year, newNode->month, newNode->day);
        printf("일정을 추가하려면 Yes를, 덮어쓰려면 No를 입력하세요: ");
        scanf(" %s", n);

        // 비교한 두 문자가 같으면 0 반환 -> else(일정 추가), 다르면 1 반환 -> if(덮어 쓰기)
        if (strcmp(n, str1)){ // 덮어 쓰기
            Delete_Node(newNode);
            Append_Node(newNode);
            printf("일정을 추가하였습니다.\n");
        }
        else{ // 일정 추가
            Append_Node(newNode);
            ch_cnt++;
            printf("일정을 추가하였습니다.\n");
        }
        printf("아무 키나 입력하세요...\n");
        getchar();
        return;
    }
    else{ // 일정이 없으면
        Append_Node(newNode);
        ch_cnt++;
        printf("일정을 추가하였습니다.\n");
        printf("아무 키나 입력하세요...\n");
        getchar();
        return;
    }
}

/********** 해당일에 일정이 있는지 없는지 확인하는 함수(1) - 날짜만 확인 *********/
// 일정이 있으면 1 출력, 없으면 0 출력
int schedule_day_check(Node *newNode){
    Node *cur;
    cur = head;
    while(cur != NULL){
        // 일정이 있으면
        if((cur->year == newNode->year) &&(cur->month == newNode->month) && (cur->day == newNode->day)) return 1; 
        cur = cur->next;
    }
    return 0;
}

/********** 해당일에 일정이 있는지 없는지 확인하는 함수(2) - 날짜 && 내용 확인 *********/
// 일정이 있으면 1 출력, 없으면 0 출력
int schedule_content_check(Node *newNode){
    Node *cur;
    cur = head;
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
void delete_schedule(void){
    Node *newNode = (Node *)malloc(sizeof(Node));
    Node *cur;
    cur = head;

    printf("입력: ");
    scanf(" %d %d %d %s", &newNode->year, &newNode->month, &newNode->day, newNode->content);
    
    // 일정이 있으면 해당 일정 삭제
    while(cur->next != NULL){
        if(schedule_content_check(newNode)){ 
            printf("%d 년 %d 월 %d 일에 일정이 있습니다.\n", newNode->year, newNode->month, newNode->day);
            Delete_Node(newNode);
            printf("일정을 삭제하였습니다.\n");
            ch_cnt--;
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
void Append_Node(Node *newNode){
    // 처음 삽입되는 노드라면 (더미노드 없기때문에 조건 달리 지정)
    if(head ==  NULL){
        head = newNode;
    }
    else { // 처음 삽입되는 노드가 아니라면
        Node *cur;
        cur = head;

        // 정렬하면서 연결
        while(cur != NULL){
            printf("is checking now\n");
            printf("cur : %d %d %d %s\n", cur->year, cur->month, cur->day, cur->content);
            // 년도 비교    
            // ok
            if(newNode->year < cur->year){ // 헤더보다 더 앞 순위라면 (예: 헤더 - 2015, newNode - 2014)
                printf("in if\n");
                newNode->next = cur;
                cur->prev = newNode;
                head = newNode;
                break;
            }
            else if( newNode -> year == cur -> year ){ // 노드 내에 20150312(head) - 20160312(cur) - 20160412(newNode) - 20170312 넣는 식
                printf("in else if\n");
                if (newNode->month > cur->month) { // 모든 노드 들보다 newNode의 month가 가장 크다면, 현재 cur가 NULL을 가리키고 있는 상태
                    if(cur->next == NULL){
                        printf("in else\n");
                        printf("마지막 노드\n");
                        newNode->prev = cur;
                        cur->next = newNode;
                        break;
                    }
                    else if (newNode->month > cur->month && newNode->month < cur->next->month) { // 예: cur - 2월, cur->next - 4월, newNode - 3월 오류 뜸 !!!!!!!!!!!!
                        printf("in if\n");
                        newNode->prev = cur;
                        cur->next = newNode;
                        newNode->next = cur->next;
                        cur->next->prev = newNode;
                        break;
                    }
                }                   
                else if ( newNode -> month <= cur -> month ) { // 예: cur - 3월, cur->next - 3월, newNode - 3월 or cur - 3월, cur->next - 4월, newNode - 3월
                    printf("in else if 111\n");
                     // 예: newNode - 03.13 cur->next - 03.16
                    if(newNode->month == cur->month && newNode->day <= cur->day){ // newNode->day <= cur->day
                        printf("in if 1111\n");
                        cur->next = newNode;
                        newNode->prev = cur;
                        break;
                    }
                    else if(newNode->month == cur->month && newNode->day > cur->day){
                        printf("in else if 11111\n");
                        if(cur->next != NULL){
                            printf("in else if 1111111\n");
                            cur->next = newNode;
                            newNode->prev = cur;
                            cur->next->prev = newNode;
                            newNode->next = cur->next;
                        }
                        else{
                            printf("in else if 1111111\n");
                            cur->next = newNode;
                            newNode->prev = cur;
                        }
                        break;
                    }
                    else{ // ok
                        printf("in else 111111\n");
                        newNode->prev = cur-> prev;
                        newNode -> next = cur;
                        if(cur->prev != NULL){
                            cur->prev->next = newNode;
                            cur->prev = newNode;
                        } else head = newNode;
                        break;
                    }
                } 
                else if(newNode->month == cur->month){ // month가 같은 경우 
                    printf("in else if 1111\n");
                    if(newNode->day <= cur->day){ // newNode->day <= cur->day
                        cur->next = newNode;
                        newNode->prev = cur;
                        break;
                    } 
                    else { // newNode->day > cur->day
                        cur->prev = newNode;
                        newNode->next = cur;
                        break;
                    } 

                }
            }
            else { // 기존 노드들 보다 newNode의 year가 더 큰 경우 // ok
                if(cur->next == NULL){
                    cur->next = newNode;
                    cur = newNode->prev;
                    break;
                }
            }
            cur = cur->next;
        }
    }
    return;
} 

/************** Node 삭제 *********************/
void Delete_Node(Node *newNode){
    Node *cur; 
    cur = head;

    while(cur->next != NULL){
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

void Print(void){
    Node *cur;
    cur = head;
    printf("in Print()\n");

    if(head == NULL){
        printf("노드가 존재하지 않습니다.\n");
        return;
    }

    while(cur != NULL){
        printf("%d %d %d %s\n", cur->year, cur->month, cur->day, cur->content);
        cur = cur->next;
    }
    printf("\n");
    return;
}
