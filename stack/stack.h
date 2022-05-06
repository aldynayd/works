#ifndef INC_2_1_STACK_H
#define INC_2_1_STACK_H

typedef struct {
    int rang;
    char *string;
} Element;

typedef struct {
    Element* data;
    int size;
    int capacity;
} vecStack;
typedef struct Node{
    char *str;
    int rang;
    struct Node *next;
} Node;
typedef struct {
    Node *top;
} listStack;

void push_vec(vecStack *stack, int rang,  char* string);
Element* pop_vec(vecStack *stack);
char * result_vec(char *string);
Node * push_list(char *string, int rang, listStack *stack);
Node * pop_list(listStack * stack);
char * result_list(char *string);
void output(char *str);
char* get_str();
#endif //INC_2_1_STACK_H
