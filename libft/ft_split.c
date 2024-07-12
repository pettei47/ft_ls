/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 00:47:26 by tkitagaw          #+#    #+#             */
/*   Updated: 2021/06/14 15:17:25 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	c_count(char const *s, char c)
{
	char	*str;
	size_t	i;
	size_t	count;

	str = (char *)s;
	i = 1;
	count = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != c && str[i - 1] == c)
			count++;
		i++;
	}
	count++;
	if (str[i] == '\0' && str[i - 1] != c)
		count++;
	return (count);
}

static char	*mkstr(char *s, char c, char *o)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s[len] != c && s[len])
		len++;
	o = (char *)malloc(sizeof(char) * (len + 1));
	if (!o)
		return (NULL);
	while (i < len)
	{
		o[i] = s[i];
		i++;
	}
	o[i] = '\0';
	return (o);
}

static char	**my_free(char **o)
{
	size_t	i;

	i = 0;
	while (o[i])
		free(o[i++]);
	free(o);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**outcome;
	char	*str;
	size_t	i;

	if (s == NULL)
		return (NULL);
	str = (char *)s;
	outcome = (char **)malloc(sizeof(char *) * (c_count(s, c)));
	if (!outcome)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str != c)
		{
			outcome[i] = mkstr(str, c, outcome[i]);
			if (!outcome[i])
				return (my_free(outcome));
			str += ft_strlen(outcome[i++]) - 1;
		}
		str++;
	}
	outcome[i] = NULL;
	return (outcome);
}
