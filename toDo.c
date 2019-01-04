/*
* CS 261 Assignment 5
* Name: Derrick Li
* Date: May 28, 2017
* Description: Part 2: To-do list implementation - toDo.c file
*/

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
     while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // FIXME: Implement
	if (command == 'l')
	{
		char fileName[256];
		printf("\nPlease enter a file name to load: ");
		scanf("%s", fileName);
		while (getchar() != '\n');

		FILE *inputFile = fopen(fileName, "r");

		if (inputFile == NULL)
		{
			printf("Cannot open \"%s\".\n\n", fileName);
		}
		else
		{
			listLoad(list, inputFile);
			fclose(inputFile);
			printf("Successfully loaded \"%s\".\n\n", fileName);
		}
		
	}
	else if (command == 's')
	{
		char fileName[256];
		printf("\nPlease enter a file name to save: ");
		scanf("%s", fileName);
		while (getchar() != '\n');

		FILE *outputFile = fopen(fileName, "w");

		if (outputFile == NULL)
		{
			printf("Error in saving to \"%s\".\n\n", fileName);
		}
		else
		{
			listSave(list, outputFile);
			fclose(outputFile);
			printf("Successfully saved to \"%s\".\n\n", fileName);
		}
		
	}
	else if (command == 'a')
	{
		int priority = 0;
		char taskName[256];

		printf("\nPlease enter the task description: ");
		scanf("%[^\n]s", taskName);
		while (getchar() != '\n');

		printf("Please enter the task priority (0-999): ");
		scanf("%d", &priority);
		while (getchar() != '\n');

		Task *newTask = taskNew(priority, taskName);
		dyHeapAdd(list, newTask, taskCompare);

		printf("\nThe task \"%s\" has been added to your to-do list.\n\n", taskName);
	}
	else if (command == 'g')
	{
		if (dySize(list) > 0)
		{
			Task *firstTask = dyHeapGetMin(list);

			printf("\nYour first task is: %s\n\n", firstTask->name);

		}
		else
		{
			printf("\nYour to-do list is empty!\n\n");
		}
		
	}
	else if (command == 'r')
	{
		if (dySize(list) > 0)
		{
			Task *firstTask = dyHeapGetMin(list);
			char firstTaskName[256];
			strcpy(firstTaskName, firstTask->name);

			taskDelete(dyGet(list, 0));
			dyHeapRemoveMin(list, taskCompare);

			printf("\nThe first task \"%s\" on your list has been successfully removed.\n\n", firstTaskName);
		}
		else
		{
			printf("\nYour to-do list is empty! There are no items to remove.\n\n");
		}
		
	}
	else if (command == 'p')
	{
		if (dySize(list) > 0)
		{
			printf("\nYour to-do list (priority, name)\n");
			printf("-----------------------------------------------\n");
			listPrint(list);
			printf("\n");
		}
		else
		{
			printf("\nYour to-do list is empty!\n\n");
		}

	}
	else if (command == 'e')
	{
		printf("\nGoodbye.\n\n");
	}

}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);

    }
    while (command != 'e');
 /* free dynamically allocated List pointers in array to avoid memory leaks */
         /* Fix it */
	while (dySize(list) > 0)
	{
		taskDelete(dyGet(list, 0));
		dyHeapRemoveMin(list, taskCompare);
	}

    dyDelete(list);
    return 0;
}