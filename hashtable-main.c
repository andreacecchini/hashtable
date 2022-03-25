/****************************************************************************
 *
 * hashtable-main.c -- dimostrazione hash table
 *
 * Copyright (C) 2021 Moreno Marzolla
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

#define MAX_KEY_SIZE 100

int main( int argc, char *argv[] )
{
    int table_size = 10;
    char key[MAX_KEY_SIZE];
    char op;
    int val;
    HashNode *item;
    HashTable *table;
    FILE *filein = stdin;

        filein = fopen("hashtable.in", "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[1]);
            return EXIT_FAILURE;
        }



    if (1 != fscanf(filein, "%d", &table_size)) {
        fprintf(stderr, "Missing size\n");
        return EXIT_FAILURE;
    }
    printf("INIT %d\n", table_size);
    table = ht_create(table_size);

    while (1 == fscanf(filein, " %c", &op)) {
        switch (op) {
        case '+': /* insert */
            fscanf(filein, "%s %d", key, &val);
            printf("INSERT %s %d\n", key, val);
            ht_insert(table, key, val);
            break;
        case '-': /* delete */
            fscanf(filein, "%s", key);
            printf("DELETE %s ", key);
            if (0 == ht_delete(table, key)) {
                printf("NOT FOUND\n");
            } else {
                printf("OK\n");
            }
            break;
        case '?': /* search */
            fscanf(filein, "%s", key);
            printf("SEARCH %s ", key);
            item = ht_search(table, key);
            if (item == NULL) {
                printf("NOT FOUND\n");
            } else {
                printf("%d\n", item->value);
            }
            break;
        default:
            fprintf(stderr, "Unknown command %c\n", op);
        }
    }

    ht_destroy(table);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
