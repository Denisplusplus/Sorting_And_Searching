exec: main.o table.o 
	gcc -o exec main.o table.o 

main.o: main.c table.h 
	gcc -c -std=c99 -w main.c

table.o: table.c table.h 
	gcc -c -std=c99 -w table.c


clean:
	rm -rf *.o exec
