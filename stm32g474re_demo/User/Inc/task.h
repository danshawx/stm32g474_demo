/*
 * task.h
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
    uint32_t           periodictimems;
    uint32_t           remaintoexec;
} my_task_t;


// #define SCHED_MAX_TASKS    1

void my_task_init(void);
void my_sched_loop(void);


#endif /* INC_MY_TASK_H_ */
