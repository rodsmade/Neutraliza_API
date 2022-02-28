#include "server.h"

static string	*split_and_trim_body(const char *body)
{
	string *list_of_words;
	int	i = -1;

	list_of_words = ft_split(body, ' ');
	while (list_of_words[++i])
	{
		list_of_words[i] = ft_strtrim(list_of_words[i], "!.,?-\"\'+&$@#*()=_");
		printf("word[%i]: %s\n", i, list_of_words[i]);
	}
	return (list_of_words);
}

static void	create_word_list(string *split_body, t_word_list **words_list)
{
	t_word		new_word;
	int			i = -1;

	while (split_body[++i])
	{
		new_word.name = strdup(split_body[i]);
		new_word.is_adjective = 0;
		new_word.class = none;
		new_word.length = strlen(new_word.name);
		ft_lstadd_back(words_list, ft_lstnew(new_word));
	}
	return ;
}

static void	translate_to_nonbinary(t_word_list **words_list)
{
	t_word_list	*pivot = *words_list;
	int			is_plural = 0;

	while (pivot)
	{
		if (pivot->word.is_adjective)
		{
			// check if is in the plural
			if (pivot->word.name[pivot->word.length - 1] == 's')
				is_plural = 1;
			if (pivot->word.name[pivot->word.length - 1 - is_plural] == 'a'
				|| pivot->word.name[pivot->word.length - 1 - is_plural] == 'o')
				pivot->word.name[pivot->word.length - 1 - is_plural] = 'e';
		}
		pivot = pivot->next;
	}
}

static char	*word_list_to_string(t_word_list **words_list)
{
	char		*sentence = strdup("");
	t_word_list	*pivot = *words_list;

	while (pivot)
	{
		sentence = ft_append_string(sentence, pivot->word.name, pivot->word.length);
		if (pivot->next)
			sentence = ft_append_string(sentence, " ", 1);
		pivot = pivot->next;
	}
	return (sentence);
}

string	translation_service(const char *body)
{
	char	*non_binary_sentence;

	string *split_body = split_and_trim_body(body);
	t_word_list	*words_list = NULL;
	create_word_list(split_body, &words_list);
	parse_words(&words_list);	//api_call
	translate_to_nonbinary(&words_list);
	non_binary_sentence = word_list_to_string(&words_list);
	return (non_binary_sentence);
}
