#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/************************************************
 * calc.c에 필요한 헤더파일들은 현재 파일에 선언
 * calc.c에 구현될 함수들의 원형(proto type)은 현재 파일에 선언
 * 구조체 및 DEFINE 메크로도 현재 파일에 선언
 * ************************************************/

void calc(void);
char* transformation(char * input);
char* postfix(char * transformed);
void input(void);
void deleteSpace(char *);
void calculate(char *postfixed);

_Bool isEmpty();
void push(char operator);
char pop();
char peek();

double calStack[100]={};
int calTop=-1;

_Bool calIsEmpty(){
   return (calTop==-1);
}

double calPeek(){
   if(!calIsEmpty()){
      return calStack[calTop];
   }
}

double calPush(double operator){
   calStack[++calTop]=operator;
}
double calPop(){
   if(!(calIsEmpty())){
      return calStack[calTop--];
   }
}
