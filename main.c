#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define LENGHT 20
#define SWAP_KEYS(A, B) {int t = A; A = B; B = t;}

void swap_data(char *str1, char *str2)
{
  char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
  strcpy(temp, str1);
  strcpy(str1, str2);
  strcpy(str2, temp);
  free(temp);
}  

typedef enum {S1, S2} State;

struct str {
	int key ;
	char* data;
};

typedef struct str Str;

int to_number(char c)
{
	return(c - 48);
}

int str_quantity(char* filename)
{	
	FILE *file = fopen(filename, "r");
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
    	printf("%d ",table[i].key);
    	printf("%s\n", table[i].data);
   	}
   	printf("\n");
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

void table_linear_sort(Str *table, int str_amount)
{
	for(int i = 0; i < (str_amount -1); i++) {
		for (int j=(i + 1); j < str_amount; j++) {
			if (table[j].key < table[i].key) {
				SWAP_KEYS(table[j].key, table[i].key);
				swap_data(table[j].data, table[i].data);
			}
		}
	}

	for (int i=0; i<str_amount; i++) {
    	printf("%d ",table[i].key);
    	printf("%s\n", table[i].data);
    }

}

Str* table_create(char* filename, Str *table, int str_amount)
{
	FILE *file = fopen(filename, "r");
	int c;
	int j=0;
	int i=0;
	int lenght= LENGHT;
	int number=0;
	State s = S1; 
    while (i!=str_amount-1) {
    	do {
    		c = fgetc(file);
            switch (s) {
                case S1 :
                	if (isdigit(c)) {
	                	number=number*10+ to_number(c);
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
						if (j==0) {
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

int main (void) {
	char filename[10];
	printf("Enter the name of file\n");
	scanf("%s", filename);


	int str_amount=str_quantity(filename);
	Str *table=(Str *)malloc(sizeof(Str)*str_amount);
	table = table_create(&filename[0], table, str_amount);
	//table_data_search(table, str_amount);
	table_print(table, str_amount);
	Str *table_new = table;
	table_linear_sort(table_new, str_amount);

	
	return 0;
}
