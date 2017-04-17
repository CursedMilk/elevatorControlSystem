#include "Stack.h"

void stackInit(Stack *stack){
	stack->top = 0xFFFFFFFF;
	for(int i = 0; i < MAXSTACKSIZE; i++){
		stack->stk[i] = 0xFFFFFFFF;
	}
}

int stackPush(Stack *stack, int argument){	
	if(stack->top == (MAXSTACKSIZE - 1)){
		return -1;
	}else{
		stack->stk[stack->top++] = argument;
	}
	return 1;
}

int stackPop(Stack *stack){
	int value;
	
	if(stack->top == -1){
		//stack is empty
		return stack->top;
	}else{
		value = stack->stk[stack->top-1];
		stack->stk[stack->top-1] = 0xFFFFFFFF;
		stack->top--;
	}
	return value;
}

int stackTop(Stack *stack){
	return stack->stk[stack->top-1];
}
