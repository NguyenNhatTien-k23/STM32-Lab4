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

void Schedular_Init(){
	Queue_Init(&avalable_task_id_list);
	Queue_Init(&ready_task_list);
	for(int i = 0; i < MAX_TASK_CAPACITY; ++i){
		Queue_PushBack(i, &avalable_task_id_list);
	}
}

uint8_t Schedular_AddTask(void (* function)(), uint32_t delay, uint32_t period){

}

void Schedular_DeleteTask(uint8_t task_id);

void Schedular_Update();
void Schedular_Dispatch();
