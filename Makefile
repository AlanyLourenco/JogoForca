all: ProjetoForca

ProjetoForca: forca.h forca.c main.c
	gcc -o ProjetoForca forca.c main.c

clean: 
	rm -f ProjetoForca

run: ProjetoForca
	./ProjetoForca