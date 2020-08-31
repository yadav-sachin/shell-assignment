CC = gcc
CFLAGS = -Wall
SOURCE = main.c
OUTPUT = buake

all: $(SOURCE) resources
	$(CC) $(SOURCE) $(CFLAGS) -o $(OUTPUT)

run: ./buake	
	./buake	

clean: 
	rm -rf $(OUTPUT)	