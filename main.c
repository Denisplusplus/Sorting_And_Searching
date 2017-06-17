#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "table.h"


int main (void) {
	char filename[10];
	printf("Enter the name of file:\n");
	scanf("%s", filename);
	int str_amount=str_quantity(filename);
	Str *table=(Str *)malloc(sizeof(Str)*str_amount);
	table = table_create(filename, table, str_amount);

	char action[4];
	menu();
    do
    {
        
        scanf("%3s", action);
        if (!strcmp(action, "1")) {
           table_print(table, str_amount);
        } else if (!strcmp(action, "2")) {
        	table_check_sort(table, str_amount);
        } else if (!strcmp(action, "3")) {
            table_data_search(table, str_amount);
        } else if (!strcmp(action, "4")) {
            table_linear_sort(table, str_amount);
        } else if (!strcmp(action, "5")) {
            table_sort_random(table, str_amount);
        } else if (!strcmp(action, "6")) {
            table_reverse(table, str_amount);
        } else if (!strcmp(action, "7")) {
            menu();        
        } else if (!strcmp(action, "0")) {
        	table_destroy(&table, str_amount);
            break;
        } else {
            printf("\nIncorrect input. Try another.\n");
        }
    } while (1);

	return 0;
}


void menu(void)
{
  		printf("Menu:\n");
        printf("1) Print the table\n");
        printf("2) Check the sorting of the table\n");
        printf("3) Search for the data by key\n");
        printf("4) Sort the table\n");
        printf("5) Shuffle the table\n");
        printf("6) Reverse the table\n");
        printf("7) Print menu \n");
        printf("0) Exit\n");
        printf("\nChose the action:\n");  	
    
}
