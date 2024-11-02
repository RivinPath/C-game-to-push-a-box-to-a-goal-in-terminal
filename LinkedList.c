/*
 * FILE: LinkedList.c
 * AUTHOR: Rivin Pathirage
 * UNIT: Unix and C Programming
 * PURPOSE: Implenting a generic linked list
 * Referrences:
 */

#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

ListNode *firstNode;

/*
 * METHOD: initializeList
 * PURPOSE: initializing the linked list
 * IMPORTS: *list
 * EXPORTS:
 */
void initializeList(LinkedList *list)
{
	list -> head = NULL;
}

/*
 * METHOD: insertFirst
 * PURPOSE: inserting a node for the begining of the linked list
 * IMPORTS: playerRow, playerCol, list, pMapRowHigh, boxRow, boxCol
 * EXPORTS:
 */
void insertFirst(LinkedList *list, void *playerRow, void *playerCol, void *boxRow, void *boxCol)
{
	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->playerRow = playerRow;
	newNode->playerCol = playerCol;
	newNode->boxRow = boxRow;
	newNode->boxCol = boxCol;
	newNode->next = list->head;
	list->head = newNode;
}


/*
 * METHOD: deleteFirst
 * PURPOSE: delete a node from the begining of the linked list
 * IMPORTS:*list
 * EXPORTS:
 */
void deleteFirst(LinkedList *list)
{
	if (list->head == NULL)
	{
		return;
	}

	firstNode = list->head;
	list->head = firstNode->next;

	free(firstNode);
	

}

/*Test the list*/
void printList(LinkedList *list )
{
	ListNode *current = list->head;

	while (current != NULL)
	{
		printf("\nplayer row is:- %d\n", current->playerRow);
		printf("player col is:- %d\n", current->playerCol);
		printf("box row is:- %d\n", current->boxRow);
		printf("box col is:- %d\n", current->boxCol);
		printf("\n");

		current = current->next;
	}
}

/*
 * METHOD: getFirst
 * PURPOSE: getting a node for the begining of the linked list
 * IMPORTS: *list
 * EXPORTS:
 */
void *getFirst(LinkedList *list)
{
    if (list->head != NULL)
    {
        ListNode *firstNode = list->head;
        void *playerRow = firstNode->playerRow;
        void *playerCol = firstNode->playerCol;
        void *boxRow = firstNode->boxRow;
        void *boxCol = firstNode->boxCol;
        return (void *)firstNode;
    }

    return NULL;
}

/*
 * METHOD: freeList
 * PURPOSE: freeing the entire list from the heap memory
 * IMPORTS: *list
 * EXPORTS:
 */
void freeList(LinkedList *list)
{
	ListNode *current = list->head;
	ListNode *next;


	while (current !=  NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	list->head = NULL;
}



