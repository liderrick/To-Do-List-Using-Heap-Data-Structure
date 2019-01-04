/*
* CS 261 Assignment 5
* Name: Derrick Li
* Date: May 28, 2017
* Description: Part 1 and 2: Task implementation file - task.c file
*/

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Creates a new task with the given priority and name.
 * @param priority
 * @param name
 * @return  The new task.
 */
Task* taskNew(int priority, char* name)
{
    // FIXME: implement
	Task *newTask = (Task *)malloc(sizeof(Task));

	newTask->priority = priority;
	strcpy(newTask->name, name);	

    return newTask;
}

/**
 * Frees a dynamically allocated task.
 * @param task
 */
void taskDelete(Task* task)
{
    free(task);
}

/**
 * Casts left and right to Task pointers and returns
 * -1 if left's priority < right's priority,
 *  1 if left's priority > right's priority,
 *  0 if left's priority == right's priority.
 * @param left  Task pointer.
 * @param right  Task pointer.
 * @return 
 */
int taskCompare(void* left, void* right)
{
    // FIXME: implement
	int result;

	Task *leftTask = (Task *)left;
	Task *rightTask = (Task *)right;

	if (leftTask->priority < rightTask->priority)
	{
		result = -1;
	}
	else if(leftTask->priority > rightTask->priority)
	{
		result = 1;
	}
	else   /* leftTask->priority == rightTask->priority */
	{
		result = 0;
	}

    return result;
}

/**
 * Prints a task as a (priority, name) pair.
 * @param value  Task pointer.
 */
void taskPrint(void* value)
{
    Task* task = (Task*)value;
    printf("(%d, %s)", task->priority, task->name);
}
