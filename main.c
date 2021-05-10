#include<stdio.h>
//#include "calc.h"
#include "calender.h"
//공학용 계산기와 스케줄 관리 프로그램의 로직들을 main.c에서 호출하여 사용
//main.c에서는 단순 메뉴 출력만을 위한 로직을 구현
//gcc -o project main.c calc.c calender.c 명령을 이용하여 컴파일
// ./project 명령을 이용하여 실행
int main(){
    //calc();
    calender();
    printf("수정\n");
    return 0;
}