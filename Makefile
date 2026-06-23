CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic

all: bin/task-cli.exe

bin/task-cli.exe: build/main.o build/task.o build/file_io.o
	$(CC) $(CFLAGS) build/main.o build/task.o build/file_io.o -o bin/task-cli.exe

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/task.o: src/task.c include/task.h
	$(CC) $(CFLAGS) -c src/task.c -o build/task.o

build/file_io.o: src/file_io.c include/file_io.h include/task.h
	$(CC) $(CFLAGS) -c src/file_io.c -o build/file_io.o

# NOVA ENGRENAGEM: Target isolado para compilar e rodar a suíte de testes
test: build/task.o build/file_io.o tests/test_main.c
	$(CC) $(CFLAGS) build/task.o build/file_io.o tests/test_main.c -o bin/test_runner.exe
	.\bin\test_runner.exe

run: all
	.\bin\task-cli.exe

clean:
	-del /q /f build\*.o 2>nul
	-del /q /f bin\*.exe 2>nul