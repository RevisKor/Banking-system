all: app

app: main.o account.o tools.o
	gcc main.o account.o tools.o -o app

main.o: main.c
	gcc -Wall -Wextra -Iinclude -g -c main.c -o main.o

account.o: src/account.c
	gcc -Wall -Wextra -Iinclude -g -c src/account.c -o account.o

tools.o: src/tools.c
	gcc -Wall -Wextra -Iinclude -g -c src/tools.c -o tools.o

rebuild:
	make clean
	make

clean:
	rm -f app *.o

run:
	./app