#include "header.h"

void	parse_words(char **split_body)
{
	t_word_list	*words_list = NULL;
	t_word		new_word;
	int			i = -1;

	while (split_body[++i])
	{
		new_word.class = none;
		new_word.name = strdup(split_body[i]);
		ft_lstadd_back(&words_list, ft_lstnew(new_word));
	}
	t_word_list	*pivot;
	pivot = words_list;
	while (pivot)
	{
		printf("list item: {name = %s; class = %i}\n", pivot->word.name, pivot->word.class);
		pivot = pivot->next;
	}
}