#ifndef HEADER_H
# define HEADER_H

# include "mongoose.h"
# include <stdio.h> // fopen(), fread()
# include <stdlib.h>
# include <bsd/string.h>

typedef enum e_class {
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
}	t_class;

typedef struct s_word
{
	char	*name;
	t_class	class;
}	t_word;

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char delimiter);

#endif