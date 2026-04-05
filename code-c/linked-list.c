#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


typedef struct node{
    int data;
    struct node *next;
} node;

node* initLinkedList(int num){
    node *new = malloc(sizeof(node));
    if(new == NULL) return NULL;
    new->data = num;
    new->next = NULL;

    return new;
}

int lengthLinkedList(node *head){
    if(head == NULL) return 0;
    node *temp = head;
    int a = 0;
    while(temp != NULL){
        a++;
        temp = temp->next;
    }

    return a;
}

void insert_node_end(node **head, int num) {
    if (head == NULL) return;

    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) return;

    new_node->data = num;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    node *temp = *head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = new_node;
}

void insertBeginning(node **head, int num) {
    if (head == NULL) return;

    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) return;

    new_node->data = num;
    new_node->next = *head;
    *head = new_node;
}

bool insertByIndex(node **head, int id, int num) {
    if (head == NULL || id < 0) return false;

    int tam = lengthLinkedList(*head);
    if (id > tam) return false; // inválido

    if (id == tam) {            // inserir no fim
        insert_node_end(head, num);
        return true;
    }

    if (id == 0) {              // inserir no começo
        insertBeginning(head, num);
        return true;
    }

    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) return false;
    new_node->data = num;

    node *temp = *head;
    for (int i = 0; i < id - 1; i++) temp = temp->next;

    new_node->next = temp->next;
    temp->next = new_node;
    return true;
}
