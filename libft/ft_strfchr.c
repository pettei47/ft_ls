/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 23:16:20 by teppei            #+#    #+#             */
/*   Updated: 2021/06/14 14:58:10 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfchr(const char *s, int c)
{
	char	*ret;
	int		i;

	ret = (char *)s;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			ret[i] = '\0';
			return (ret);
		}
		i++;
	}
	return (NULL);
}
