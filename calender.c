#include "calender.h"
#include <stdlib.h> // 메모리 할당 (malloc, free), sleep
#include <string.h> // strcmp, strcat
#define MAX_INDEX 400
//스케줄 관리 프로그램의 작동 로직은 calender.c에서 구현한다.

Calender cal[MAX_INDEX]; 
int ch_cnt = 0;

/************** 일정 관리 실행 함수 *****************/
void calender(){
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
            case 2:
                delete_schedule();
                break;   
            case 3:
                view_schedule();
                break;
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
void input_schedule(void) {
    Calender input;
    char str1[] = "Yes";

    printf("입력: ");
    scanf(" %d %d %d %s", &input.year, &input.month, &input.day, input.content);
    printf("출력: %d 년 %d 월 %d 일 %s \n", input.year, input.month, input.day, input.content);

    if (schedule_bool()) { // 일정이 있으면
        char n[5];
        printf("출력: %d 년 %d 월 %d 일에 일정이 있습니다.\n", input.year, input.month, input.day);
        printf("일정을 추가하려면 Yes를, 덮어쓰려면 No를 입력하세요: ");
        scanf(" %s", n);

        // 비교한 두 문자가 같으면 0 반환 -> else(일정 추가), 다르면 1 반환 -> if(덮어 쓰기)
        if (strcmp(n, str1)) { // 덮어 쓰기
            cal[ch_cnt].year = input.year;
            cal[ch_cnt].month = input.month;
            cal[ch_cnt].day = input.day;
            strcpy(cal[ch_cnt].content, input.content);
            ch_cnt += 4;
            printf("일정을 추가하였습니다.\n");
        }
        else { // 일정 추가 
            ch_cnt++;
            cal[ch_cnt].year = input.year;
            cal[ch_cnt].month = input.month;
            cal[ch_cnt].day = input.day;
            strcpy(cal[ch_cnt].content, input.content);
            ch_cnt--;    
            printf("일정을 추가하였습니다.\n");
        }
    }
    else { // 일정이 없으면
        cal[ch_cnt].year = input.year;
        cal[ch_cnt].month = input.month;
        cal[ch_cnt].day = input.day;
        strcpy(cal[ch_cnt].content, input.content);
        ch_cnt += 4;
        printf("일정을 추가하였습니다.\n");
    }
    printf("아무 키나 입력하세요...\n");

    getchar();
    return;
}

/********** 일정이 있는지 없는지 확인하는 함수 *********/
// 일정이 있으면 1 출력, 없으면 0 출력
int schedule_bool(void){
    for(int i = 0; i < MAX_INDEX; i++){
        // 일정이 없으면 (cal[i].content == NULL 보다는 있는 값으로 조건문하는게 최선)
        if(cal[i].year==0 && cal[i].month == 0 && cal[i].day == 0) return 0;
        else return 1;
    }
}

/***************** 일정 삭제 Main 함수 ********************/
/* 일정이 있을 경우 해당 일정 삭제, 일정이 없을 경우 일정이 없다고 출력*/
// 해당 일정만 삭제 해야함. 

void delete_schedule(void) {
    Calender input; 
    printf("입력: ");
    scanf(" %d %d %d %s", &input.year, &input.month, &input.day, input.content);
    if (schedule_bool()) { // 일정이 있다면
        printf("%d 년 %d 월 %d 일에 일정이 있습니다.\n", input.year, input.month, input.day);
        schedule_sub_delete(input); // 해당 일정 삭제 
        printf("일정을 삭제하였습니다.\n");
    }
    else { // 일정이 없다면
        printf("%d 년 %d 월 %d 일에 일정이 없습니다.\n", input.year, input.month, input.day);
    }
    printf("아무 키나 입력하세요...\n");
    getchar();
    return;
}
/********** 해당 일정 삭제 Sub 함수 *********/
// 일정이 있으면 삭제
void schedule_sub_delete(Calender input){
    for(int i = 0; i < MAX_INDEX; i++){
        // 해당 일정이 있다면 삭제
        if(strcmp(cal[i].content, input.content) == 0){ 
            cal[i].year = 0;
            cal[i].month = 0;
            cal[i].day = 0;
            //strcpy(cal[i].content, NULL);  오류 발생 !!!!!!!!!!!!!!!!!!!!!!!!!!!
            return;
        }
    }
    return ;
}

/***************** 일정 출력 함수 ********************/

void view_schedule(void){
    int d[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int count = 0;
    for(int i = 0; i <MAX_INDEX; i++){
        // 빠른 스케줄부터 보여주기
        if(cal[i].year != 0 && cal[i].month != 0 && cal[i].day != 0) {
            if(year_check(i)){ // 윤년이라면
                d[1] = 29;
                int first_dates = ((cal[i].year * 365) + (cal[i].year)/4 - ((cal[i].year-1)/100)+ ((cal[i].year-1)/400)) % 7; // 해당 년 1월 1일 index
                for(int j = 0; j < cal[i].month - 1; j++){
                    first_dates += d[j];
                }
                first_dates = first_dates % 7; // 해당 달의 1일 index 
                int dates = (first_dates + (cal[i].day - 1)) % 7; // 해당 일 index
                printf("\t\t\t%d월\n",cal[i].month);
                
                printf("일\t월\t화\t수\t목\t금\t토\n"); 
                for(int j = 0; j < first_dates; j++){
                    printf("\t");
                    count++;
                }
                // 일정도 출력! 
                for(int j = 1; j <= d[cal[i].month - 1]; j++){
                    if(count == 7){
                        printf("\n");
                        count = 0;
                    }
                    printf("%d\t", j);
                    /*
                    if(j == cal[i].day){
                        for(int k = 0; k < dates; k++)
                            printf("\t");
                        printf("\n%s\n", cal[i].content);
                    }
                    */
                    count++;
                } 
                printf("\n");   
            }
            else{ // 윤년이 아니라면
                int first_dates = ((cal[i].year * 365) + (cal[i].year)/4 - ((cal[i].year-1)/100)+ ((cal[i].year-1)/400)) % 7; // 해당 년 1월 1일 index
                for(int j = 0; j < cal[i].month - 1; j++){
                    first_dates += d[j];
                }
                first_dates = first_dates % 7; // 해당 달의 1일 index 
                int dates = (first_dates + (cal[i].day - 1)) % 7; // 해당 일 index
                printf("\t\t\t%d월\n",cal[i].month);

                printf("일\t월\t화\t수\t목\t금\t토\n"); 
                for(int j = 0; j < first_dates; j++){
                    printf("\t");
                    count++;
                }
                // 일정도 출력! 
                for(int j = 1; j <= d[cal[i].month - 1]; j++){
                    if(count == 7){
                        printf("\n");
                        count = 0;
                    }
                    printf("%d\t", j);
                    /*
                    if(j == cal[i].day){
                        for(int k = 0; k < dates; k++)
                            printf("\t");
                        printf("\n%s\n", cal[i].content);
                    }
                    */
                    count++;
                } 
                printf("\n");   
            }
        }
    }
    return;
}

/***************** 윤년 check 함수 ********************/
int year_check(int n){
    if((cal[n].year % 4 == 0) && (cal[n].year % 100 != 0) && (cal[n].year % 400 == 0)) return 1;
    else return 0;
}