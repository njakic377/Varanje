#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tree.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct _command Command;

struct _command {
    char *command;
    char *arg;
};


Command *create_command(char *cmd, char *arg) {
    Command *new_command = (Command *)malloc(sizeof(Command));

    if(new_command == NULL) {
        perror("Error allocating memory"); 
        exit(1);
    }

    new_command->command = cmd;
    new_command->arg = arg;

    return new_command;
}


Command *get_new_command() {
    char input[20];
    char cmd[10];
    char arg[10];

    fgets(input, 20, stdin);
    sscanf(input, "%s %s", cmd, arg);

    Command *new_command = create_command(strdup(cmd), strdup(arg));

    return new_command;
}

Tree *md(Tree *current, char *name){
    Tree *new_child = add_child(current, name);
    return new_child;
}


Tree *cd(Tree **current, char *where, Node *stack_head, char *path) {
    if(strcmp(where, "..") == 0) {
        Node *poped = pop_from_stack(stack_head);
        int path_size = strlen(path); 
        int poped_name_size = strlen(poped->val->name);
        path[path_size - poped_name_size - 1] = '\0';        
        if(stack_head->next == NULL) { printf("Can't go back."); return NULL; }
        *current = stack_head->next->val;
        return *current;
    }

    Tree *child = find_child(*current, where);
    if(child == NULL) {
        printf("cd: no such file or directory: %s\n", where);
        return NULL;
    }
    *current = child;
    push_to_stack(stack_head, child);
    strcat(path, "/");
    strcat(path, (*current)->name);

    return child;
}


char is_cmd(Command *cmd, char *str) {
    return strcmp(cmd->command, str) == 0;
}

int execute_command(Command *command, Tree *current, Node *stack_head, char *path) {
    if(is_cmd(command, "mkdir")) {
        Tree *new_dir = md(current, command->arg);
    }
    else if(is_cmd(command, "ls")) {
        print_children(current);
    }
    else if(is_cmd(command, "cd")) {
        cd(&current, command->arg, stack_head, path);
    }
    else if(is_cmd(command, "exit")) {
        exit(0);
    } else {
        printf("jsh: command not found: %s\n", command->command);
    }

    return 0;
}


int main() {
    Tree *current = create_leaf("~");
    Node *stack_head = create_node(NULL);
    char path[100] = "~";
    Command *comm;

    push_to_stack(stack_head, current);

    while(1) {
        printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, path);
        printf(ANSI_COLOR_RED " >> " ANSI_COLOR_RESET);
        comm = get_new_command();
        execute_command(comm, current, stack_head, path);
    }

}

