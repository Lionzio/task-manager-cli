CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic

all: bin/task-cli.exe

bin/task-cli.exe: build/main.o
	$(CC) $(CFLAGS) build/main.o -o bin/task-cli.exe

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

run: all
	.\bin\task-cli.exe

clean:
	-del /q /f build\*.o 2>nul
	-del /q /f bin\*.exe 2>nul