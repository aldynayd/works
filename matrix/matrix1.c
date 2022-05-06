#include <stdio.h>
#include <malloc.h>
#include "matrix1.h"
#include <math.h>
// ввод целого числа
// приобнаружении ошибки ввод повторяется
// функция возвращает 1, если ввод корректен,
// и 0 при обнаружении конца файла
int getInt(int *a)
{
    int n;
    do{
        n = scanf("%d", a, sizeof(int));
        if (n < 0) // обнаружен конец файла
            return 0;
        if (n == 0){ // обнаружен некорректный символ - ошибка
            printf("%s\n", "Error! Repeat input");
            scanf("%*c", 0);
        }
    } while (n == 0);
    return 1;
}
// ввод вещественного числа
// при обнаружении ошибки ввод повторяется
// функция возвращает 1, если ввод корректен,
// и 0 при обнаружении конца файла
int getDouble(double *a)
{
    int n;
    do{
        n = scanf("%lf", a, sizeof(double));
        if (n < 0) // обнаружен конец файла
            return 0;
        if (n == 0){ // обнаружен некорректный символ - ошибка
            printf("%s\n", "Error! Repeat input");
            scanf("%*c", 0);
        }
    } while (n == 0);
    return 1;
}
// функция ввода матрицы
// функция возвращает 1, если ввод корректен, и 0 при обнаружении конца файла;
// если конец файла обнаружен в середине ввода - нужно освободить выделенную память
int input(Matrix *rm)
{
    const char *pr = ""; // будущее сообщение об ошибке
    int m; // количество строк матрицы
    int i, j;
    double *p;
// сначала вводим количество строк
    do{
        printf("%s\n", pr);
        printf("Enter number of lines: --> ");
        pr = "You are wrong; repeat, please!";
        if(getInt(&m) == 0)
            return 0; // обнаружен конец файла; память не выделялась
    } while (m < 1);
    rm->lines = m;
// выделяем память под массив структур - строк матрицы
    rm->matr = (Line *)calloc(m, sizeof(Line));
    for (i = 0; i < rm->lines; ++i){
// теперь для каждой строки матрицы вводим количество столбцов
        pr = "";
        do{
            printf("%s\n", pr);
            printf("Enter number of items in line %d: --> ", i + 1);
            pr = "You are wrong; repeat, please!";
            if (getInt(&m) == 0){
// освобождение выделенной памяти
                rm->lines = i; // сколько строк сформировано, память выделена
                erase(rm);
                return 0; // обнаружен конец файла
            }
        } while (m < 1);
        rm->matr[i].n = m;
// и выделяем необходимую память под элементы строки
        p = (double *)malloc(sizeof(double)* m);
        rm->matr[i].a = p;
// теперь можно вводить сами элементы данной строки матрицы
        printf("Enter items for matrix line #%d:\n", i + 1);
        for (j = 0; j < m; ++j, ++p)
            if (getDouble(p) == 0){
// освобождение выделенной памяти
                rm->lines = i + 1; // выделена память и под текущую, i-ю строку
                erase(rm);
                return 0;
            }
    }
    return 1;
}
// функция вывода
void output(const char *msg, Matrix a)
{
    int i, j;
    double *p;
    printf("%s:\n", msg);
    for (i = 0; i < a.lines; ++i){
        p = a.matr[i].a;
        for (j = 0; j < a.matr[i].n; ++j, ++p)
            printf("%10lf ", *p);
        printf("\n");
    }
}
// функция освобождения занятой памяти
void erase(Matrix *a)
{
    int i;
    for (i = 0; i < a->lines; ++i)
        free(a->matr[i].a);
    free(a->matr);
    a->lines = 0;
    a->matr = NULL;
}
// функция вычисления главного результата
Matrix *result(Matrix *pm)
{
    Matrix *newmatr = (Matrix *)malloc(sizeof(Matrix) *1);
    newmatr->lines = pm->lines;
    newmatr->matr = (Line *)malloc(sizeof(Line) *pm->lines);
    for (int i = 0; i < newmatr->lines; ++i){
        Line *line = linechange(&pm->matr[i]);
        newmatr->matr[i].a = line->a;
        newmatr->matr[i].n = line->n;
        free(line);
    }
    return newmatr;
}
void change(double *b, double *c){
    double h = *b;
    *b = *c;
    *c = h;
}
Line *linechange(Line *line) {
    Line *stroka = (Line *)malloc(sizeof(Line)* 1);
    stroka->a = (double *)malloc(sizeof(double)* line->n);
    stroka->n = line->n;
    double **max;
    double **min;
    int maxsize = 0;
    int minsize = 0;
    for (int i = 0; i < stroka->n; ++i){
        stroka->a[i] = line->a[i];
    }
    max = maxim(stroka, &maxsize);
    min = minim(stroka, &minsize);
    for (int j = 0; j < (minsize < maxsize ? minsize : maxsize); ++j) {
        change(max[j], min[j]);
    }
    free(max);
    free(min);
    return stroka;
}

double **maxim(Line *line, int *size)
{
    double **a = (double **)malloc(sizeof(double *)* line->n);
    *size = 0;
    double max = *line->a;
    for ( int i = 0; i < line->n; ++i){
        if (line->a[i] > max) {
            free(a);
            a = (double **)malloc(sizeof(double *)* line->n);
            *size = 0;
            max = line->a[i];
        }
        if (line->a[i] == max) {
            a[*size] = &line->a[i];
            (*size)++;
        }
    }
    return a;
}
double **minim(Line *line, int *size)
{
    double **a = (double **)malloc(sizeof(double *)* line->n);
    *size = 0;
    double min = *line->a;
    for ( int i = 0; i < line->n; ++i){
        if (line->a[i] < min) {
            free(a);
            a = (double **)malloc(sizeof(double *)* line->n);
            *size = 0;
            min = line->a[i];
        }
        if (line->a[i] == min) {
            a[*size] = &line->a[i];
            (*size)++;
        }
    }
    return a;
}
