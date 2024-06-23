#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct{
    char name[50];
    int age;
}Data;

typedef struct{
    Data data[10];
    int top;
    int base;
    int limit;
}Stack;

void reset(Stack *stack){
    stack->base=0;
    stack->top=0;
    stack->limit=10;
}

bool empty(Stack *stack){
    return stack->top==0;
}

bool full(Stack *stack){
    return stack->top==10;
}

bool PUSH(Stack *stack, Data *item){
    if(!full(stack)){
        stack->data[stack->top]= *item;
        stack->top++;
        return true;
    }else{
        return false;
    }
}

void POP(Stack *stack, Data *item){
   if(stack->top==0){
    return;
   }

   stack->top--;
   *item=stack->data[stack->top];
}

void List(Stack *stack){
    while(!empty(stack)){
        Data item;
        POP(stack, &item);
        printf("%i-%s\n", item.age, item.name);

    }
}

int main(){
    Stack stack;
    Data data;
    int n=0;

    while(n!=(-1)){
        printf("0-Reset the stack, 1-Test if the stack is full or no, 2- Test if the stack if empty or no, 3-Put element in the stack, 4-Remove element from the stack, 5-List all the stack ");
        scanf("%d", &n);
        while ( getchar() != '\n' );
        switch (n)
        {
        case 0:
            reset(&stack);
            break;
        case 1:
            full(&stack);
            break;
        case 2:
            empty(&stack);
            break;
        case 3:
            printf("Digite o nome e a idade: ");
            fgets(data.name, sizeof(data.name), stdin);
            scanf("%d", &data.age);
            
            while (getchar() != '\n');
            PUSH(&stack, &data);
            break;

        case 4:
            POP(&stack, &data);
            break;
        case 5:
            List(&stack);
            break;
        default:
            break;
        }

    }

    return 0;
}