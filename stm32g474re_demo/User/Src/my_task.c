/*
 * my_task.c
 *
 *  Created on: Nov 23, 2020
 *      Author: dany.shaw
 */

#include "main.h"
#include "my_task.h"

My_Task_t g_uMy_Task[SCHED_MAX_TASKS] =
{
    {Comm_Task, 100, 100},
};


void My_Sched_Loop(void)
{
    uint8_t i;

    for (i = 0; i < SCHED_MAX_TASKS; i++)
    {
        if(HAL_GetTick() >= g_uMy_Task[i].remainToExec)
        {
            g_uMy_Task[i].runnable();
            g_uMy_Task[i].remainToExec = g_uMy_Task[i].periodicTimeMs + HAL_GetTick();

            //Iwdg_Clear();
        }
    }
    //exp deal
}

