#include "server.h"

string	*split_and_trim_body(struct mg_str body)
{
	string *list_of_words;
	int	i = -1;

	list_of_words = ft_split(body.ptr, ' ');
	while (list_of_words[++i])
	{
		list_of_words[i] = ft_strtrim(list_of_words[i], "!.,?");
		printf("word[%i]: %s\n", i, list_of_words[i]);
	}
	return (list_of_words);
}

void	create_word_list(string *split_body, t_word_list	**words_list)
{
	t_word		new_word;
	int			i = -1;

	while (split_body[++i])
	{
		new_word.class = none;
		new_word.name = strdup(split_body[i]);
		ft_lstadd_back(words_list, ft_lstnew(new_word));
	}
	return ;
}

string	translate(void)
{
	return("sua tradução sr.");
}
