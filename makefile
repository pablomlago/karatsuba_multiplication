CC = gcc -Wall
LIBS = -lm
MAIN= karatsuba

SRCS = main.c vectordinamico.c enteirolargo.c

DEPS = vectordinamico.h enteirolargo.h

OBJS = $(SRCS:.c=.o)

$(MAIN): $(OBJS)
	$(CC) -o $(MAIN) $(OBJS) $(LIBS) 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< 

cleanall: clean
	rm -f $(MAIN)

clean:
	rm -f *.o *.~w
