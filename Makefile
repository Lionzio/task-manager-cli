CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic

all: bin/task-cli.exe

bin/task-cli.exe: build/main.o build/task.o
	$(CC) $(CFLAGS) build/main.o build/task.o -o bin/task-cli.exe

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/task.o: src/task.c include/task.h
	$(CC) $(CFLAGS) -c src/task.c -o build/task.o

run: all
	.\bin\task-cli.exe

clean:
	-del /q /f build\*.o 2>nul
	-del /q /f bin\*.exe 2>nul