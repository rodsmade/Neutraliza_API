
DEBUG = -g

all:
	gcc $(DEBUG) mongoose.h mongoose.c header.h utils_libft.c main.c -o server -lbsd