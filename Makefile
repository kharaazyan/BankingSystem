CC = gcc
CFLAGS = -Wall -Wextra -I./include
OBJ = src/main.o src/utils.o src/metainfo.o src/admin.o src/accounts.o
EXEC = bank_app

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

src/main.o: src/main.c include/bank.h include/functions.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/utils.o: src/utils.c include/bank.h include/functions.h
	$(CC) $(CFLAGS) -c src/utils.c -o src/utils.o

src/metainfo.o: src/metainfo.c include/bank.h include/functions.h
	$(CC) $(CFLAGS) -c src/metainfo.c -o src/metainfo.o

src/admin.o: src/admin.c include/bank.h include/functions.h
	$(CC) $(CFLAGS) -c src/admin.c -o src/admin.o

src/accounts.o: src/accounts.c include/bank.h include/functions.h
	$(CC) $(CFLAGS) -c src/accounts.c -o src.accounts.o
	@mv src.accounts.o src/accounts.o

clean:
	rm -f src/*.o $(EXEC)

.PHONY: all clean
