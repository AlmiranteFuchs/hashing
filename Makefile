CFLAGS = -Wall -g
LDFLAGS = -lm

CC = gcc

objects = myht.o libs/hash.o

all: $(objects)
	$(CC) -o myht $(objects) $(LDFLAGS)

myht.o: myht.c
	$(CC) -c $(CFLAGS) myht.c 

hash.o: libs/hash.c
	$(CC) -c $(CFLAGS) libs/hash.c

#remove os arquivos temporários (mantém o executável)
clean:
	rm -f myht $(objects)