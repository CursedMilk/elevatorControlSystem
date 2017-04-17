#define MAXSTACKSIZE 100

struct stack
{
	int stk[MAXSTACKSIZE];
	int top;
};

typedef struct stack Stack;

void stackInit(Stack *s);
int stackPush(Stack *s, int argument);
int	stackPop(Stack *s);
int stackTop(Stack *s);
