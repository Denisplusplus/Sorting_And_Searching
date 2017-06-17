#ifndef _TABLE_H_
#define _TABLE_H_

#include "table.h"

typedef enum {S1, S2} State;

struct str {
    int key ;
    char* data;
};
typedef struct str Str;


int to_number(char c);
int str_quantity(char* filename);
void table_print(Str *table, int str_amount);
void table_sort_random(Str* table, int str_amount);
void table_destroy(Str** table, int str_amount);
void table_data_search(Str *table, int str_amount);
void table_reverse(Str *table, int str_amount);
void table_linear_sort(Str *table, int str_amount);
void table_check_sort(Str* table, int str_amount);
Str* table_create(char* filename, Str *table, int str_amount);


#endif
