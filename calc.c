#include "calc.h"

//공학용 계산기의 작동 로직은 calc.c에서 구현한다.
int top=-1;
char stack[100]={};
int alphabet[26]={0, };
void calc(){
    printf("it is cal.c\n");
}
int main(){
   input();

   return 0;
}
void input()
{
   char *input = malloc(sizeof(char)*100);

   while(1){
      printf("Input : ");
      scanf("%[^\n]s", input);   
      getchar();

      deleteSpace(input);   

      if(strchr(input, '=')==NULL){
         char *transformed = malloc(sizeof(char)*100);
         char *postfixed = malloc(sizeof(char)*100);
         transformed=transformation(input);
         postfixed=postfix(transformed);
         calculate(postfixed);
         break;
      }else{
         char *ptr = strtok(input,"=");
         char ch = ptr[0];
         int index = ch-65;

         ptr=strtok(NULL," =");
         alphabet[index]=atoi(ptr);

      }
   }   
}
char * transformation(char * input)
{
   char *result = malloc(sizeof(char)*100);
   int i=0, j=0; 
   while(input[i]!= '\0'){   //input이 null일 때까지 반복
      if(input[i]>='A'&&input[i]<='Z'){   //변수이면
         int index = input[i]-65;   
         int num = alphabet[index];
         
         sprintf(result+j, "%d", num);   //변수 대신 값 넣기
         do{
            if(num<0){   //변수가 음수값이면
               j++; //부호(-)저장할 자리 +1
               num=num*(-1);   //음수를 양수로 바꾸고 while문 돌면서 자릿수 계산
               }
            j++;   //자릿수만큼 while문 돌면서 j++
            num=num/10;
         }while(num>0);

         i++;

         printf("Transformation : %s",result);   //변수를 숫자로 바꾼 만큼 출력
         printf("%s\n",input+i);   //숫자로 바뀐 곳 다음부터 출력
      }
      else{
         result[j]=input[i];   //변수 아니면 그대로 복사
         i++; j++;
      }
   }

   return result;
   
}
char * postfix(char * transformed)
{
   char *postfix=malloc(sizeof(char)*100);
   int pi=0; 
   int curr=0;
   char ch;
   //수식이 끝날때까지 반복
   do{
      ch = transformed[curr++];
      if(ch=='('){   //ch가 왼쪽 괄호면 push
         push(ch);
      }else if(ch>='0'&&ch<='9'){   //ch가 숫자면 자릿수 확인 후 num으로 출력
         int num =0;
         int pj=0;
         do{
            pj++;   //num의 자릿수만큼 pi에 더함
            num = num *10 + ch-'0';
            ch = transformed[curr++];
         }while(ch>='0'&&ch<='9');
         sprintf(postfix+pi, "%d", num);   //num을 배열에 저장
         pi=pi+pj;
         postfix[pi++]=' ';   //num뒤에 공백 추가
         printf("postfix notation : %s\n",postfix);   //postfix notaion 출력
         --curr;
      }
      else if(ch == '+'||ch == '-'||ch == '*'||ch == '/'){   //연산자일때
         if(isEmpty()){   //스택이 비어있으면 push
            push(ch);
         }
         else if(peek()=='('){   //top이 왼쪽괄호면 push
            push(ch);
         }
         else{   
            switch(ch){
               case '*':
               case '/':
                  if(peek()!='*'&&peek()!='/'){push(ch);}   //top이 *,/ 가 아닐때만 push
                  else{   //ch의 우선순위가 top보다 높을 때까지 pop
                     postfix[pi++]=pop();   //pop한 연산자를 postfixed에 저장
                     postfix[pi++]=' ';   //공백추가
                     printf("postfix notation : %s\n",postfix);   //출력
                     --curr;
                     }
                  break;
               case '+':
               case '-':
                  if(peek()!='*'&&peek()!='/'&&peek()!='+'&&peek()!='-'){push(ch);}   //top이 *,/,-,+ 가 아닐때만 push
                  else{   //ch의 우선순위가 top보다 높을 때까지 pop
                     postfix[pi++]=pop();   //pop한 연산자를 postfixed에 저장
                     postfix[pi++]=' ';   //공백추가
                     printf("postfix notation : %s\n",postfix);   //출력
                     --curr;
                     }
            }
         }
      }else if(ch==')'){   //ch가 오른쪽 괄호이면 왼쪽괄호가 나올때까지 pop
            while(peek()!='('){
               postfix[pi++]=pop();   //왼쪽괄호가 나올때까지 연산자를 postfixed에 저장하고 출력
               postfix[pi++]=' ';
               printf("postfix notation : %s\n",postfix);
               }
            pop();
         }
   }while(ch!='\0'&&ch!='\n');

   //수식이 끝나면 stack에 있는 모든 연산자 출력
   while(top != -1){
      postfix[pi++]=pop();   //pop할때마다 연산자를 postfixed에 저장하고 출력
      postfix[pi++]=' ';
      printf("postfix notation : %s\n",postfix);
   }

   return postfix;
}
void calculate(char *postfixed)
{
   int array_i=0;
   char *array=malloc(sizeof(char)*100);
   char *ptr = strtok(postfixed, " ");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환

   while(ptr != NULL){
      if(ptr[0] >= '0' && ptr[0] <= '9'){
         int num=0;
         do{
            num=num*10+(*ptr)-'0';
            ptr++;
         }while(*ptr>='0'&&*ptr<='9');

         calPush(num);
      }
      else{
         double num1=calPop();
         double num2=calPop();
         
         switch(ptr[0]){
            case '*':
               calPush(num2*num1);
               printf("check : %.2f %s\n", num2*num1,ptr++);
               break;
            case '/':
               calPush(num2/num1);
               printf("check : %.2f %s\n", num2/num1,ptr++);
               break;
            case '+':
               calPush(num2+num1);
               printf("check : %.2f %s\n", num2+num1,ptr++);
               break;
            case '-':
               calPush(num2-num1);
               printf("check : %.2f %s\n", num2-num1,ptr++);
               break;
         }
      }
      ptr = strtok(NULL, " ");
   }
   printf("result : %f\n",calPop());
}
void print(){

}
char peek(){
   if(!isEmpty()){
      return stack[top];
   }
}
_Bool isEmpty(){
   return (top==-1);
}
void push(char operator){
   stack[++top]=operator;
}
char pop(){
   if(!(isEmpty())){
      return stack[top--];
   }
}
void deleteSpace(char * input)
{
   for(int i=0;i<strlen(input);i++){
      if(input[i]==' '){
         int len = strlen(input);
         for(int j=i;j<len;j++){
            input[j]=input[j+1];
         }
         input[len-1] = '\0';
      }
   }
}