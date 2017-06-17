#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "table.h"

#define LENGHT 20



int to_number(char c)
{
    return(c - 48);
}

int str_quantity(char* filename)
{   
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }
    int str_amount = 0;
    while (! feof(file)) {
        fscanf(file, "%*[^\n]%*c");
        str_amount++;
    }
    fclose(file);
    return(str_amount);
}


void table_print(Str *table, int str_amount)
{   
    printf("\n");

    for (int i=0; i<str_amount; i++) {
        printf("%d ",  table[i].key);
        printf("%s\n", table[i].data);
    }
  
    printf("\n");
}

void table_sort_random(Str* table, int str_amount)
{
    int j;
    srand(time(NULL));

    for (int i = 0; i < str_amount; ++i) {
        j = rand() % str_amount;
        Str temp = table[j];
        table[j] = table[i];
        table[i] = temp;
    }   
    printf("The table has been successfully shuffled\n");
}

void table_destroy(Str** table, int str_amount)
{

    for(int i = 0; i < str_amount; i++) {
        if((*table)[i].data) {
            free((*table)[i].data);
            (*table)[i].data = NULL;
        }
    }
    if(*table) {
        free(*table);
        *table = NULL;
    }
}

void table_data_search(Str *table, int str_amount)
{   
    int key_to_search = 0;
    printf("Input the key to search in the table:\n");
    scanf("%d", &key_to_search);
    int flag = 0;
    for (int i=0; i<str_amount;i++) {
        if (table[i].key == key_to_search) {
            flag = 1;
            printf("%s\n", table[i].data);
            return;
        }
    }
    if (flag == 0) {
        printf("No matches for key %d found\n", key_to_search);
    }
}

void table_reverse(Str *table, int str_amount)
{
    for (int i = 0; i < (str_amount / 2); ++i) {
        Str temp = table[i];
        table[i] = table[str_amount - i - 1];
        table[str_amount - i - 1] = temp;
    }
     printf("The table has been successfully reversed\n");

}

void table_linear_sort(Str *table, int str_amount)
{
    for(int i = 0; i < (str_amount -1); i++) {
        for (int j=(i + 1); j < str_amount; j++) {
            if (table[j].key < table[i].key) {
                Str temp = table[j];
                table[j] = table[i];
                table[i] = temp;
            }
        }
    }
    printf("Table has been successfully sorted\n");
}

void table_check_sort(Str* table, int str_amount)
{
    int flag = 0;
    for (int i=0; i < str_amount; i++) {
        if (table[i].key < table[i+1].key) {
            flag++;
        }
    }
    if (flag==str_amount-1) {
        printf("Table is sorted\n");
    } else
    if (flag == 0) {
        printf("Table is reversed\n");
    } else {
        printf("Table isn't sorted\n");
    }
}


Str* table_create(char* filename, Str *table, int str_amount)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }
    int c;
    int j=0;
    int i=0;
    int lenght= LENGHT;
    int number=0;
    State s = S1; 
    while (i != str_amount - 1) {
        do {
            c = fgetc(file);
            switch (s) {
                case S1 :
                    if (isdigit(c)) {
                        number = number * 10 + to_number(c);
                        s = S1;
                        break;
                    } else if (c == ' ') {
                        table[i].key=number;
                        number=0;
                        s = S2;
                        break;
                    }  

                case S2 :
                    if ((c != EOF) && (c!='\n')) {
                        if (j == 0) {
                            table[i].data= (char*) malloc(lenght * sizeof(char*));
                        }
                        if (j== lenght-1) {
                            lenght*=2;
                            table[i].data = (char *) realloc(table[i].data, lenght * sizeof(char*));
                        }
                        table[i].data[j++]=c;
                        break;
                    } else if (c =='\n') {
                        i++;
                        j=0;
                        s=S1;
                        break;
                    } else {
                        break;
                    }
            }       

        } while ((c != EOF));        

    }
    fclose(file);
    return(table);
    
}
