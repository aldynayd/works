#include <stdio.h>
#include <stdlib.h>
#include "table.h"
const char *msgs[] = {"0.Quit", "1.Add", "2.Find", "3.Delete", "4.Show",
                      "5.Find range of nums in first key space", "6. Delete key from second key space",
                      "7. Delete key and version from second key space", "8. Find key from second key space",
                      "9. Find key and release from second key space"};
const int NMsgs = sizeof(msgs)/sizeof(msgs[0]);
int main() {
    int ms1 = 0, ms2 = 0;
    printf("msize1 = ");
    scanf("%d", &ms1);
    printf("\nmsize2 = ");
    scanf("%d", &ms2);
    Table *table = table_cr(ms1, ms2);
    int rc;
    for (int i = 0; i < NMsgs; ++i) {
        printf("%s\n", msgs[i]);
    }
    while ((scanf("%d", &rc)) && rc != 0) {
        if (rc == 1) {
            printf("key1 = .. key2 = ..\n");
            int key1, key2;
            char *s;
            scanf("%d %d", &key1, &key2);
            scanf("%*c");
            printf("info: ");
            s = get_str();      // пункт 6 удалять все элементы, в поиске выводить результат
            add(table, key1, key2, s);
        } else if (rc == 2) {
            printf("key1: .. key2: .. \n");
            int key1, key2;
            scanf("%d %d", &key1, &key2);
            if (find(table, key1, key2)) {
                printf("Found\n");
            } else {
                printf("Not found\n");
            }
        } else if (rc == 3) {
            printf("key1: .. key2: .. \n");
            int key1, key2;
            scanf("%d %d", &key1, &key2);
            delete(table, key1, key2);
        }
        else if (rc == 4) show(table);
        else if (rc == 5)  {
            printf("key1 = .. key2 = ..\n");
            int key1, key2;
            scanf("%d %d", &key1, &key2);
            free_t(find_d(table, key1, key2));
        }
        else if (rc == 6) {
            printf("key2 = .. \n");
            int key1;
            scanf("%d", &key1);
            delete_key(table, key1);
        }
        else if (rc == 7) {
            printf("key: .. release: .. \n");
            int key1, version;
            scanf("%d %d", &key1, &version);
            delete_rel(table, key1, version);
        } else if (rc == 8) {
            printf("key:\n");
            int key1;
            scanf("%d", &key1);
            free_t(find_key(table, key1));
        }
        else if (rc == 9) {
            printf("key: .. release: .. \n");
            int key1, version;
            scanf("%d %d", &key1, &version);
            free_t(find_rel(table, key1, version));
        }
        for (int i = 0; i < NMsgs; ++i) {
            printf("%s\n", msgs[i]);
        }
    }
    free_t(table);
    return 0;
}
