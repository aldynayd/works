#ifndef INC_1_2_2022_MATRIX_H
#define INC_1_2_2022_MATRIX_H
#include <stdio.h>
#include <malloc.h>

// структура для задания строки матрицы
typedef struct Line{
    int n; // количество элементов в строке матрицы
    double *a; // массив элементов
} Line;
// структура для задания самой матрицы
typedef struct Matrix{
    int lines; // количество строк матрицы
    Line *matr; // массив строк матрицы
} Matrix;

int getInt(int *); // ввод целого числа
int getDouble(double *); // ввод вещественного числа
int input(Matrix *a); // ввод матрицы
void output(const char *msg, Matrix a); // вывод матрицы
Matrix *result(Matrix *pm);
Line *linechange(Line *line);
double **maxim(Line *line, int *size);
double **minim(Line *line, int *size);
void erase(Matrix *a); // освобождение занятой памяти

#endif //INC_1_2_2022_MATRIX_H
