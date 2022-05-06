#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"
char* get_str() {
    int n, len, len_res = 0;
    char buf[51];
    char* res = NULL;
    do {
        n = scanf("%50[^\n]", buf);
        if (n < 0) {
            if (!res) return NULL;
        }
        else if (n > 0) {
            len = (int)strlen(buf);
            len_res += len;
            res = (char *)realloc(res, (len_res + 1) * sizeof(char));
            memcpy(res + len_res - len, buf, len);
        }
        else {
            scanf("%*c");
        }
    } while (n > 0);
    if (len_res > 0) {
        res[len_res] = '\0';
    }
    else {
        res = (char*)calloc(1, sizeof(char));
    }
    return res;
}
void push_vec(vecStack *stack, int rang,  char* string) {
    if (stack->size == stack->capacity) {
        if (stack->capacity == 0) stack->capacity = 1;
        stack->data = (Element *)realloc(stack->data, sizeof(Element)*2*(stack->capacity));
        //(*stack).data
        stack->capacity = 2 * stack->capacity;
    }
    (stack->data)[stack->size].string = (char *)malloc(sizeof(char) * (strlen(string) + 1));
    (stack->data)[stack->size].rang = rang;
    strcpy((stack->data)[stack->size].string, string);
    stack->size++;
}
Element* pop_vec(vecStack *stack) {
    Element *el = (Element *)malloc(sizeof(Element));
    if (stack->size == 0) {
        printf("Stack is empty");
        return NULL;
    }
    stack->size--;
    el->string = (char *)malloc(sizeof(char) * (strlen((stack->data)[stack->size].string) + 1));
    strcpy(el->string,(stack->data)[stack->size].string);
    el->rang = (stack->data)[stack->size].rang;
    free((stack->data)[stack->size].string);
    return el;
}
char * result_vec(char *string) {
    vecStack * stack = (vecStack *)malloc(sizeof(vecStack) * 1);
    stack->data = NULL;
    char * new_str = NULL;
    int size;
    int sign = 1;
    Element *el1;
    Element *el2;
    stack->size = 0;
    stack->capacity = 0;
    for (size = 0; size < strlen(string); ++size) {
        if (string[size] == '+') {
            el1 = pop_vec(stack);
            el2 = pop_vec(stack);
            char *p = (char *) malloc(sizeof(char) * (strlen(el1->string) + strlen(el2->string) + 5));
            snprintf(p, (strlen(el1->string) + strlen(el2->string) + 4), "%s + %s", el1->string, el2->string);
            p[strlen(el1->string) + strlen(el2->string) + 3] = '\0';
            push_vec(stack, 0, p);
            sign = 1;
            free(p);
            free(el2->string);
            free(el1->string);
            free(el1);
            free(el2);
        } else if (string[size] == '-') {
            el1 = pop_vec(stack);
            el2 = pop_vec(stack);
            char *p = (char *) malloc(sizeof(char) * (strlen(el1->string) + strlen(el2->string) + 5));
            snprintf(p, (strlen(el1->string) + strlen(el2->string) + 4), "%s - %s", el1->string, el2->string);
            push_vec(stack, 0, p);
            sign = 1;
            free(p);
            free(el2->string);
            free(el1->string);
            free(el1);
            free(el2);
        } else if (string[size] == '*' || string[size] == '/') {
            el1 = pop_vec(stack);
            el2 = pop_vec(stack);
            char *p;
            if (el1->rang == 0 && el2->rang == 0) {
                p = (char *) malloc(sizeof(char) * (strlen(el1->string) + strlen(el2->string) + 9));
                snprintf(p, (strlen(el1->string) + strlen(el2->string) + 8), "(%s) %c (%s)", el1->string, string[size],
                         el2->string);
                p[strlen(el1->string) + strlen(el2->string) + 7] = '\0';
                push_vec(stack, 1, p);
            } else if (el1->rang == 0) {
                p = (char *) malloc(sizeof(char) * (strlen(el1->string) + strlen(el2->string) + 7));
                snprintf(p, (strlen(el1->string) + strlen(el2->string) + 6), "(%s) %c %s", el1->string, string[size],
                         el2->string);
                p[strlen(el1->string) + strlen(el2->string) + 5] = '\0';
                push_vec(stack, 1, p);
            } else if (el2->rang == 0) {
                p = (char *) malloc(sizeof(char) * (strlen(el1->string) + strlen(el2->string) + 7));
                snprintf(p, (strlen(el1->string) + strlen(el2->string) + 6), "%s %c (%s)", el1->string, string[size],
                         el2->string);
                p[strlen(el1->string) + strlen(el2->string) + 5] = '\0';
                push_vec(stack, 1, p);
            } else  { //if (node2->rang == 1 && node1->rang == 1)
                p = (char *)malloc(sizeof(char) * (strlen(el1->string) + strlen(el2->string) + 5));
                snprintf(p, (strlen(el1->string) + strlen(el2->string) + 4), "%s %c %s", el1->string, string[size], el2->string);
                //p[strlen(el1->string) + strlen(el2->string) + 3] = '\0';
                push_vec(stack, 1, p);
            }
            sign = 1;
            free(p);
            free(el2->string);
            free(el1->string);
            free(el1);
            free(el2);
        } else if (string[size] != ' ') {
            if (new_str != NULL) {
                char *p = (char *) malloc(sizeof(char) * (strlen(new_str) + 2));
                snprintf(p, (strlen(new_str) + 2), "%s%c", new_str, string[size]);
                p[strlen(new_str) + 1] = '\0';
                free(new_str);
                new_str = p;
            } else {
                new_str = (char *) malloc(sizeof(char) * 2);
                new_str[0] = string[size];
                new_str[1] = '\0';
            }
            sign = 0;
        } else if (string[size] == ' ') {
            if (sign == 0) {                              // в прошлый раз между пробелами выражение
                push_vec(stack, 2, new_str);
                free(new_str);
                new_str = NULL;
            }
            sign = 1;
        }
    }
    new_str = (char *)malloc(sizeof(char) * strlen(stack->data->string) + 1);
    strcpy(new_str, stack->data->string);
    free(stack->data->string);
    free(stack->data);
    free(stack);
    return new_str;
}

