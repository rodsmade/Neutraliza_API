#include "server.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	slength;
	size_t	i;

	slength = strlen(s);
	if (start >= slength)
		return (strdup(""));
	if (slength - start < len)
		len = slength - start;
	substring = malloc((len + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	i = 0;
	while (s[i + start] && (i < len))
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[len] = '\0';
	return (substring);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (strchr(set, *s1) && *s1)
		s1++;
	i = strlen(s1);
	while (strchr(set, s1[i - 1]) && i)
		i--;
	return (ft_substr(s1, 0, i));
}

void	ft_free_arr(void ***arr)
{
	int	i;

	i = -1;
	while ((*arr)[++i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
	}
	free(*arr);
}

void	ft_free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

/**
 * In order for this function to work properly with NO LEAKS, original_str
 * HAS to be malloced initially. It WILL be freed. So it's reasonable to call
 * my_string = ft_append_string(strdup("Hello "), "world!", 6);
**/
string	ft_append_string(string original_str, const char *appendage, size_t n)
{
	string	new_str;
	int		orig_len = 0;
	size_t	i;

	orig_len = strlen(original_str);
	new_str = realloc(original_str, (orig_len + n + 1) * sizeof(char));
	new_str[orig_len + n] = '\0';
	i = -1;
	while (++i < n)
		new_str[orig_len + i] = appendage[i];
	return (new_str);
}

/**
 * In order for this function to work properly with NO LEAKS, body HAS TO BE
 * malloced previously. It WILL be freed. So it's reasonable to call:
 * myStr = ft_append_string(strdup("Here's "), 3, "some ", "other ", "strings");
**/
char	*ft_append_string_va(char* body, int count_append, char *appendage, ...)
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
	if ((new_str = realloc(body, (body_len + appendage_len + 1) * sizeof(char))))
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
		if ((new_str = realloc(new_str, (body_len + appendage_len + 1) * sizeof(char))))
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
