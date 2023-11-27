/*
 * scheduler.c
 *
 *  Created on: Nov 20, 2023
 *      Author: thien
 */

#include "scheduler.h"

// Linked List
struct Node *CreateNode(sTask data)
{
    struct Node *NewNode = malloc(sizeof(*NewNode));
    if (!NewNode)
        return NULL;

    NewNode->data.pTask = data.pTask;
    NewNode->data.Delay = data.Delay;
    NewNode->data.Period = data.Period;
    NewNode->data.RunMe = data.RunMe;
    NewNode->data.TaskID = data.TaskID;
    NewNode->next = NULL;
    return NewNode;
}

void AddTask(struct Node **head, sTask data)
{
    struct Node *NewNode = CreateNode(data);
    if (*head == NULL)
    {
        *head = NewNode;
//        (*((*head)->data.pTask))();
        return;
    }

    struct Node *current = *head;
    if (NewNode->data.Delay < (*head)->data.Delay)
    {
        current->data.Delay -= NewNode->data.Delay;
        NewNode->next = current;
        *head = NewNode;
//        (*((*head)->data.pTask))();
        return;
    }
    else
        NewNode->data.Delay -= current->data.Delay;

    while (current->next != NULL && current->next->data.Delay <= NewNode->data.Delay)
    {
        NewNode->data.Delay -= current->next->data.Delay;
        current = current->next;
    }
    if (current->next == NULL)
        current->next = NewNode;
    else
    {
        NewNode->next = current->next;
        current->next = NewNode;
    }
//    (*((NewNode)->data.pTask))();
}

void DeleteTask(struct Node **head)
{
    if (*head == NULL)
        return;
    struct Node *current = *head;
    *head = current->next;
    free(current);
}

void ClearList(struct Node **head)
{
    while (*head != NULL)
        DeleteTask(head);
}

void DeleteTaskID(struct Node **head, uint32_t taskID)
{
    struct Node *current = *head;
    struct Node *prev = NULL;

    while (current != NULL && current->data.TaskID != taskID)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
        return;
    if (prev == NULL)
        DeleteTask(head);
    else
        prev->next = current->next;
    free(current);
}

// Scheduler
static int id = 0;
static struct Node *head = NULL;

void SCH_Init()
{
    ClearList(&head);
    id = 0;
}

void SCH_Add_Task(void (*pTask)(), uint32_t Delay, uint32_t Period)
{
    sTask data;
    data.pTask = pTask;
    data.Delay = Delay;
    data.Period = Period;
    data.RunMe = 0;
    data.TaskID = id;
    AddTask(&head, data);
    id++;
}

void SCH_Delete_Task(uint32_t taskID)
{
    DeleteTaskID(&head, taskID);
}

void SCH_Dispatch_Task(void)
{
    if (head == NULL)
        return;
    if (head->data.RunMe == 1)
    {
        (*(head->data.pTask))();
        if(head->data.Period == 0)
            DeleteTask(&head);
        else
        {
            sTask RenewTask;
            RenewTask.pTask = head->data.pTask;
            RenewTask.Delay = head->data.Period;
            RenewTask.Period = head->data.Period;
            RenewTask.RunMe = 0;
            RenewTask.TaskID = id;
            DeleteTask(&head);
            AddTask(&head, RenewTask);
        }
    }
//    struct Node *list = head;
//    while (list != NULL)
//    {
//        printf("Delay: %d\n", list->data.Delay);
//        list = list->next;
//    }
}

void SCH_Update(void)
{
    if (head == NULL)
        return;
    if (head->data.Delay > 0)
        head->data.Delay--;
    else
        head->data.RunMe = 1;
}

void SCH_Testing()
{
	SCH_Add_Task(set_init, 0, 0);
	SCH_Add_Task(fsm_mode, 0, 1);
	SCH_Add_Task(fsmIncVal, 0, 1);
	SCH_Add_Task(seg_leds, 0, 1);
}
