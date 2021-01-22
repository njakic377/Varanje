typedef struct _stack Node;
typedef struct _tree Tree;

struct _tree {
    int val;
    Tree *ptr_left;
    Tree *ptr_right;
};

struct _stack {
    Tree *val;
    Node *next;
};


void print_stack(Node *head);
Node *create_node(Tree *val);
Node *pop_from_stack(Node *head);
Node *push_to_stack(Node *head, Tree *val);
Node *empty_stack(Node *head);
