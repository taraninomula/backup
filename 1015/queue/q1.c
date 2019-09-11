#include<stdio.h>
#include<stdlib.h>
typedef struct stu
{
    int data;
    struct stu *next;
}a;
 
void push(a** top, int new_data);
int pop(a** top);
struct queue
{
    a *stack1;
    a *stack2;
};
 

void enqueue(struct queue *q, int x)
{
    push(&q->stack1, x);
}

int dequeue(struct queue *q)
{
    int x;
   
    if(q->stack1 == NULL && q->stack2 == NULL)
    
        printf("Q is empty");
        
 
if(q->stack2 == NULL)
{
    while(q->stack1 != NULL)
    {
        x = pop(&q->stack1);
        push(&q->stack2, x);
         
    }
}
 
x = pop(&q->stack2);
return x;
}
 
void push(a ** top, int new_data)
{
    
    a* new_node =(a*) malloc(sizeof(a));
        if(new_node == NULL)
        
            printf("Stack overflow \n");

new_node->data = new_data;
new_node->next = (*top);
(*top) = new_node;
}
 
int pop(a** top)
{
    int res;
    a *top1;
     
    if(*top == NULL)
        printf("Stack underflow \n");
    else
    {
        top1 = *top;
        res = top1->data;
        *top = top1->next;
        free(top1);
	top1=NULL;
        return res;
         
    }
}
int main()
{
struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    q->stack1 = NULL;
    q->stack2 = NULL;
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    printf("first queued element is %d\n", dequeue(q));
    printf("second queued element is %d\n", dequeue(q));
    printf("third queued element is %d\n", dequeue(q));
}
