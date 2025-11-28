

/*implementation of stack using array*/

#include<stdio.h>
#define SIZE 100

int stack [SIZE];
int top=-1;

void push(int value){
if (top==SIZE-1){
printf("Stack overflow\n");
}else{
top++;
stack[top]=value;
printf("%d pushed to stack\n",value);
}}

void pop(){
if(top==-1){
printf("Stack underflow\n");
}else{
printf("%d popped from stack\n", stack[top]);
top--;
}}

void display(){
if(top==-1){
printf("Stack is empty \n");
}else{
printf("stack elements:");
for(int i=0;i<=top;i++){
printf("%d", stack[i]);
}
printf("\n");
}}

int main(){
int choice,value;

while(1){
printf("\n stack menu\n");
printf("1.push\n2.pop\n3.display\n4.Exit\n");
printf("Enter your choice:");
scanf("%d",&choice);

switch(choice){
case 1:
printf("enter value to push:");
scanf("%d",&value);
push(value);
break;
case 2:
pop();
break;
case 3:
display();
break;
case 4:
return 0;
default:
printf("invalid choice\n");
}
}
return 0;
}
