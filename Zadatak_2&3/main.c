#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    char *surname;
    unsigned int year_that_brought_you_in;
} Person;

typedef struct Node {
    Person *val;
    struct Node *next;

} Node;

Node *create_node(Person *person);
Person *create_person(char name[], char surname[], unsigned int year_that_brought_you_in);
Node *prepend(Node *element, Person *person);
Node *append(Node *element, Person *person);
int insert_before(Node *root, Person *person, Person *new_person);
int insert_after(Node *root, Person *person, Person *new_person);
int print_list(Node *root);
Node *find_node_by_person(Node *root, Person *person);
Person *find_by_last_name(Node *root, char surname[]);
int delete_person(Node *root, Person *person_del);
int sort(Node *root);

int main()
{
     Node *list_root;

    list_root = (Node *)malloc(sizeof(Node));

    Person *p1 = create_person("Vladimir", "Bartic", 2016);
    Person *p2 = create_person("Martin", "Foten", 2003);
    Person *p3 = create_person("Josip", "Korten", 2000);
    Person *p4 = create_person("Teddy", "Maul", 2009);
    Person *p5 = create_person("Stipe", "Kosuta", 1977);

    append(list_root, p1);
    append(list_root, p2);
    append(list_root, p1);
    append(list_root, p3);
    append(list_root, p1);
    print_list(list_root->next);

    Person *person_searched = find_by_last_name(list_root->next, "Korten");
    if(person_searched != NULL) {
        printf(
                "\n%s %s %d\n",
                person_searched->name,
                person_searched->surname,
                person_searched->year_that_brought_you_in
              );
    }
    printf("\n");
    delete_person(list_root, person_searched);
    print_list(list_root->next);

    printf("\n");
    insert_after(list_root, p2, p4);
    print_list(list_root->next);

    printf("\n");
    insert_before(list_root, p2, p5);
    print_list(list_root->next);

    printf("\n");
    sort(list_root);
    print_list(list_root->next);

}










Node *create_node(Person *person) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->val = person;
    new_node->next = NULL;

    return new_node;
}

Person *create_person(char name[], char surname[], unsigned int year_that_brought_you_in) {
    Person *new_person = (Person *)malloc(sizeof(Person));

    new_person->name = strdup(name);
    new_person->surname = strdup(surname);
    new_person->year_that_brought_you_in = year_that_brought_you_in;

    return new_person;
}

Node *prepend(Node *root, Person *person) {
    Node *new_node = create_node(person);

    new_node->next = root->next;
    root->next = new_node;

    return new_node;
}

Node *append(Node *root, Person *person) {
    Node *new_node = create_node(person);

    Node *last_node = root;
    while(last_node->next != NULL) {
        last_node = last_node->next;
    }

    last_node->next = new_node;

    return new_node;
}

int print_list(Node *root) {
    Node *node_temp = root;
    Person *node_val;

    while(node_temp != NULL) {
        node_val = node_temp->val;
        printf(
                "%s %s %d\n",
                node_val->name,
                node_val->surname,
                node_val->year_that_brought_you_in
              );
        node_temp = node_temp->next;
    }

    return 0;
}

Person *find_by_last_name(Node *root, char surname[]) {
    Node *node_temp = root;
    Person *node_val;

    while(node_temp != NULL) {
        node_val = node_temp->val;
        if(strcmp(node_val->surname, surname) == 0) {
            return node_val;
        }
        node_temp = node_temp->next;
    }

    return NULL;
}

int delete_person(Node *root, Person *person_del) {
    Node *node_temp = root;
    Node *last_node = NULL;

    while(node_temp != NULL) {
        if(node_temp->val == person_del) {
            last_node->next = node_temp->next;
            free(node_temp->val);
            free(node_temp);
            return 0;
        }
        last_node = node_temp;
        node_temp = node_temp->next;
    }
    return 1;
}

int insert_before(Node *root, Person *person, Person *new_person) {
    Node *node_temp = root;
    Node *last_node = NULL;
    Node *new_node = create_node(new_person);

    while(node_temp != NULL) {
        if(last_node != NULL && node_temp->val == person) {
            last_node->next = new_node;
            new_node->next = node_temp;
            return 0;
        }
        last_node = node_temp;
        node_temp = node_temp->next;
    }

    return 1;
}

int insert_after(Node *root, Person *person, Person *new_person) {
    Node *node_temp = root;
    Node *last_node = NULL;
    Node *new_node = create_node(new_person);

    while(node_temp != NULL) {
        if(last_node != NULL && last_node->val == person) {
            last_node->next = new_node;
            new_node->next = node_temp;
            return 0;
        }
        last_node = node_temp;
        node_temp = node_temp->next;
    }

    return 1;
}

int sort(Node *root) {
    Node *node_temp, *node_next_temp;

    Person *val_temp, *val_next_temp;

    for(node_temp=root->next; node_temp!=NULL; node_temp=node_temp->next) {
        for(node_next_temp=root->next; node_next_temp->next!=NULL; node_next_temp=node_next_temp->next) {

            val_temp = node_next_temp->val;
            val_next_temp = node_next_temp->next->val;

            if(strcmp(val_temp->surname, val_next_temp->surname) > 0) {
                node_next_temp->val = val_next_temp;
                node_next_temp->next->val = val_temp;
            }
        }
    }

    return 0;
}
