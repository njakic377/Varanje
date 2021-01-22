#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

#define foreach(p, q) for(p=q->next; p!=NULL; p=p->next)


Node *pop_from_stack(Node *head) {
    if(head->next == NULL) {
        printf("No elements to pop");
        return NULL;
    }

    Node *removed = head->next;
    head->next = removed->next;
    return removed;
}


Node *push_to_stack(Node *head, Tree *val) {  
    Node *new_node = create_node(val);

    new_node->next = head->next;
    head->next = new_node;

    return new_node;
}


Node *create_node(Tree *val) {
    Node *new_node = (Node *)malloc(sizeof(Node));

    if(new_node == NULL) {
        printf("Unable to allocate space");
        return NULL;
    }

    new_node->next = NULL;
    new_node->val = val;

    return new_node;
}


void print_stack(Node *head) {
    Node *temp_node;
    foreach(temp_node, head) {
        printf("%d ", temp_node->val->val);
    }
}


Node *empty_stack(Node *head) {
    head->next = NULL;
    return head;
}

