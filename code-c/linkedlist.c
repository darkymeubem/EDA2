#include "linkedlist.h"

#include <stdlib.h>

LinkedListNode *ll_create_node(int value) {
    LinkedListNode *node = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    if (node == NULL) return NULL;

    node->value = value;
    node->next = NULL;
    return node;
}

bool ll_push_front(LinkedListNode **head, int value) {
    if (head == NULL) return false;

    LinkedListNode *node = ll_create_node(value);
    if (node == NULL) return false;

    node->next = *head;
    *head = node;
    return true;
}

bool ll_push_back(LinkedListNode **head, LinkedListNode **tail, int value) {
    if (head == NULL || tail == NULL) return false;

    LinkedListNode *node = ll_create_node(value);
    if (node == NULL) return false;

    if (*tail != NULL) {
        (*tail)->next = node;
    } else {
        *head = node;
    }

    *tail = node;
    return true;
}

bool ll_pop_front(LinkedListNode **head, LinkedListNode **tail, int *value) {
    if (head == NULL || tail == NULL || value == NULL || *head == NULL) return false;

    LinkedListNode *node = *head;
    *value = node->value;
    *head = node->next;

    if (*head == NULL) {
        *tail = NULL;
    }

    free(node);
    return true;
}

int ll_length(LinkedListNode *head) {
    int length = 0;

    while (head != NULL) {
        length++;
        head = head->next;
    }

    return length;
}

void ll_free(LinkedListNode **head, LinkedListNode **tail) {
    if (head == NULL || tail == NULL) return;

    LinkedListNode *current = *head;
    while (current != NULL) {
        LinkedListNode *next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
    *tail = NULL;
}
