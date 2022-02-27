#include "include/neutraliza-cli.h"

// char	*append_string_va(char *body, char *appendage, ...)

char	*append_n_strs(char* body, int count_append, char *appendage, ...)
{
	va_list	args;
	char	*arg;
	char	*new_str;
	int		body_len;
	int		appendage_len;
	int		i;
	int		count;

	va_start(args, appendage);
	// append first argument
	body_len = strlen(body);
	appendage_len = strlen(appendage);
	if (new_str = realloc(body, (body_len + appendage_len + 1) * sizeof(char)))
	{
		new_str[body_len + appendage_len] = '\0';
		i = -1;
		while (++i < appendage_len)
			new_str[body_len + i] = appendage[i];
	}

	// append var args
	count = 0;
	while (++count < count_append)
	{
		arg = va_arg(args, char *);
		body_len = strlen(new_str);
		appendage_len = strlen(arg);
		if (new_str = realloc(new_str, (body_len + appendage_len + 1) * sizeof(char)))
		{
			new_str[body_len + appendage_len] = '\0';
			i = -1;
			while (++i < appendage_len)
				new_str[body_len + i] = arg[i];
		}
	}
	va_end(args);
	return (new_str);
}

int main()
{
	// char *init = strdup("hello ");
	char *init =  append_n_strs(strdup("hello "), 5, "world ", "what ", "is", " ", "up?");
	printf("%s\n", init);
	free(init);
	return 0 ;
}