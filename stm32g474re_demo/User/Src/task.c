/*
 * my_task.c
 *
 *  Created on: Nov 23, 2020
 *      Author: dany.shaw
 */

#include "main.h"
#include "task.h"


my_task_t g_umy_task[] =
{
    {comm_task, 100, 100},
    {led_task, 500, 500},
};


void my_sched_loop(void)
{
    uint8_t i;
    static uint8_t task_num = sizeof(g_umy_task) / sizeof(my_task_t);

    for (i = 0; i < task_num; i++)
    {
        if(HAL_GetTick() >= g_umy_task[i].remaintoexec)
        {
            g_umy_task[i].runnable();
            g_umy_task[i].remaintoexec = g_umy_task[i].periodictimems + HAL_GetTick();
        }
        //Iwdg_Clear();
        hal_watchdog_feed();
    }
    //exp deal
}

