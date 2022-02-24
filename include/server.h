#ifndef HEADER_H
# define HEADER_H

// ------------------------------------------------		INCLUDES	-----------

# include "mongoose.h"
# include <stdio.h> // fopen(), fread(), fprintf()
# include <stdlib.h>
# include <bsd/string.h>
# include <string.h>
# include <signal.h>

// ------------------------------------------------		TYPEDEFS	-----------

typedef char *string;

// ------------------------------------------------		ENUMS		-----------

enum e_http_method {
	GET,
	POST,
	PUT,
	PATCH,
	DELETE
};

static inline char *http_method_to_string(enum e_http_method method)
{
	char *strings[] = {"GET", "POST", "PUT", "PATCH", "DELETE"};

	return strings[method];
}

enum e_class {
	none,
	adjective,
	adverb,
	article,
	conjunction,
	interjection,
	numeral,
	preposition,
	pronoun,
	noun,
	verb
};

static inline char *class_to_string(enum e_class class)
{
	char *strings[] = {"none", "adjective", "adverb", "article", "conjunction", "interjection", "numeral", "preposition", "pronoun", "noun", "verb"};

	return strings[class];
}

// ------------------------------------------------		STRUCTS		-----------

typedef struct s_word
{
	char	*name;
	string	class;
}			t_word;

typedef	struct s_word_list
{
	struct s_word_list	*next;
	t_word				word;
}			t_word_list;

typedef struct s_logger
{
	int		fd;
	string	timestamp;
	string	method;
	string	uri;
	string	query;
	string	protocol;
	string	body;
	string	*headers;
}			t_logger;

// ------------------------------------------------		PROTOTYPES	-----------
// services_ext_api_calls.c
void		parse_words(t_word_list	**words_list);

// services_translation.c
void		create_word_list(string *split_body, t_word_list	**words_list);
string		translate(void);

// utils_libft.c + utils_libft_ft_split.c
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char delimiter);

// utils_list.c
t_word_list	*ft_lstnew(t_word word);
int			ft_lstsize(t_word_list *lst);
t_word_list	*ft_lstlast(t_word_list *lst);
void		ft_lstadd_back(t_word_list **lst, t_word_list *new);

// utils_logger.c
void		logger_close(t_logger *logger);
void		logger_error(string	err_msg, t_logger *logger);
void		logger_init(t_logger *logger);
void		logger_write(t_logger *logger);

#endif