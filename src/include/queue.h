#include "linked_list.h"

typedef struct queue{
    struct linked_list *list;
}queue;

queue *new_queue();
void enqueue(queue *q, linked_list_element val);
linked_list_element dequeue(queue *q);
linked_list_element peek(queue *q);
void print_queue(queue *q);
void free_queue(queue *q);