

typedef struct _Node
{
    int value;
    struct _Node *next;
}
Node;

typedef struct _ServiceQueue
{
    Node *first;
    Node *last;
} 
ServiceQueue;

ServiceQueue* serviceQueue_new(int length);
void serviceQueue_add(ServiceQueue* serviceQueue, int value);
int serviceQueue_length(ServiceQueue* serviceQueue);
int serviceQueue_head(ServiceQueue* serviceQueue);
void serviceQueue_clear(ServiceQueue *serviceQueue);
