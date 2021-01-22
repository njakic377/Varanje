#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define foreach(p, q) for(p=q->next; p!=NULL; p=p->next)
#define MIN_RAND 10
#define MAX_RAND 100

typedef struct _node Node;
typedef struct _node_double NodeDouble;

struct _node {
    double val;
    Node *next;
};


int count_lines(char filename[]) {
    FILE *file = fopen(filename, "r");
    char char_temp;
    int counter = 0;

    while(!feof(file)) {
        char_temp = fgetc(file); 

        if(char_temp == '\n') {
            counter += 1;
        }
    }

    fclose(file);

    return counter;
}


Node *create_node(double val) {
    Node *new_node = (Node *)malloc(sizeof(Node));

    if(new_node == NULL) {
        printf("Unable to allocate space");
        return NULL;
    }

    new_node->next = NULL;
    new_node->val = val;

    return new_node;
}


Node *push_to_stack(Node *head, double val) {
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


int print_list(Node *head) {
    Node *node_temp;

    foreach(node_temp, head) {
        printf("%lf\n", node_temp->val);
    }

    return 0;
}


double apply_operator(double num1, double num2, char *operator) {
    switch(operator[0]) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            return num1 / num2;
    }

    return 0;
}


Node *on_read(Node *head, char *val) {
    char *endptr;

    double result = strtod(val, &endptr);
    if(*endptr != '\0') {
        printf("Ovo je string: %s\n", val);
        double num1 = pop_from_stack(head)->val;
        double num2 = pop_from_stack(head)->val;

        push_to_stack(head, apply_operator(num2, num1, val));
        printf("STACK:\n");
        print_list(head);
        printf("\n");
    } else {
        printf("Ovo je broj: %lf\n", result);
        push_to_stack(head, result);

        printf("STACK:\n");
        print_list(head);
        printf("\n");
    }
    
    return head;
}


Node *read_expr(char *filename, int length) {
    int i;
    FILE *file = fopen(filename, "r");
    char element[20];

    Node *head = create_node(0);

    for(i=0; i<length; i++) {
        fscanf(file, "%s", element);
        on_read(head, strdup(element));
    }

    return head;
}


int main() {
    int lines_count = count_lines("expression.txt");
    printf("Lines count: %d \n", lines_count);

    Node *stack = read_expr("expression.txt", lines_count);


    printf("\n");
    printf("Rezultat je:\n");
    Node *poped = pop_from_stack(stack);
    printf("%lf\n", poped->val);

    return 0;
}
