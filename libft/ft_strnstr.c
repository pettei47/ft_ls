/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 19:20:05 by tkitagaw          #+#    #+#             */
/*   Updated: 2021/06/14 14:46:32 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_chk(const char *str, const char *to_find)
{
	int	i;

	i = 0;
	while (str[i] && to_find[i])
	{
		if (str[i] != to_find[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	tmp;

	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	if (ft_strlen(to_find) > ft_strlen(str) || ft_strlen(to_find) > len)
		return (0);
	while (str[i])
	{
		if (str[i] == to_find[0] && i <= len - ft_strlen(to_find))
		{
			tmp = i;
			if (ft_chk(&str[i], to_find) == 1)
				return ((char *)&str[tmp]);
		}
		i++;
	}
	return (0);
}
