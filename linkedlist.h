#ifndef LINKEDLIST_H
#define LINKEDLIST_H


typedef struct ListNode
{
        void *playerRow;
        void *playerCol;
        void *boxRow;
        void *boxCol;
        struct ListNode *next;
} ListNode;

typedef struct
{
        ListNode *head;
} LinkedList;


void initializeList(LinkedList *list);
void insertFirst(LinkedList *list, void *playerRow, void *playerCol, void *boxRow, void *boxCol);
void deleteFirst(LinkedList *list);
void printList(LinkedList *list );
void freeList(LinkedList *list);
void *getFirst(LinkedList *list);

#endif