Node * push_list(char *string, int rang, listStack *stack) {
    Node *newnode;
    newnode = (Node *)malloc(sizeof(Node) * 1);
    newnode->str = (char *)malloc(sizeof(char) * strlen(string) + 1); // + \0
    newnode->rang = rang;
    strcpy(newnode->str, string);
    newnode->next = stack->top;
    stack->top = newnode;
    return newnode;
}
Node * pop_list(listStack * stack){
    Node *newnode;
    if (stack->top == NULL) {
        printf("Stack is empty");
        return NULL;
    }
    newnode = stack->top;
    stack->top = newnode->next;
    newnode->next = NULL;
    return newnode;
}
char * result_list(char *string) {
    listStack *stack = (listStack *)malloc(sizeof(listStack) * 1);
    stack->top = NULL;
    char *new_str = NULL; //*(new_str + 1) == new_str[1] == 1[new_str]
    Node * node1;
    Node * node2;
    int sign = 1;
    for (int i = 0; i < strlen(string); ++i){
        if (string[i] == '+') {
            node2 = pop_list(stack);
            node1 = pop_list(stack);
            char * p = (char *)malloc(sizeof(char) * (strlen(node1->str) + strlen(node2->str) + 5));
            snprintf(p, (strlen(node1->str) + strlen(node2->str) + 4), "%s + %s", node1->str, node2->str);
            p[strlen(node1->str) + strlen(node2->str) + 3] = '\0';
            push_list(p, 0, stack);
            sign = 1;
            free(node2->str);
            free(node1->str);
            free(node2);
            free(node1);
            free(p);
        }
        else if (string[i] == '-') {
            node1 = pop_list(stack);
            node2 = pop_list(stack);
            char * p = (char *)malloc(sizeof(char) * (strlen(node1->str) + strlen(node2->str) + 5));
            snprintf(p, (strlen(node1->str) + strlen(node2->str) + 4), "%s - %s", node1->str, node2->str);
            p[strlen(node1->str) + strlen(node2->str) + 3] = '\0';
            push_list(p, 0, stack);
            sign = 1;
            free(node2->str);
            free(node1->str);
            free(node2);
            free(node1);
            free(p);
        }
        else if (string[i] == '*' || string[i] == '/') {
            node1 = pop_list(stack);
            node2 = pop_list(stack);
            char * p;
            if (node1->rang == 0 && node2->rang == 0) {
                p = (char *)malloc(sizeof(char) * (strlen(node1->str) + strlen(node2->str) + 9));
                snprintf(p, (strlen(node1->str) + strlen(node2->str) + 8), "(%s) %c (%s)", node1->str, string[i], node2->str);
                p[strlen(node1->str) + strlen(node2->str) + 7] = '\0';
                push_list(p, 1, stack);
            }
            else if (node1->rang == 0) {
                p = (char *)malloc(sizeof(char) * (strlen(node1->str) + strlen(node2->str) + 7));
                snprintf(p, (strlen(node1->str) + strlen(node2->str) + 6), "(%s) %c %s", node1->str, string[i], node2->str);
                p[strlen(node1->str) + strlen(node2->str) + 5] = '\0';
                push_list(p, 1, stack);
            }
            else if (node2->rang == 0) {
                p = (char *)malloc(sizeof(char) * (strlen(node1->str) + strlen(node2->str) + 7));
                snprintf(p, (strlen(node1->str) + strlen(node2->str) + 6), "%s %c (%s)", node1->str, string[i], node2->str);
                p[strlen(node1->str) + strlen(node2->str) + 5] = '\0';
                push_list(p, 1, stack);
            }
            else  { //if (node2->rang == 1 && node1->rang == 1)
                p = (char *)malloc(sizeof(char) * (strlen(node1->str) + strlen(node2->str) + 5));
                snprintf(p, (strlen(node1->str) + strlen(node2->str) + 4), "%s %c %s", node1->str, string[i], node2->str);
                p[strlen(node1->str) + strlen(node2->str) + 3] = '\0';
                push_list(p, 1, stack);
            }
            sign = 1;
            free(node2->str);
            free(node1->str);
            free(node2);
            free(node1);
            free(p);
        }
        else if (string[i] != ' ') {
            if (new_str != NULL) {
                char * p = (char *)malloc(sizeof(char ) * (strlen(new_str) + 2));
                snprintf(p, (strlen(new_str) + 1), "%s%c", new_str, string[i]);
                p[strlen(new_str) + 1] = '\0';
                sign = 0;
                free(new_str);
                new_str = p;
            }
            else {
                new_str = (char  *)malloc(sizeof(char ) *2);
                new_str[0] = string[i];
                new_str[1] = '\0';
                sign = 0;
            }
        }
        else if (string[i] == ' ') {
            if (sign == 0) {                              // в прошлый раз между пробелами выражение
                push_list(new_str, 2, stack);
                free(new_str);
                new_str = NULL;
            }
        }
    }
    new_str = stack->top->str;
    free(stack->top);
    free(stack);
    return new_str;
}
void output(char *str) {
    printf("result:\n");
    for (int i=0; i < strlen(str); ++i) {
        printf("%c", str[i]);
    }
}
