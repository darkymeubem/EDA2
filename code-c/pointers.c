#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node *create_node(int num){
    node *new = malloc(sizeof(node)); //malloc devolve o endereço de um nó alocado na heap
    printf("new: %p\n", new);
    if(new == NULL) return NULL;
    new->data = num;
    new->next = NULL;
    return new;
}

int main() {
    //[ 0x00AF1908 ] 0x0061FF1C

    node *head = create_node(4);
    
    printf("%p %p %p\n",head->next, head, &head );
    printf("%d\n", sizeof(node));
  
    node *new = create_node(10);
    head->next = new;
    int num = 5;
  
    printf("%p %p %p %d %p\n",head->next, new, &new, num, &num );


    return 0;
}