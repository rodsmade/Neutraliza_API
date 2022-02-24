#include "server.h"

void	call_dic_api(void)
{
	//use libcurl
}

void	parse_words(t_word_list	**words_list)
{
	// make api call item by item
	t_word_list	*pivot = *words_list;
	while (pivot)
	{
		printf("find class: {name = %s; class = %i}\n", pivot->word.name, pivot->word.class);
		pivot = pivot->next;
	}
	return ;
}