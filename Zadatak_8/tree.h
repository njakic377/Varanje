typedef struct _tree Tree;

struct _tree {
    char *name;
    Tree *next_sibling;
    Tree *first_child;
};

char *str_duplicate(char *old);
Tree *create_leaf(char *name);
Tree *add_child(Tree *where, char *what);
Tree *add_sibling(Tree *where, char *what);
Tree *find_child(Tree *from, char *what);
void print_children(Tree *head);


typedef struct _stack Node;

struct _stack {
    Tree *val;
    Node *next;
};

Node *create_node(Tree *val);
Node *pop_from_stack(Node *head);
Node *push_to_stack(Node *head, Tree *val);
