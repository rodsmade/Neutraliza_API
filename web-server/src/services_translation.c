#include "server.h"

static string	*split_and_trim_body(const char *body)
{
	string *list_of_words;
	int	i = -1;

	list_of_words = ft_split(body, ' ');
	while (list_of_words[++i])
	{
		list_of_words[i] = ft_strtrim(list_of_words[i], "!.,?");
		printf("word[%i]: %s\n", i, list_of_words[i]);
	}
	return (list_of_words);
}

static void	create_word_list(string *split_body, t_word_list	**words_list)
{
	t_word		new_word;
	int			i = -1;

	while (split_body[++i])
	{
		new_word.name = strdup(split_body[i]);
		new_word.is_adjective = 0;
		new_word.class = none;
		ft_lstadd_back(words_list, ft_lstnew(new_word));
	}
	return ;
}

string	translate(const char *body)
{
	string *split_body = split_and_trim_body(body);
	t_word_list	*words_list = NULL;
	create_word_list(split_body, &words_list);
	parse_words(&words_list);	//api_call
	return("sua tradução sr.");
}
