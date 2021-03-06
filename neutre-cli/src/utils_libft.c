#include "neutraliza-cli.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (unsigned char) c)
		return ((char *)s + i);
	return (NULL);
}

size_t	ft_strlen(const char *s)
/**
 * Returns the length of a valid string
*/
{
	int	qtd_caracteres;

	qtd_caracteres = 0;
	while (*s)
	{
		qtd_caracteres++;
		s++;
	}
	return (qtd_caracteres);
}

char	*ft_strdup(const char *s)
/**
 * duplicates one string into another. allocates memory using malloc.
*/
{
	unsigned int	strlength;
	char			*newstr;
	unsigned int	i;

	strlength = ft_strlen(s);
	newstr = malloc((strlength + 1) * sizeof(const char));
	if (newstr == NULL)
		return (NULL);
	newstr[strlength] = '\0';
	i = 0;
	while (i < strlength)
	{
		((char *) newstr)[i] = ((char *) s)[i];
		i++;
	}
	return (newstr);
}

char	*ft_strjoin(char const *s1, char const *s2)
/**
 * concatenates two strings of fixed length into one.
 * allocates memory using malloc.
*/
{
	char	*joint;
	int		i;
	int		length_s1;
	int		length_s2;

	length_s1 = ft_strlen(s1);
	length_s2 = ft_strlen(s2);
	joint = malloc((length_s1 + length_s2 + 1) * sizeof(char));
	if (joint == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		joint[i] = s1[i];
	i = -1;
	while (s2[++i])
		joint[i + length_s1] = s2[i];
	joint[length_s1 + length_s2] = '\0';
	free((char *)s1);
	return (joint);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
/**
 * copies (up to size bytes) the content of one string (src) into another (dst).
 * overwrites the contents of dst.
*/
{
	unsigned int	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

int	contains_nl(char *string)
/**
 * scans a string for single line character (\n).
 * if found, returns its position (>= 0).
 * otherwise, returns -1.
*/
{
	int	i;

	if (!string)
		return (-1);
	i = 0;
	while (string[i])
	{
		if (string[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
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
