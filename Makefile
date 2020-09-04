CC = gcc
CFLAGS = -Wall
MAIN = main.c
HEADERS = headers/commands.h headers/text_colors.h headers/launch_animation.h
FILES = src/buake_cat.c src/buake_chmod.c src/buake_cp.c src/buake_grep.c src/buake_ls.c src/buake_mkdir.c src/buake_mv.c src/buake_rm.c src/launch_text.txt
OUTPUT = buake

all: $(MAIN) $(HEADERS) $(FILES)
	$(CC) $(MAIN) $(CFLAGS) -o $(OUTPUT)
	mkdir -p bin
	$(CC) src/buake_cat.c -o bin/buake_cat
	$(CC) src/buake_chmod.c -o bin/buake_chmod
	$(CC) src/buake_cp.c -o bin/buake_cp
	$(CC) src/buake_grep.c -o bin/buake_grep
	$(CC) src/buake_ls.c -o bin/buake_ls
	$(CC) src/buake_mkdir.c -o bin/buake_mkdir
	$(CC) src/buake_mv.c -o bin/buake_mv
	$(CC) src/buake_rm.c -o bin/buake_rm

run: ./buake	
	./buake

clean: 
	rm -rf $(OUTPUT)	
	rm -rf bin