

typedef struct _Node
{
    int value;
    struct _Node *next;
}
Node;

typedef struct _Queue
{
    Node *first;
    Node *last;
    
    int queueType;
} 
Queue;

Queue* queue_new(int newQueueType);
void queue_add(Queue* queue, int value);
void queue_insert(Queue* queue, int value);
int queue_length(Queue* queue);
int queue_head(Queue* queue);
int queue_tail(Queue* queue);
void queue_clear(Queue *queue);
