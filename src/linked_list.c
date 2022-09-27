#include "include/linked_list.h"

void print_linked_list(linked_list *list){
    linked_node *node = list->head;
    while(node){
        printf("%s ->", node->val);
        node = node->next;
    }   
    printf("\n");
}   

/*create a node*/
linked_node *new_node(linked_list_element val, uint8_t cat){
    linked_node *ret = malloc(sizeof(linked_node));

    ret->val = val;
    ret->category = cat;
    ret->next = NULL;
    return ret;
}

/*free a node*/
void free_node(linked_node *node){
    node->val = NULL;
    node->category = 0;
    node->next = NULL;
    free(node);
}

/*initialize new linked list*/
linked_list *new_linked_list(){
    linked_list *ret = malloc(sizeof(linked_list));

    ret->head = NULL;
    ret->tail = NULL;
    ret->current = NULL;

    ret->length = 0;
    return ret;
}

/*free list and nodes*/
void free_linked_list(linked_list *list){
    linked_node *cur, *temp;
    cur = list->head;
    while (cur != NULL)
    {
        temp = cur->next;
        free_node(cur);
        cur = temp;
    }

    list->head = NULL;
    list->tail = NULL;
    
    list->length = 0;
}

void linked_list_prepend(linked_list *list, linked_list_element val, uint8_t cat){
    linked_node *node = new_node(val, cat);
    node->next = list->head;
    list->head = node;
    if (list->tail == NULL){
        list->tail = list->head;
    }
    list->length++;
}

void linked_list_append(linked_list *list, linked_list_element val, uint8_t cat){
    if (list->tail == NULL){
        linked_list_prepend(list, val, cat);
    }
    else{
        linked_node *node = new_node(val, cat);
        list->tail->next = node;
        list->tail = node;
        list->length++;
    }
}

linked_list_element linked_list_index(linked_list *list, int i){
    if(i >= list->length){
        printf("Index out of Bounds");
        return NULL;
    }
    linked_node *node = list->head;
    for(int j = 0; j<i; j++){
        node = node->next;
    }
    return node->val;
}