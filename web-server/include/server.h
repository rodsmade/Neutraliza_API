#ifndef HEADER_H
# define HEADER_H

// ------------------------------------------------		MACROS		-----------
# define RESPONSE_HEADER "Content-Type: text/html; charset=UTF-8\r\n"
# define RESPONSE_HEADER_JSON "{\"Content-Type\":\"text/html; charset=UTF-8\"}"

// ------------------------------------------------		INCLUDES	-----------

# include "mongoose.h"
# include "cJSON.h"
# include <stdio.h> // fopen(), fread(), fprintf()
# include <stdlib.h>
# include <bsd/string.h>
# include <string.h> // strdup(), strndup(), strncmp()
# include <signal.h> // signal()
# include <curl/curl.h> // external API calls

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
}			t_logger;

typedef struct s_memory
{
	char	*memory;
	size_t	size;
}			t_memory;

// ------------------------------------------------		GLOBAL VARS	-----------
extern t_logger	g_logger;


// ------------------------------------------------		PROTOTYPES	-----------
// services_ext_api_calls.c
void		parse_words(t_word_list	**words_list);

// services_load_resources.c
string		load_resource(string resource_path);

// services_routing.c
void		route_request_to_endpoint(struct mg_connection *connection, struct mg_http_message *request);

// services_translation.c
void		create_word_list(string *split_body, t_word_list **words_list);
string		*split_and_trim_body(struct mg_str body);
string		translate(void);

// utils_art.c
void		print_grand_opener(void);

// utils_http.c
string		class_to_string(enum e_class class);
string		http_status_to_string(enum e_http_method method);
string		http_method_to_string(enum e_http_method method);
int			http_status_to_int(enum e_http_method method);
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
void		logger_close(void);
void		logger_error(string	err_msg);
void		logger_info(string	info_msg);
void		logger_init(void);
void		logger_new_request(struct mg_http_message *request);
string		append_string(string original_str, const char *appendage, size_t n);
void		logger_log_response(int status_code, string headers, string body);


#endif