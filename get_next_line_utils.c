/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbokotej <vbokotej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:01:53 by vbokotej          #+#    #+#             */
/*   Updated: 2026/04/14 15:18:53 by vbokotej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
returns the length of string
if s == null then length = 0
*/
size_t	ft_strlen(char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

/*
finds first occurrence of character c in string s
it will be used to detect '\n'
returns pointer to c, or null if not found
*/
char	*ft_strchr(char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

/*
joins stash + buffer into a NEW string. frees old stash
if stash is null, it is initialized as an empty string
example:
stash =  "Hello"
buffer = "World"
result = "HelloWorld"
*/
char	*ft_strjoin(char *stash, char *buffer)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!stash)
	{
		stash = (char *)malloc(1 * sizeof(char));
		stash[0] = '\0';
	}
	if (!stash || !buffer)
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buffer)) + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	j = 0;
	if (stash)
		while (stash[++i] != '\0')
			new_str[i] = stash[i];
	while (buffer[j] != '\0')
		new_str[i++] = buffer[j++];
	new_str[ft_strlen(stash) + ft_strlen(buffer)] = '\0';
	free(stash);
	return (new_str);
}

/*
extracts FIRST line from stash
example:
"Hello\nWorld\n" -> "Hello\n"
if no '\n': "Hello" -> "Hello"
*/
char	*ft_get_line(char *stash)
{
	char	*line;
	int		i;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/*
removes first line from stash and keeps the rest
example:
"Hello\nWorld\n" -> "World\n"
if no newline -> free and return null
*/
char	*ft_new_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}
