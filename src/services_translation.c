#include "server.h"

void	create_word_list(char **split_body, t_word_list	**words_list)
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

char	*translate(void)
{
	return("sua tradução sr.");
}
