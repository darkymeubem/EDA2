#include <stdio.h>
#include <stdlib.h>

int main(){
    int a = 6;
    int *p = &a;
    printf("%p %d\n",p,*p);
    *p = 5;

    printf("%d %d",a,*p);


    return 0;
}