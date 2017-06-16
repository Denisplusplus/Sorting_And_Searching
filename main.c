#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define LENGHT 20
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

void table_create(char* filename)
{
	FILE *file = fopen(filename, "r");
	int c;
	int j=0;
	int i=0;
	int lenght= LENGHT;
	int number=0;
	State s = S1;
    int str_amount=str_quantity(filename);
    Str table[str_amount];   

  // printf("%d\n", str_amount);
    while (i!=str_amount-1) {
    	do {
    		c = fgetc(file);
            switch (s) {
                case S1 :
                	if (isdigit(c)) {
	                	number=number*10+ to_number(c);
	                	//printf("%d\n", number);
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

  for (int i=0; i<str_amount; i++) {
    	printf("%d ",table[i].key);
    	printf("%s\n", table[i].data);
   }
    fclose(file);

}

int main (void) {
	char filename[10];
	printf("Enter the name of file\n");
	scanf("%s", filename);

	//int str_amount=str_quantity(filename);
	//Str table[str_amount];
	table_create(&filename[0]);


	return 0;
}
