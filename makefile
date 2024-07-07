Shell: assign2.o
	gcc assign2.o -lreadline -o Shell

assign2.o: assign2.c
	gcc -c assign2.c -o assign2.o
