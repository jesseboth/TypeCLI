#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef char *linked_list_element;

/* Linked list node
    @param val      main value in list
    @param category additional modifier
    @param *next    next node
*/
typedef struct linked_node
{
    linked_list_element val;    //value in list
    uint8_t category;           // 
    struct linked_node *next;   //next node
} linked_node;

/* Linked List naster struct 
    @param *head    first element
    @param *tail    last element
    @param length   current length
*/
typedef struct linked_list
{
    linked_node *head;          //store head
    linked_node *tail;          //store tail

    int length;                 //list length
} linked_list;


/* Prints the linked list  
    @param *list    linked_list
    @return -
*/
void print_linked_list(linked_list *list);

/* Creates a new node  
    @param val      main value
    @param cat      category value
    @return -
*/
linked_node *new_node(linked_list_element val, uint8_t cat);

/* Free node  
    @param *node     linked list node
    @return -
*/
void free_node(linked_node *node);

/* Make a new list  
    @param -
    @return linked_list*     initialzed linked list
*/
linked_list *new_linked_list();

/* Clear the entire list  
    @param *list    list to be freed
    @return -
*/
void free_linked_list(linked_list *list);

/* Append to linked list  
    @param *list    list to be appended to
    @param val      node value
    @param cat      node category
    @return -
*/
void linked_list_prepend(linked_list *list, linked_list_element val, uint8_t cat);

/* Append to linked list  
    @param *list    list to be prepended to
    @param val      node value
    @param cat      category
    @return -
*/
void linked_list_append(linked_list *list, linked_list_element val, uint8_t cat);

/* Get a value from a specific index  
    @param *list    linked list
    @param i        index
    @return -
*/
linked_list_element linked_list_index(linked_list *list, int i);


// TODO

/* Get a node from a specific index  
    @param *list            linked list
    @param i                index
    @return -
*/
linked_node linked_list_index_node(linked_list *list, int i);

/* Remove a node from a specific index - frees node
    @param *list            linked list
    @param in
    @return -
*/
void linked_list_remove_index(linked_list *list, int i);

/* Remove a node from a specific index
    @param *list            linked list
    @param i                index
    @return linked_node*    at index
*/
linked_node *linked_list_remove_index_node(linked_list *list, int i);

/* Remove a node at head - frees node
    @param *list             linked list
    @return -
*/
void linked_list_remove_head(linked_list *list);

/* Remove node at head
    @param *list            linked list
    @return linked_node*    at head
*/
linked_node lined_list_remove_head_node(linked_list *list);


/* Remove node at head - frees node
    @param *list            linked list
    @return -
*/
void linked_list_remove_tail(linked_list *list);

/* Remove tail 
    @param *list            linked list
    @return lined_node*     at tail
*/
linked_node lined_list_remove_head_tail(linked_list *list);


