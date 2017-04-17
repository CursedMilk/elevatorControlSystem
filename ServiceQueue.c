#include "ServiceQueue.h"
#include <stdio.h>
#include <stdlib.h>

ServiceQueue* serviceQueue_new(int length){
	ServiceQueue* serviceQueue = (ServiceQueue*)malloc(sizeof(Node) * length);
		
	
	
	return serviceQueue;
}

void serviceQueue_add(ServiceQueue* serviceQueue, int value){
	Node* node = (Node*)malloc(sizeof(Node));
	
	node->value = value;
	node->next = NULL;
	
	if (serviceQueue->first->next == NULL)			//if serviceQueue is empty -> set last and first value to value
	{
		serviceQueue->last = node;
		serviceQueue->first = serviceQueue->last;
	}
	else																				//if serviceQueue is not empty -> append to end
	{
		serviceQueue->last->next = node;
	}
}

int serviceQueue_length(ServiceQueue* serviceQueue){
	return 0;
}

int serviceQueue_head(ServiceQueue* serviceQueue){
	return 0;
}

void serviceQueue_clear(ServiceQueue *serviceQueue){
	
}
