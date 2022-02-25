
# COMPILATION VARIABLES
CC = gcc
CFLAGS = -I $(INCLUDE_PATH) $(LIBS) # -Wall -Wextra -Werror
LIBS = -lbsd -lcurl
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
HEADERS = $(INCLUDE_PATH)mongoose.h \
			$(INCLUDE_PATH)server.h \
			$(INCLUDE_PATH)cJSON.h
SRC_FILES = cJSON.c \
			mongoose.c \
			services_ext_api_calls.c \
			services_translation.c \
			utils_http.c \
			utils_libft_ft_split.c \
			utils_libft.c \
			utils_list.c \
			utils_logger.c \
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

# SANITIZE
# -> deletes all .o files; also runs libft's clean target
clean:
	@$(RM) $(OBJECTS)

# -> deletes .o files + static library file + executable; also runs libft's fclean target
fclean: clean
	@$(RM) $(NAME)
