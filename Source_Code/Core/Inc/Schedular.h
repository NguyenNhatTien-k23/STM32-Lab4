/*
 * Schedular.h
 *
 *  Created on: Oct 29, 2025
 *      Author: Hi
 */

#ifndef INC_SCHEDULAR_H_
#define INC_SCHEDULAR_H_

#define MAX_TASK_CAPACITY 40

#include <stdint.h>
#include "Queue.h"

typedef struct {
	void (* task)();

	uint32_t delay;
	uint32_t period;

	uint8_t task_id;
}Task;

void Schedular_Init();

uint8_t Schedular_AddTask(void (* function)(), uint32_t delay, uint32_t period);
void Schedular_DeleteTask(uint8_t task_id);

void Schedular_Update();
void Schedular_Dispatch();


#endif /* INC_SCHEDULAR_H_ */
