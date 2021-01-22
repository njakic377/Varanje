#include<stdio.h>
#include<stdlib.h>
#define foreach(p, q) for(p=q->next; p!=NULL; p=p->next)

struct _node;
typedef struct _node Node;

struct _node {
    int val;
    Node* next;
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


Node *create_node(int val) {
    Node *node = (Node *)malloc(sizeof(Node));

    if(node == NULL) {
        printf("Memory allocation failed");
        return NULL;
    }

    node->val = val;
    node->next = NULL;

    return node;
}


Node *read_nums(char filename[], int lines) {
    FILE *file = fopen(filename, "r");

    if(file == NULL) {
        printf("Unable to open file");
        return NULL;
    }

    Node *head = (Node *)malloc(sizeof(Node));
    head->next = NULL;

    if(head == NULL) {
        printf("Memory allocation failed");
        return NULL;
    }

    Node *node_temp = head;

    for(int i=0; i<lines; i++) {
        int temp;
        fscanf(file, "%d",  &temp);
        node_temp->next = create_node(temp);
        node_temp = node_temp->next;
    }

    return head;
}


int print_list(Node *head) {
    Node *node_temp;

    foreach(node_temp, head) {
        printf("%d\n", node_temp->val);
    }

    return 0;
}


Node *copy_list(Node *head) {
    Node *head_new = create_node(0);
    Node *node_temp;
    Node *new_temp = head_new;

    foreach(node_temp, head) {
        new_temp->next = create_node(node_temp->val);
        new_temp = new_temp->next;
    }

    return head_new;
}


Node* unions(Node *head1, Node *head2) {
    Node *head_union = copy_list(head1);
    Node *node_before = head_union;
    Node *node_temp2, *node_temp1;
    int inserted = 0;

    foreach(node_temp2, head2) {
        inserted = 0;
        foreach(node_temp1, head_union) {
            if(node_temp1->val == node_temp2->val) {
                inserted = 1;
                break;
            };

            if(node_temp1->val > node_temp2->val) {
                Node *new_node = create_node(node_temp2->val);
                node_before->next = new_node;
                new_node->next = node_temp1;
                inserted = 1;
                break;
            }
            node_before = node_temp1;
        }

        if(!inserted) {
            Node *new_node = create_node(node_temp2->val);
            node_before->next = new_node;
        }
    }

    return head_union;
}


Node *intersect(Node *head1, Node *head2) {
    Node *node_temp1, *node_temp2;
    Node *head_inter = create_node(0);
    Node *inter_temp = head_inter;

    foreach(node_temp1, head1) {
        foreach(node_temp2, head2) {
            if(node_temp1->val == node_temp2->val) {
                inter_temp->next = create_node(node_temp1->val);
                inter_temp = inter_temp->next;
                break;
            }
        }
    }

    return head_inter;
}


int main() {
    int lines1 = count_lines("brojevi1.txt");
    int lines2 = count_lines("brojevi2.txt");

    Node *list1 = read_nums("brojevi1.txt", lines1);
    Node *list2 = read_nums("brojevi2.txt", lines2);

    print_list(list1);
    printf("\n");
    print_list(list2);
    printf("\n");

    Node *union_list = unions(list1, list2);
    Node *intersect_list = intersect(list1, list2);
    print_list(union_list);
    printf("\n");
    print_list(intersect_list);

    return EXIT_SUCCESS;
}
