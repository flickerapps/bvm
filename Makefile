CC = gcc
CFLAGS = -std=c99 -I include
OBJS = \
	src/main.o \
	src/vm.o

BIN = bin/bvm
.SILENT:
build:$(BIN)
$(BIN): $(OBJS)
	mkdir -p bin
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)
src/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<
run: $(BIN)
	./$(BIN)
.PHONY: clean
clean:
	rm src/*.o
	rm bin/*
	rm -r bin
