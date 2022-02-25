#ifndef HEADER_H
# define HEADER_H

// ------------------------------------------------		INCLUDES	-----------

# include "mongoose.h"
# include "cJSON.h"
# include <stdio.h> // fopen(), fread(), fprintf()
# include <stdlib.h>
# include <bsd/string.h>
# include <string.h> // strdup(), strndup(), strncmp()
# include <signal.h> // signal()

// ------------------------------------------------		TYPEDEFS	-----------

typedef char *string;
typedef unsigned long int ulint;

// ------------------------------------------------		ENUMS		-----------

enum e_http_method {
	GET,
	POST,
	PUT,
	PATCH,
	DELETE
};

enum e_http_status {
	CONTINUE_100,
	OK_200,
	BAD_REQUEST_400,
	NOT_FOUND_400,
	TEAPOT_418,
	SERVER_ERROR_500
};

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
	ulint	transaction_id;
	string	timestamp;
	string	body;
	string	method;
	string	protocol;
	string	query;
	string	uri;
	string	headers[MG_MAX_HTTP_HEADERS];
}			t_logger;

// ------------------------------------------------		PROTOTYPES	-----------
// services_ext_api_calls.c
void		parse_words(t_word_list	**words_list);

// services_translation.c
void		create_word_list(string *split_body, t_word_list **words_list);
string		translate(void);

// utils_http.c
string		class_to_string(enum e_class class);
string		http_status_to_string(enum e_http_method method);
string		http_method_to_string(enum e_http_method method);
int			http_match_method(struct mg_http_message *request, int method);

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
void		logger_info(string	info_msg, t_logger *logger);
void		logger_init(t_logger *logger);
void		logger_log_request(struct mg_http_message *request, t_logger *logger);
// TODO: alterar depois:
void		logger_log_response(t_logger *logger);


#endif