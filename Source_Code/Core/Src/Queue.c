/*
 * Queue.c
 *
 *  Created on: Oct 30, 2025
 *      Author: Hi
 */

#include "Queue.h"

void Queue_PushBack(uint8_t task_id, Queue* queue){
	QueueNode_t* new_node = (QueueNode_t*)malloc(sizeof(QueueNode_t));

	new_node->next_node = 0;
	new_node->task_id = task_id;

	queue->tail->next_node = new_node;
	queue->tail = new_node;
}

uint8_t Queue_PopFront(Queue* queue){
	QueueNode_t* removed_node = queue->head->next_node;

	uint8_t returned_id = removed_node->task_id;
	queue->head->next_node = removed_node->next_node;

	free(removed_node);
	return returned_id;
}

void Queue_Init(Queue* queue){
	queue->head = (QueueNode_t*)malloc(sizeof(QueueNode_t));
	queue->tail = queue->head;
}
