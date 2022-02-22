
DEBUG = -g
UTILS = utils_libft.c utils_ft_split.c

all:
	gcc $(DEBUG) mongoose.h mongoose.c header.h $(UTILS) main.c -o server -lbsd