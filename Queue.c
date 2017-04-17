#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

Queue* queue_new(int newQueueType)
{
   Queue* queue = (Queue*)malloc(sizeof(Queue));
    
   if (queue == NULL)
   {
      fprintf(stderr, "Error: Unable to allocate memory in queue_new()\n");
      
      exit(EXIT_FAILURE);
   }
   
   queue->first = NULL;
   queue->last  = NULL;
   
   queue->queueType = newQueueType;
   
   return queue;
}

void queue_add(Queue* queue, int value)
{
   Node* node = (Node*)malloc(sizeof(Node));
   
   if (node == NULL)
   {
      fprintf(stderr, "Error: Unable to allocate memory in queue_add()\n");
      
      exit(EXIT_FAILURE);
   }
   
   node->value = value;
   node->next  = NULL;
    
   if (queue->last == NULL)
   {
      queue->first = queue->last = node;
   }
   else
   {
      queue->last = queue->last->next = node;  
   }
}

void queue_insert(Queue* queue, int value)
{
   Node* node = (Node*)malloc(sizeof(Node));

   if (node == NULL)
   {
      fprintf(stderr, "Error: Unable to allocate memory in queue_insert()\n");
      
      exit(EXIT_FAILURE);
   }
    
   node->value = value;
   node->next  = queue->first;
   
   if (queue->first == NULL)
   {
      queue->first = queue->last = node;
   }
   else
   {
      queue->first = node;
   }
}

int queue_length(Queue* queue)
{
   int length = 0;
    
   for (Node* node = queue->first; node != NULL; node = node->next)
   {
       length++;
   }
    
   return length;
}

int queue_head(Queue* queue)
{
    if (queue->first == NULL)
    {
       fprintf(stderr, "Error: attempt to return the head of an empty queue.");

       exit(EXIT_FAILURE);
    }

    int value = queue->first->value;

    Node *node = queue->first;

    if (queue->first == queue->last)
    {
       queue->first = queue->last = NULL;    
    }
    else
    {
       queue->first = queue->first->next;    
    }

    free(node);

    return value;
}

int queue_tail(Queue* queue)
{
    if (queue->last == NULL)
    {
        fprintf(stderr, "Error: attempt to return the tail of an empty queue.");

        exit(EXIT_FAILURE);       
    }
   
    int value = queue->last->value;
   
    Node* tail = queue->last;

    if (queue->first == queue->last)
    {
        queue->first = queue->last = NULL;
    }
    else
    {
        Node* node;

        for (node = queue->first; node->next != tail; node = node->next);

        queue->last       = node;
        queue->last->next = NULL;
    }

    free(tail);
    
    return value;
}
