#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../queue/queue.h"
#include <stdbool.h>


char findOperator(Queue *q){
    int x = q->front;
    char opr;
    while(x <= q->rear){
         opr = q->expr[x++];
        if(opr == '+') return opr;
        else if(opr == '-') return opr;
        else if(opr == '*') return opr;

    }
    return '/';
}

int handleOperation(Queue *q, char operator){
    char opr = findOperator(q);
    char val;
    while(!isEmpty(q)){
        dequeue(q, &val);
    }
}

int main(){
    int N;
    scanf("%d", &N);
    char temp[1000];
    Queue *q;
    initQueue(q);
    for(int i = 0; i < N; i++){
        fgets(temp, 1000, stdin);
        temp[strcspn(temp, "\n")] = 0;
        int x = strlen(temp);
        int a = 0;
        while(x > 0){
            enqueue(q, temp[a++]);
            x--;
        }
        


    }


    return 0;
}

