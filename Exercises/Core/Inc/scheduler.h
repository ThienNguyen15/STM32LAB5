/*
 * scheduler.h
 *
 *  Created on: Nov 20, 2023
 *      Author: thien
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"
#include "scheduler.h"
#include "fsm_mode.h"
#include "7SEG_LEDs.h"
#include "global.h"
#include "software_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define SCH_MAX_TASKS		50
#define NO_TASK_ID			0

typedef struct
{
    void (*pTask)(void);
    uint32_t Delay;
    uint32_t Period;
    uint32_t RunMe;
    uint32_t TaskID;
} sTask;

struct Node
{
    sTask data;
    struct Node *next;
};

struct Node *CreateNode(sTask data);

void AddTask(struct Node **head, sTask data);

void DeleteTask(struct Node **head);

void ClearList(struct Node **head);

void DeleteTaskID(struct Node **head, uint32_t taskID);

void SCH_Init();

void SCH_Add_Task(void (*pTask)(), uint32_t Delay, uint32_t Period);

void SCH_Delete_Task(uint32_t taskID);

void SCH_Dispatch_Task(void);

void SCH_Update(void);

void SCH_Testing();

#endif /* INC_SCHEDULER_H_ */
