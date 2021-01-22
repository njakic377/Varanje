#include<stdio.h>
#include<stdlib.h>

#define foreach(p, q) for(p=q->next; p!=NULL; p=p->next)

struct Expression {
    int base;
    int exponent;
};

typedef struct Expression Expression;

struct Polinome {
    Expression *val;
    struct Polinome *next;
};

typedef struct Polinome Polinome;


Expression *create_expr(int base, int exponent) {
    Expression *expr = (Expression *)malloc(sizeof(Expression));

    expr->base = base;
    expr->exponent = exponent;

    return expr;
}


Polinome *create_polinome(Expression *expr) {
    Polinome *pol = (Polinome *)malloc(sizeof(Expression));

    pol->val = expr;
    pol->next = NULL;

    return pol;
}


Polinome *copy_polinome(Polinome *root) {
    Polinome *root_new = (Polinome *)malloc(sizeof(Polinome));
    Polinome *pol_new_temp = root_new;
    Polinome *pol_temp = root->next;

    while(pol_temp!=NULL) {
        Expression *expr_temp = pol_temp->val;
        Expression *expr_copy = create_expr(expr_temp->base, expr_temp->exponent);
        Polinome *pol_copy = create_polinome(expr_copy);

        pol_new_temp->next = pol_copy;
        pol_temp = pol_temp->next;
        pol_new_temp = pol_new_temp->next;
    }

    return root_new;
}


int print_polinome(Polinome *root) {
    Polinome *pol_temp;
    Expression *expr_temp;

    foreach(pol_temp, root) {
        expr_temp = pol_temp->val;
        printf("%dx^%d\n", expr_temp->base, expr_temp->exponent);
    }
    return 0;
}


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


Expression *validate_expr(Expression *expr) {
    if(expr->base == 0 || expr->exponent == 0) {
        return NULL;
    }

    return expr;
}


Polinome *insert_polinome(Polinome *root, Expression *expr_new) {
    if(validate_expr(expr_new) == NULL) return root;

    Polinome *pol_new = create_polinome(expr_new);

    if(root->next == NULL) {
        root->next = pol_new;
        return root;
    }

    Polinome *pol_temp, *pol_last = root;
    foreach(pol_temp, root) {
        if(pol_temp->val->exponent > expr_new->exponent) {
            pol_last->next = pol_new;
            pol_new->next = pol_temp;
            return root;
        }

        if(pol_temp == NULL) break;

        pol_last = pol_temp;
    }

    pol_last->next = pol_new;
    return root;
}


Polinome *read_polinome(int lines_count, char filename[]) {
    FILE *file = fopen(filename, "r");

    Polinome *root = (Polinome *)malloc(sizeof(Polinome));
    root->val = NULL;
    root->next = NULL;

    int temp_base, temp_exp, i;
    Expression *expr_temp;

    for(i=0; i<lines_count; i++) {
        fscanf(file, "%d %d", &temp_base, &temp_exp);
        expr_temp = create_expr(temp_base, temp_exp);
        insert_polinome(root, expr_temp);
    }

    fclose(file);
    return root;
}


Expression *find_same_power(Polinome *root, Expression *expr) {
    Polinome *pol_temp = root->next;

    while(pol_temp!=NULL) {
        if(pol_temp->val->exponent == expr->exponent)
            return pol_temp->val;
        pol_temp = pol_temp->next;
    }

    return NULL;
}

Polinome *add_polinomes(Polinome *root1, Polinome *root2) {
    Polinome *pol_sum = copy_polinome(root1);
    Polinome *pol2_temp;

    foreach(pol2_temp, root2) {
        Expression *same_power = find_same_power(pol_sum, pol2_temp->val);

        if(same_power!=NULL) {
            same_power->base += pol2_temp->val->base;
            continue;
        }

        Expression *expr_new = create_expr(
                pol2_temp->val->base,
                pol2_temp->val->exponent
                );
        insert_polinome(pol_sum, expr_new);
    }

    return pol_sum;
}


Polinome *multiply_polinomes(Polinome *root1, Polinome *root2) {
    Polinome *pol_sum = create_polinome(NULL);
    Polinome *pol2_temp, *pol1_temp;

    foreach(pol2_temp, root2)
        foreach(pol1_temp, root1){
            Expression *new_expr = create_expr(
                    pol2_temp->val->base * pol1_temp->val->base,
                    pol2_temp->val->exponent + pol1_temp->val->exponent
                    );

            insert_polinome(pol_sum, new_expr);
        }
    return pol_sum;
}


int main() {
    int lines_count1 = count_lines("polinom1.txt");
    Polinome *root1 = read_polinome(lines_count1, "polinom1.txt");

    int lines_count2 = count_lines("polinom2.txt");
    Polinome *root2 = read_polinome(lines_count2, "polinom2.txt");

    print_polinome(root1);

    printf("First polinome: \n");
    print_polinome(root1->next);
    printf("\n");
    printf("Second polinome: \n");
    print_polinome(root2->next);
    printf("\n");

    Polinome *pol_sum = add_polinomes(root1, root2);
    printf("Polinome sum: \n");
    print_polinome(pol_sum->next);
    printf("\n");

    Polinome *pol_mult = multiply_polinomes(root1, root2);
    printf("Polinome mult: \n");
    print_polinome(pol_mult->next);
    printf("\n");

    return 0;
}
