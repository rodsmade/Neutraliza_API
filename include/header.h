#ifndef HEADER_H
# define HEADER_H

// ------------------------------------------------		INCLUDES	-----------
# include "mongoose.h"
# include <stdio.h> // fopen(), fread()
# include <stdlib.h>
# include <bsd/string.h>
# include <string.h>

// ------------------------------------------------		TYPEDEFS	-----------
typedef enum e_class {
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
}	t_enum_class;

typedef struct s_word
{
	char			*name;
	t_enum_class	class;
}					t_word;

typedef	struct s_word_list
{
	struct s_word_list	*next;
	t_word				word;
}					t_word_list;

// ------------------------------------------------		PROTOTYPES	-----------
// utils_libft.c
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char delimiter);

// utils_list.c
t_word_list	*ft_lstnew(t_word word);
int		ft_lstsize(t_word_list *lst);
t_word_list	*ft_lstlast(t_word_list *lst);
void	ft_lstadd_back(t_word_list **lst, t_word_list *new);

// services_ext_api_calls.c
void	parse_words(char **split_body);

// services_translation.c
char	*translate(void);

#endif