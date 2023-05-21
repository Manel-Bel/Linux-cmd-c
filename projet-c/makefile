CC=gcc
CFLAGS=-g -Wall
EXEC=my_program
SOURCEFILE= $(wildcard *.c)
OBJECTFILES = $(SOURCEFILE:.c=.c)

all : $(EXEC)

%.o: %.c
	$(CC)  $(CFLAGS) -c $< 
my_program : $(OBJECTFILES)
	$(CC)  $(CFLAGS) -o $@ $^
clean :
	rm -rf $(EXEC) *.o