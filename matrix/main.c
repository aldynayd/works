/*Из входного потока вводится непрямоугольная матрица целых чисел [aij ], i = 1, . . . , m, j = 1, . . . , ni
Значения m и ni заранее не известны и вводятся из входного потока.
Сформировать новую матрицу, поменяв в каждой строке местами максимальный и минимальный элементы
(все, если их несколько).
Исходную и полученную матрицы вывести в выходной поток с необходимыми комментариями.*/

#include <stdio.h>
#include "matrix1.h"
#include <malloc.h>

int main() {
    Matrix matr = {0, NULL};
    Matrix *matrix;
    if (input(&matr) == 0){
        printf("%s\n", "End of file occured");
        return 1;
    }
    matrix = result(&matr);
    output("Source matrix", matr);
    output("Result:\n", *matrix);
    erase(&matr); // освобождение памяти
    erase(matrix);
    free(matrix);
    return 0;
}
