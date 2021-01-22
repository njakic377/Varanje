#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include"tree.h"

#define foreach_child(p, q) for(p=q->first_child; p!=NULL; p=p->next_sibling)

extern int errno;


char *str_duplicate(char *old) {
    char *copy = malloc(strlen(old) + 1);

    if(copy == NULL) {
        perror("Error allocating memory"); 
        exit(1);
    }

    strcpy(copy, old);
    return old;
}


Tree *create_leaf(char *name) {
    Tree *new_leaf = (Tree *)malloc(sizeof(Tree));

    if(new_leaf == NULL) {
        perror("Error allocating memory"); 
        exit(1);
    }

    new_leaf->name = str_duplicate(name);
    new_leaf->next_sibling = NULL;
    new_leaf->first_child = NULL;

    return new_leaf;
}


Tree *add_child(Tree *where, char *what) {
    if(where->first_child == NULL) {
        Tree *new_leaf = create_leaf(what);
        where->first_child = new_leaf;
        return new_leaf;
    }

    return add_sibling(where->first_child, what);
}


Tree *add_sibling(Tree *root, char *name) {  //Funkcija za dodavanje na kraj liste
    Tree *new_leaf = create_leaf(name);

    Tree *last_leaf = root;
    while(last_leaf->next_sibling != NULL) {
        last_leaf = last_leaf->next_sibling;
    }

    last_leaf->next_sibling = new_leaf;

    return new_leaf;
}


Tree *find_child(Tree *from, char *what) {
    Tree *leaf_temp = from;

    foreach_child(leaf_temp, from) {
        if(strcmp(leaf_temp->name, what) == 0) {
            return leaf_temp;
        }
    }

    return NULL;
}


void print_children(Tree *head) {
    Tree *leaf_temp;

    foreach_child(leaf_temp, head) {
        printf("%s\n", leaf_temp->name);
    }
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
