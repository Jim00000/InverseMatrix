CC=gcc -std=gnu99
CFLAGS=-g -O0 -Wall -Wextra
EXE=a.out
OBJS=test.o matrix.o

.PHONY:all
all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

$.o : $.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm $(EXE) $(OBJS)