# COMPILATION VARIABLES
CC = gcc
CFLAGS = -I $(INCLUDE_PATH) # -Wall -Wextra -Werror
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
BIN_PATH = ./bin/

# FILES
NAME = $(BIN_PATH)neutre
HEADERS = $(INCLUDE_PATH)neutraliza-cli.h $(INCLUDE_PATH)get_next_line.h
SRC_FILES = neutraliza-cli.c \
			utils_exec.c \
			utils_get_next_line.c \
			utils_init.c \
			utils_libft.c \
			utils_log_search.c \
			utils_parsing.c \
			utils_print.c \
			utils_strings.c
SOURCES = $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
OBJECTS = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

all: make_dir $(NAME)

make_dir:
	@$(MKDIR) $(BIN_PATH)
	@$(MKDIR) $(OBJ_PATH)

# -> build server
$(NAME): $(OBJECTS)
	@$(CC) -o $(NAME) $(OBJECTS)

# -> creates object files
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# SANITIZE
# -> deletes all .o files; also runs libft's clean target
clean:
	@$(RM) $(OBJECTS)

# -> deletes .o files + static library file + executable; also runs libft's fclean target
fclean: clean
	@$(RM) $(BIN_PATH)$(NAME)
