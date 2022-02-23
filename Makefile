
# COMPILATION VARIABLES
CC = gcc
CFLAGS = -I $(INCLUDE_PATH) $(LIBS) # -Wall -Wextra -Werror
LIBS = -lbsd
DEBUG = -g
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q --tool=memcheck

# BASH COMMANDS
RM = rm -f
MKDIR = mkdir -p
MAKE_NOPRINT = $(MAKE) --no-print-directory
TOUCH = touch -a

# PATH VARIABLES
INCLUDE_PATH = ./include/
SRC_PATH = ./src/
OBJ_PATH = ./obj/
BINS_PATH = ./bin/

# FILES
NAME = $(BINS_PATH)server
HEADERS = mongoose.h header.h
SRC_FILES = mongoose.c \
			services_ext_api_calls.c \
			services_translation.c \
			utils_ft_split.c \
			utils_libft.c \
			utils_list.c \
			main.c
SOURCES = $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
OBJECTS = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

all: make_dir $(NAME)

make_dir:
	@$(MKDIR) $(BINS_PATH)
	@$(MKDIR) $(OBJ_PATH)

# -> build server
$(NAME): $(OBJECTS)
	@$(CC) -o $(NAME) $(OBJECTS)

# -> creates object files
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# %.o: $(SRC_PATH)%.c
# 	$(CC) $(CFLAGS) -c $< -o $(OBJ_PATH)$@
