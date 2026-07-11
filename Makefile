all: app

app: main.o account.o auth.o tools.o ui.o transactions.o
	gcc main.o account.o auth.o tools.o ui.o transactions.o -o app

main.o: main.c
	gcc -Wall -Wextra -Iinclude -g -c main.c -o main.o

account.o: src/account.c
	gcc -Wall -Wextra -Iinclude -g -c src/account.c -o account.o

auth.o: src/auth.c
	gcc -Wall -Wextra -Iinclude -g -c src/auth.c -o auth.o

tools.o: src/tools.c
	gcc -Wall -Wextra -Iinclude -g -c src/tools.c -o tools.o

ui.o: src/ui.c
	gcc -Wall -Wextra -Iinclude -g -c src/ui.c -o ui.o

transactions.o:	src/transactions.c
	gcc -Wall -Wextra -Iinclude -g -c src/transactions.c transactions.o

rebuild:
	make clean
	make

clean:
	rm -f app *.o

run:
	./app