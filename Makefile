# The compiler: gcc for C programs
CC = gcc

# Compiler flags:
# -Wall for debugger warnings
# -std=c11 for updated standards
CFLAGS = -Wall -std=c11

# The name of the program that we are producing.
TARGET = bench

# This is a "phony" target
# that just tells make what other targets to build.
all: $(TARGET)

# All the .o files we need for our executable.
OBJS = freemem.o getmem.o get_mem_stats.o print_heap.o mem_utils.o bench.c

# The executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -g -o $(TARGET) $(OBJS)

# source files
getmem.o: getmem.c mem.h mem_impl.h
	$(CC) $(CFLAGS) -g -c getmem.c

freemem.o: freemem.c mem.h mem_impl.h
	$(CC) $(CFLAGS) -g -c freemem.c

get_mem_stats.o: get_mem_stats.c mem.h mem_impl.h
	$(CC) $(CFLAGS) -g -c get_mem_stats.c

print_heap.o: print_heap.c mem.h mem_impl.h
	$(CC) $(CFLAGS) -g -c print_heap.c

mem_utils.o: mem_impl.h mem_utils.c
	$(CC) $(CFLAGS) -g -c mem_utils.c

noassert: CFLAGS += -DNDEBUG
noassert: bench

# A "phony" target to remove built files and backups
clean:
	rm -rf *.o bench *~

# run bench
test: bench
	./bench 10000 50 10 200 20000 1
