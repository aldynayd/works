#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Table  *table_cr(int msize1, int msize2) {
    Table *table = (Table *) calloc(1, sizeof (Table));
    table->msize2 = msize2;
    table->msize1 = msize1;
    table->csize1 = 0;
    table->csize2 = 0;
    table->ks1 = (KeySpace1*) calloc(msize1, sizeof(KeySpace1));
    table->ks2 = (KeySpace2*) calloc(msize2, sizeof(KeySpace2));
    for (int i = 0; i < msize1; ++i) table->ks1[i].info = NULL;
    for (int i = 0; i < msize2; ++i) table->ks2[i].info = NULL;
    return table;
}
int dialog(const char *msgs[], int N) {
    char *errmsg = "";
    int rc;
    int i, n;
    do {
        puts(errmsg);
        errmsg = "You're wrong. Try again.";
        for (i = 0; i < N; ++i) {
            puts(msgs[i]);
            puts("Make your choice: ");
            n = getInt(&rc);
            if (n == 0 ) rc = 0;
        }
    }while (rc < 0 || rc >= N);
    return rc;
}
int add(Table *table, int key1, int key2, char *inf){
    if (find(table, key1, key2)) {
        printf("Error. Keys are already used\n");
        return 0;
    }
    if (table->csize1 < table->msize1) {
        Item *item1 = (Item *) calloc(1, sizeof (Item));
        item1->info = (char *) calloc(strlen(inf) + 1, sizeof (char));
        strcpy(item1->info, inf);
        item1->key1 = key1;
        item1->key2 = key2;
        table->ks1[table->csize1].info = item1;
        table->ks1[table->csize1].key = key1;
        table->csize1++;
    }
    if (table->csize2 < table->msize2) {
        Item *item2 = (Item *) calloc(1, sizeof(Item));
        item2->info = (char *) calloc(strlen(inf) + 1, sizeof(char));
        strcpy(item2->info, inf);
        item2->key1 = key1;
        item2->key2 = key2;
        int ind;
        ind = key2 % table->msize2;
        if (!table->ks2[ind].info) {
            table->ks2[ind].release = 0;
            table->ks2[ind].info = item2;
            table->ks2[ind].key = key2;
            table->ks2[ind].next = NULL;
            table->csize2++;
        } else {
            KeySpace2 *curr = table->ks2 + ind;
            int ver = -1;
            while (curr->next) {
                if (curr->key == key2) ver = curr->release;
                curr = curr->next;
            }
            if (curr->key == key2) {
                ver = curr->release;
            }
            curr->next = (KeySpace2 *) calloc(1, sizeof(KeySpace2));
            curr->next->release = ver + 1;
            curr->next->key = key2;
            curr->next->info = item2;
            curr->next->next = NULL;
            table->csize2++;
        }
    }
    return 0;
}
int delete(Table *table, int key1, int key2){
    for (int i = 0; i < table->csize1; ++i) {
        if (key1 == table->ks1[i].key && key2 == table->ks1[i].info->key2) {
            free(table->ks1[i].info);
            table->ks1[i].info = NULL;
            for (int j = i + 1; j < table->csize1; ++j) {
                table->ks1[j - 1].info = table->ks1[j].info;
                table->ks1[j - 1].key = table->ks1[j].key;
            }
            table->csize1--;
        }
    }
    int ind;
    ind = key2 % table->msize2;
    if (table->ks2[ind].info != NULL) {
        KeySpace2 *curr = table->ks2 + ind, *temp = curr->next;
        if (curr->info->key1 == key1 && curr->info->key2 == key2) {
            free(curr->info);
            if (curr->next != NULL) { //если 1ый элемент и дальше что-то есть
                for (KeySpace2 *p = temp; p != NULL; p = p->next) {
                    if (p->key == key2) p->release--;
                }
                curr->info = curr->next->info;
                curr->key = curr->next->key;
                curr->release = curr->next->release;
                KeySpace2 *b = curr->next;
                curr->next = curr->next->next;
                free(b);
            } else {                // если 1ый элемент и дальше ничего нет
                curr->info = NULL;
            }
            table->csize2--;
        } else {
            while (temp->next) {        // если элемент между 1 и последним
                if (temp->key == key2 && temp->info->key1 == key1) {
                    curr->next = curr->next->next;
                    for (KeySpace2 *p = temp->next; p != NULL; p = p->next) {
                        if (p->key == key2) p->release--;
                    }
                    free(temp->info);
                    free(temp);
                    table->csize2--;
                    return 0;
                }
                temp = temp->next;
                curr = curr->next;
            }
            if (temp->info->key1 == key1 && temp->info->key2 == key2) {  // если элемент последний
                curr->next = curr->next->next;
                free(temp->info);
                free(temp);
                table->csize2--;
            }
        }
    }
    return 0;
}
int delete_key(Table *table, int key) {  // по одному ключу в КС2, НАДО УДАЛЯТЬ ИЗ ОБОИХ ПРОСТРАНСТВ
    for (int i = 0; i < table->csize1; ++i) {
        if (key == table->ks1[i].info->key2) {
            free(table->ks1[i].info->info);
            free(table->ks1[i].info);
            table->ks1[i].info = NULL;
            for (int j = i + 1; j < table->csize1; ++j) {
                table->ks1[j - 1].info = table->ks1[j].info;
                table->ks1[j - 1].key = table->ks1[j].key;
            }
            table->csize1--;
            i--;
        }
    }
    int ind;
    ind = key % table->msize2;
    if (table->ks2[ind].info == NULL) {
        return 0;
    }
    KeySpace2 *curr = table->ks2 + ind, *temp = curr->next;
    while (curr->info != NULL && curr->info->key2 == key) {  //проходим по отростку и ищем такой ключ
        free(curr->info->info);
        free(curr->info);
        if (curr->next != NULL) { //если 1ый элемент и дальше что-то есть
            curr->info = curr->next->info;
            curr->key = curr->next->key;
            curr->release = curr->next->release;  //двигаем
            if (curr->key == key) {
                curr->release--;
            }
            KeySpace2 *b = curr->next;
            curr->next = curr->next->next;
            //надо удалить из 1го пространства
            free(b);
        } else {                // если 1ый элемент и дальше ничего нет
            //надо удалить из 1го пространства
            curr->info = NULL;
        }
        table->csize2--;
    }
    if (table->ks2[ind].info == NULL) {
        return 0;
    }
    curr = table->ks2 + ind, temp = curr->next;
    while (temp->next) {        // если элемент между 1 и последним
        if (temp->key == key) {
            curr->next = curr->next->next;
            //надо удалить из 1го пространства
            free(temp->info->info);
            free(temp->info);
            free(temp);
            temp = curr->next;
            if (temp == NULL) {
                break;
            }
            table->csize2--;
        }
        temp = temp->next;
        curr = curr->next;
    }
    if (table->ks2[ind].info == NULL) {
        return 0;
    }
    if (temp != NULL && temp->info->key2 == key) {  // если элемент последний
        curr->next = curr->next->next;
        //надо удалить из 1го пространства

        free(temp->info->info);
        free(temp->info);
        free(temp);
        table->csize2--;
    }
    return 0;
}
int delete_rel(Table *table, int key, int release) { //по ключу и номеру версии
    int ind = key % table->msize2;
    for (KeySpace2 *curr = &table->ks2[ind]; curr != NULL; curr = curr->next) {
        if (curr->release == release && curr->key == key) {
            delete(table, curr->info->key1, curr->key);
            return 0;
        }
    }
    return 0;
}
    /*int ind;
    ind = key % table->msize2;
    if (table->ks2[ind].info == NULL) {
        return 0;
    }
    KeySpace2 *curr = table->ks2 + ind, *temp = curr->next;
    if (curr->release == release && curr->info->key2 == key) {
        free(curr->info->info);
        free(curr->info);
        if (curr->next != NULL) { //если 1ый элемент и дальше что-то есть
            for (KeySpace2 *p = temp; p != NULL; p = p->next) {
                if (p->key == key) p->release--;
            }
            curr->info = curr->next->info;
            curr->key = curr->next->key;
            curr->release = curr->next->release;
            KeySpace2 *b = curr->next;
            curr->next = curr->next->next;
            free(b);
        } else {                // если 1ый элемент и дальше ничего нет
            curr->info = NULL;
        }
        table->csize2--;
        return 0;
    }
    while (temp->next) {        // если элемент между 1 и последним
        if (temp->key == key && temp->release == release) {
            curr->next = curr->next->next;
            for (KeySpace2 *p = temp->next; p != NULL; p = p->next) {
                if (p->key == key) p->release--;
            }
            free(temp->info->info);
            free(temp->info);
            free(temp);
            table->csize2--;
            return 0;
        }
        temp = temp->next;
        curr = curr->next;
    }
    if (temp->release == release && temp->info->key2 == key) {  // если элемент последний
        curr->next = curr->next->next;
        free(temp->info->info);
        free(temp->info);
        free(temp);
        table->csize2--;
    }
    return 0;
}*/
int find(Table *table, int key1, int key2) { //по составному ключу НУЖНО ВЫВОДИТЬ РЕЗУЛЬТАТ ПОИСКА
    for (int i = 0; i < table->csize1; ++i) {
        if (key1 == table->ks1[i].key && key2 == table->ks1[i].info->key2) {
            printf("key1 = %d, key2 = %d, info = %s\n", table->ks1[i].key, table->ks1[i].info->key2, table->ks1[i].info->info);
            return 1;
        }
    }
    int ind;
    ind = key2 % table->msize2;
    KeySpace2 *curr = table->ks2 + ind;
    while (curr->next) {
        if (curr->next->key == key2 && curr->info->key1 == key1) {
            printf("key1 = %d, key2 = %d, info = %s\n", curr->info->key1, curr->next->key, curr->info->info);
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}
Table * find_d(Table *table, int k1, int k2) {  // по диапазону КС1
    Table *new_table = table_cr(table->msize1, table->msize2);
    for (int i = 0; i < table->csize1; ++i) {
        if (table->ks1[i].key >= k1 && table->ks1[i].key <= k2) {
            add(new_table, table->ks1[i].info->key1, table->ks1[i].info->key2, table->ks1[i].info->info);
        }
    }
    show(new_table);
    return new_table;
}
Table *find_key(Table *table, int key) { //по одному ключу КС2
    Table *new_table = table_cr(table->msize1, table->msize2);
    int ind = key % table->msize2;
    for (KeySpace2 *curr = (table->ks2 + ind); curr != NULL; curr = curr->next) {
        if (curr->key == key) add(new_table, curr->info->key1, curr->info->key2, curr->info->info);
    }
    show(new_table);
    return new_table;
}
Table *find_rel(Table *table, int key, int release) {
    Table *new_table = table_cr(table->msize1, table->msize2);
    int ind = key % table->msize2;
    for (KeySpace2 *curr = (table->ks2 + ind); curr != NULL; curr = curr->next) {
        if (curr->key == key && curr->release == release) add(new_table, curr->info->key1, curr->info->key2, curr->info->info);
    }
    show(new_table);
    return new_table;
}
int show(Table *table) {
    printf("msize1 = %d, msize2 = %d, \ncsize1 = %d, csize2 = %d\n", table->msize1, table->msize2, table->csize1, table->csize2);
    printf("prosmatrivaemaya\n");
    for (int i = 0; i < table->csize1; ++i) {
        printf("key1 = %d  key2 = %d  %s\n", table->ks1[i].info->key1, table->ks1[i].info->key2, table->ks1[i].info->info);
    }
    printf("peremeshannaya\n");
    for (int i = 0; i < table->msize2; ++i) {
        if (table->ks2[i].info == NULL) continue;
        for (KeySpace2 *curr = (table->ks2 + i); curr != NULL; curr = curr->next) {
            printf("key1 = %d  key2 = %d release = %d %s\n", curr->info->key1, curr->info->key2, curr->release, curr->info->info);
        }
    }
    return 0;
}
void free_ks2(KeySpace2* node) {
    if (node == NULL) {
        return;
    }
    free_ks2(node->next);
    free(node->info->info);
    free(node->info);
    free(node);
}
int free_t(Table *table) {
    for (int i = 0; i < table->csize1; ++i) {
        free(table->ks1[i].info->info);
        free(table->ks1[i].info);
    }
    free(table->ks1);
    for (int i = 0; i < table->msize2; ++i) {
        if (table->ks2[i].info == NULL) continue;
        if (table->ks2[i].next != NULL) {
            free_ks2(table->ks2[i].next);
        }
        free(table->ks2[i].info->info);
        free(table->ks2[i].info);
    }
    free(table->ks2);
    return 0;
}

int getInt(int *a){
    int n;
    do{
        n = scanf("%d", a, sizeof(int));
        if (n < 0) // обнаружен конец файла
            return 0;
        if (n == 0){ // некорректный символ
            printf("%s\n", "Error! Repeat input");
            scanf("%*c", 0);
        }
    } while (n == 0);
    return 1;
}
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