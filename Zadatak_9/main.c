#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

#define foreach(p, q) for(p=q->next; p!=NULL; p=p->next)
#define is_equal(t, v) (t != NULL && t->val == v)

typedef struct _tree Tree;


Tree *create_tree(int val) {
    Tree *new_tree = (Tree *)malloc(sizeof(Tree));
    
    if(new_tree == NULL) {
        printf("Error: Can't allocate memory.");
        exit(1); 
    }

    new_tree->val = val;
    new_tree->ptr_right = new_tree->ptr_left = NULL;

    return new_tree;
}


void print_tree_util(Node *curr_stack, Node *temp_stack) {
    print_stack(curr_stack);
    printf("\n");

    if(curr_stack->next == NULL) { return; }

    Node *temp_node;
    Tree *temp_tree;
    foreach(temp_node, curr_stack) {
        temp_tree = temp_node->val;

        if(temp_tree->ptr_right != NULL) {
            push_to_stack(temp_stack, temp_tree->ptr_right);
        }

        if(temp_tree->ptr_left != NULL) {
            push_to_stack(temp_stack, temp_tree->ptr_left);
        }
    }

    empty_stack(curr_stack);

    print_tree_util(temp_stack, curr_stack);
}


void print_tree(Tree *root) {
    Node *curr_stack = create_node(0);
    Node *temp_stack = create_node(0);

    push_to_stack(curr_stack, root);

    print_tree_util(curr_stack, temp_stack);
}


Tree *insert_node(Tree *root, int val) {
    if(root == NULL) { return create_tree(val); }
    else if(val < root->val) { root->ptr_left = insert_node(root->ptr_left, val); }
    else if(val > root->val) { root->ptr_right = insert_node(root->ptr_right, val); }

    return root;
}


Tree *reinsert_util(Tree *root, Tree *what) {
    if(root == NULL) { return what; }
    else if(what->val < root->val) { root->ptr_left = reinsert_util(root->ptr_left, what); }
    else if(what->val > root->val) { root->ptr_right = reinsert_util(root->ptr_right, what); }

    return root;
}


Tree *reinsert(Tree *root, Tree *what) {
    if(what == NULL) { return NULL; }

    return reinsert_util(root, what);
}


Tree *find(Tree *root, int val) {
    if(root == NULL) {
        printf("Can't find element %d\n", val);
        return NULL;
    }
    else if(is_equal(root, val)) {
        return root;
    }
    else if(val < root->val) { return find(root->ptr_left, val); }
    else if(val > root->val) { return find(root->ptr_right, val); }

    return NULL;
}



Tree *find_parent(Tree *root, int val) {
    if(root == NULL) {
        printf("Can't find element %d\n", val);
        return NULL;
    }
    else if (is_equal(root->ptr_left, val) || is_equal(root->ptr_right, val)) {
        return root;
    }
    else if(val < root->val) { return find_parent(root->ptr_left, val); }
    else if(val > root->val) { return find_parent(root->ptr_right, val); }

    return NULL;
}


Tree *delete_node(Tree *root, int val) {
    Tree *parent = find_parent(root, val);
    Tree *to_delete = NULL;

    if(parent == NULL) { return NULL; } 

    if(val < parent->val) {
        to_delete = parent->ptr_left;
        parent->ptr_left = NULL;
    }
    else if(val > parent->val) {
        to_delete = parent->ptr_right;
        parent->ptr_right = NULL;
    }

    if(to_delete != NULL) {
        reinsert(root, to_delete->ptr_left);
        reinsert(root, to_delete->ptr_right);
    }

    return NULL;
}

int main() {
    Tree *root = create_tree(10);
    insert_node(root, 15);
    insert_node(root, 5);
    insert_node(root, 20);
    insert_node(root, 7);
    insert_node(root, 3);

    print_tree(root);

    Tree *found = find(root, 20);
    printf("I found: %d\n", found->val);

    delete_node(root, 15);

    print_tree(root);
}
