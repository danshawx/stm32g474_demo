/*
 * my_task.h
 *
 *  Created on: Nov 23, 2020
 *      Author: dany.shaw
 */

#ifndef MY_TASK_H_
#define MY_TASK_H_

#include "stdint.h"

typedef void(*my_task_runnable_t)(void);

typedef struct
{
    my_task_runnable_t runnable;
    uint32_t           periodicTimeMs;
    uint32_t           remainToExec;
} My_Task_t;


#define SCHED_MAX_TASKS    1

void My_Task_Init(void);
void My_Sched_Loop(void);


#endif /* INC_MY_TASK_H_ */
