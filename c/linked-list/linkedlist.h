#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>

typedef struct LinkedListNode {
    int value;
    struct LinkedListNode *next;
} LinkedListNode;

LinkedListNode *ll_create_node(int value);
bool ll_push_front(LinkedListNode **head, int value);
bool ll_push_back(LinkedListNode **head, LinkedListNode **tail, int value);
bool ll_pop_front(LinkedListNode **head, LinkedListNode **tail, int *value);
int ll_length(LinkedListNode *head);
void ll_free(LinkedListNode **head, LinkedListNode **tail);

#endif
