#include <stdio.h>
typedef struct Item {
//    char * info;
    int key1;
    int key2;
    int strnum_key1;
    int strnum_key2;
} Item;
typedef struct KeySpace1 {
    Item *info;
    int key;
} KeySpace1;
typedef struct KeySpace2 {
    int key;
// номер версии элемента
    int release;
    Item *info;
// указатель на следующий элемент
    struct KeySpace2 *next;
} KeySpace2;
typedef struct Table {
    KeySpace1 *ks1;
    KeySpace2 *ks2;
    int msize1;
    int msize2;
    int csize1;
    int csize2;
    char *name;
} Table;
Table  *table_cr(int msize1, int msize2, char* name);
int dialog(const char *msgs[], int N);
int delete(Table *table, int key1, int key2);
int add(Table *table, int key1, int key2, char *inf);
int find(Table *table, int key1, int key2);
Table *find_d(Table *table, int key1, int key2);
Table *find_key(Table *table, int key);
Table *find_rel(Table *table, int key, int release);
int delete_key(Table *table, int key);
int delete_rel(Table *table, int key, int release);
int free_t(Table *table);
int show(Table *table);
int getInt(int *a);
char* get_str();
char* get_str_ff(FILE *fd);
void files_ex(char *name1);
Table *read_file(char *name);