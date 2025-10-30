/*
 * Schedular.c
 *
 *  Created on: Oct 29, 2025
 *      Author: Hi
 */

#include "Schedular.h"

Queue avalable_task_id_list;
Queue ready_task_list;

Task task_list[MAX_TASK_CAPACITY] = {};

uint8_t task_count = 0;

TaskNode_t* head;

void Schedular_Init(){
	//Initialize queues
	Queue_Init(&avalable_task_id_list);
	Queue_Init(&ready_task_list);

	//Initialize Linked list with dummy node
	head = (TaskNode_t*)malloc(sizeof(TaskNode_t*));
	head->next_node = 0;

	//Initialize task_id that are "free"
	for(int i = 0; i < MAX_TASK_CAPACITY; ++i){
		Queue_PushBack(i, &avalable_task_id_list);
	}
}

uint8_t Schedular_AddTask(void (* function)(), uint32_t delay, uint32_t period){
	uint8_t task_id = Queue_PopFront(&avalable_task_id_list);

	task_list[task_id].task_id = task_id;
	task_list[task_id].task_function = function;
	task_list[task_id].delay = delay;
	task_list[task_id].period = period;

	TaskNode_t* new_node = (TaskNode_t*)malloc(sizeof(TaskNode_t));
	new_node->task = &task_list[task_id];
	new_node->next_node = 0;
	return task_id;
}

void Schedular_DeleteTask(uint8_t task_id);

void Schedular_Update(){

	while(head->next_node->task->delay <= 0){
		TaskNode_t* timed_up_task = LinkedList_PopHead(head);

		if(timed_up_task->task->period > 0){
			timed_up_task->task->delay = timed_up_task->task->period;
			LinkedList_Add(head, timed_up_task);
			Queue_PushBack(timed_up_task->task->task_id, ready_task_list);
		}
		else{
			uint8_t task_id = timed_up_task->task->task_id;

			task_list[task_id].task_id = 0;
			task_list[task_id].task_function = 0;
			task_list[task_id].delay = 0;
			task_list[task_id].period = 0;

			free(timed_up_task);
		}
	}
}

void Schedular_Dispatch();

void LinkedList_Add(TaskNode_t* head_node, TaskNode_t* new_node){
	TaskNode_t* current_node = head_node->next_node;

	//Iterate until new_node to appropriate location while calculating its delay
	while(current_node->next_node && current_node->task->delay < new_node->task->delay){
		new_node->task->delay -= current_node->task->delay;
		current_node = current_node->next_node;
	}

	//Insert the new node to the appropriate location
	new_node->next_node = current_node->next_node;
	current_node->next_node = new_node;

	//If the new_node is not at tail -> update the counter next to it
	if(new_node->next_node != 0){
		new_node->next_node->task->delay = new_node->task->delay;
	}
};

TaskNode_t* LinkedList_PopHead(TaskNode_t* head_node){
	TaskNode_t* removed_node = head_node->next_node;
	head_node->next_node = removed_node->next_node;
	return removed_node;
}
