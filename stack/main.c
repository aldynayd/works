/** Вариант 005
 * ДЛя математической формулы, представленной в постфиксной нотации, сформировать ее инфиксное представление.
 * Вводимая формула может включать в себя буквы английского алфавита ("переменные"), а также следующие операторы: +, -, *, /
 * Для осуществления преобразования необходимо использовать логическую структуру данных стек. */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"

int main() {
    char * str;
    char * res;
    int i;
    printf("1.Vector\n2.List\n");
    scanf("%d", &i);
    scanf("%*c");
    printf("String:\n");
    str = get_str();
    if (i == 1) res = result_vec(str);
    if (i == 2) res = result_list(str);
    output(res);
    free(str);
    free(res);
 }