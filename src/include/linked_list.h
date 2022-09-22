#include <stdio.h>
#include <stdlib.h>
typedef char *linked_list_element;

typedef struct linked_node
{
    linked_list_element val;    //value in list
    struct linked_node *next;   //next node
} linked_node;

typedef struct linked_list
{
    linked_node *head;          //store head
    linked_node *tail;          //store tail

    int length;                 //list length
} linked_list;

void print_linked_list(linked_list *list);
linked_node *new_node(linked_list_element val);
void free_node(linked_node *node);
linked_list *new_linked_list();
void free_linked_list(linked_list *list);
void linked_list_prepend(linked_list *list, linked_list_element val);
void linked_list_append(linked_list *list, linked_list_element val);
linked_list_element linked_list_index(linked_list *list, int i);
