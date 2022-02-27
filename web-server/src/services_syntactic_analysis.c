#include "server.h"

static int	look_up_class(char *word)
{
	char *api_response;

	api_response = ext_api_call_dictionary(word);

	// Parse api_response into json_format
	cJSON *response_json = cJSON_Parse(api_response);
	if (response_json == NULL)
	{
		printf("deu ruim criar o json\n");
		cJSON_Delete(response_json);
		ft_free_ptr((void *)&word);
		return (0);
	}

	// me dá a quantidade de retorno de itens da entrada!
	if (cJSON_GetArraySize(response_json) == 0)
	{
		char *info_log = ft_append_string_va(strdup("No definitions found for word: "), 1, word);
		logger_info(info_log);
		ft_free_ptr((void *)&info_log);
		cJSON_Delete(response_json);
		ft_free_ptr((void *)&word);
		return (0);
	}
	const cJSON *word_definition = NULL;
	word_definition = response_json->child;
	while (word_definition)
	{
		const cJSON *class_json = NULL;
		class_json = cJSON_GetObjectItemCaseSensitive(word_definition, "class");
		if (cJSON_IsString(class_json) && (class_json->valuestring != NULL))
		{
			if (strncmp(class_json->valuestring, "adjetivo", 8) == 0)
			{
				cJSON_Delete(response_json);
				return (1);
			}
		}
		word_definition = word_definition->next;
	}
	cJSON_Delete(response_json);
	return (0);
}

void	parse_words(t_word_list	**words_list)
{
	// make api call item by item
	t_word_list	*pivot = *words_list;
	while (pivot)
	{
		pivot->word.is_adjective = look_up_class(pivot->word.name);
		printf("find class: {name = %s; is_adj= %d}\n", pivot->word.name, pivot->word.is_adjective);
		pivot = pivot->next;
	}
	return ;
}