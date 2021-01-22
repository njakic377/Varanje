#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define foreach(p, q) for(p=q->next; p!=NULL; p=p->next)
#define MIN_RAND 10
#define MAX_RAND 100

typedef struct _node Node;

struct _node {
    int val;
    Node *next;
};


Node *create_node(int val) {
    Node *new_node = (Node *)malloc(sizeof(Node));

    if(new_node == NULL) {
        printf("Unable to allocate space");
        return NULL;
    }

    new_node->next = NULL;
    new_node->val = val;

    return new_node;
}


int get_random_val() {
    int val = (rand() % (MAX_RAND - MIN_RAND + 1)) +
        MIN_RAND;

    return val;
}


Node *push_to_queue(Node *head) {
    int val = get_random_val();

    printf("Random val %d\n", val);

    Node *new_node = create_node(val);

    new_node->next = head->next;
    head->next = new_node;

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


Node *push_to_stack(Node *head) {
    return push_to_queue(head);	
}


Node *find_penultimate(Node *head) {
    Node *node_temp;
    Node *node_last = head;

    foreach(node_temp, head) {
        if(node_temp->next == NULL) {
            return node_last;
        } 
        node_last = node_temp;
    }

    return NULL;
}

Node *pop_from_queue(Node *head) {
    if(head->next == NULL) {
        printf("No elements to pop");
        return NULL;
    }

    Node *penultimate = find_penultimate(head);

    if(penultimate == NULL) return NULL;

    Node *node_temp = penultimate->next;
    penultimate->next = NULL;

    return node_temp;
}


void print_list(Node *head) {
    Node *node_temp;

    foreach(node_temp, head) {
        printf("%d\n", node_temp->val);
    }
}




int main() {
    srand(time(0));

    Node *stack_head = create_node(0);

    printf("GENERATED: \n");
    push_to_stack(stack_head);
    push_to_stack(stack_head);
    push_to_stack(stack_head);
    printf("\n");

    print_list(stack_head);

    printf("\nPoped element:\n");
    Node *poped = pop_from_stack(stack_head);
    printf("%d\n", poped->val);
    printf("\n");


    Node *queue_head = create_node(0);

    printf("GENERATED: \n");
    push_to_stack(queue_head);
    push_to_stack(queue_head);
    push_to_stack(queue_head);
    printf("\n");

    print_list(queue_head);

    printf("\nPoped element:\n");
    Node *poped2 = pop_from_queue(queue_head);
    printf("%d\n", poped2->val);
}
