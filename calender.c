#include "calender.h"
#include <stdlib.h> // 메모리 할당 (malloc, free), sleep
#include <string.h> // strcmp, strcat
#define MAX_INDEX 400
//스케줄 관리 프로그램의 작동 로직은 calender.c에서 구현한다.

int ch_cnt = 0;

/************** 일정 관리 실행 함수 *****************/
void calender(void){
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
                input_schedule();
                break;
                /*
            case 2:
                delete_schedule();
                break;   
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
    return;
}

/***************** 일정 입력 함수 ********************/
/* 입력한 날에 일정이 있으면 추가할 것인지 덮어쓸 것인지 확인
추가할 경우 문자열을 연결, 덮어쓸 경우 해당 일정 삭제 후 덮어쓰기
이후 화면 clear */
void input_schedule(void){
    Node *input = (Node *)malloc(sizeof(Node));
    input->next = NULL;

    char str1[] = "Yes";

    printf("입력: ");
    scanf(" %d %d %d %s", &input->year, &input->month, &input->day, input->content);
    printf("출력: %d 년 %d 월 %d 일 %s \n", input->year, input->month, input->day, input->content);

    if (schedule_bool(input)){ // 일정이 있으면
        char n[5];
        printf("출력: %d 년 %d 월 %d 일에 일정이 있습니다.\n", input->year, input->month, input->day);
        printf("일정을 추가하려면 Yes를, 덮어쓰려면 No를 입력하세요: ");
        scanf(" %s", n);

        // 비교한 두 문자가 같으면 0 반환 -> else(일정 추가), 다르면 1 반환 -> if(덮어 쓰기)
        if (strcmp(n, str1)){ // 덮어 쓰기
            
            ch_cnt++;
            printf("일정을 추가하였습니다.\n");
        }
        else{ // 일정 추가
            
            printf("일정을 추가하였습니다.\n");
        }
        printf("아무 키나 입력하세요...\n");

        getchar();
        return;
    }
}

/********** 일정이 있는지 없는지 확인하는 함수 *********/
// 일정이 있으면 1 출력, 없으면 0 출력
int schedule_bool(Node *input){
    while(input->next != NULL){
        if(input->day != 0) return 1;
        else return 0;
    }
}

/***************** 일정 삭제 Main 함수 ********************/
/* 일정이 있을 경우 해당 일정 삭제, 일정이 없을 경우 일정이 없다고 출력*/
// 해당 일정만 삭제 해야함. 
//void delete_schedule(void);

/********** 해당 일정 삭제 Sub 함수 *********/
// 일정이 있으면 삭제
//void schedule_sub_delete(Node *input);

/***************** 윤년 check 함수 ********************/
/*
int year_check(int year){
    if((year % 4 == 0) && (year % 100 != 0) && (year % 400 == 0)) return 1;
    else return 0;
}
/*****************************************************************/
/************************** LinkedList ***************************/
/*****************************************************************/

/**** List의 마지막에 새로운 data에 대한 Node 추가 ****/
void Append(Node *head, int year, int month, int day, char content[]){
    // 새로운 노드 생성
    Node *newNode = (Node *)malloc(sizeof(Node)); 
    newNode->year = year;
    newNode->month = month;
    newNode->day = day;
    strcpy(newNode->content, content);
    newNode->next = NULL;

    // 처음 삽입되는 노드라면 (더미노드 없기때문에 조건 달리 지정)
    if(head ==  NULL){
        head = newNode;
    }
    else { // 처음 삽입되는 노드가 아니라면
        Node *cur;
        cur = head;

        while(cur->next != NULL){
            if(cur->day < newNode->day && cur->next->day > newNode->day){
                cur->next = newNode;
                newNode->next = cur->next;
                cur = head;
            }
            else {
                cur = cur->next;
                cur->next = newNode;
                cur = newNode;
            }
        }
    }
    return;
} 

/**** List의 처음에 새로운 data에 대한 Node 추가 ****/
void Prepend(Node *head, int year, int month, int day, char content[]){
    Node* newNode = (Node *)mallloc(sizeof(Node));
    newNode->year = year;
    newNode->month = month;
    newNode->day = day;
    strcpy(newNode->content, content);
    newNode->next = NULL;

    // 처음 삽입되는 노드라면 (더미노드 없기때문에 조건 달리 지정)
	if (head == NULL) {
		head = newNode;
	}
	else { // 처음 삽입되는 경우가 아니라면
		newNode->next = head; // newNode의 next와 head 연결
		head = newNode; // head와 newNode를 연결
	}
}

/**** List에 있는 Node의 수를 return ****/
int Length(Node *head){
    // cur 노드를 만들어서 이동하면서 길이 구하기
    Node *cur;
    cur = head;
    int count = 0;
    while(cur->next != NULL){
        cur = cur->next;
        count++;
    }
    return count;

}

/**** List에 있는 모든 Node를 head부터 순서대로 출력
ex) 4,3,5 => "4 3 5"  ****/
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
