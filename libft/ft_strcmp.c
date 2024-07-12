/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:17:55 by teppei            #+#    #+#             */
/*   Updated: 2021/06/14 15:02:53 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*p;
	unsigned char	*q;
	int				i;
	int				len;
	int				len2;

	i = 0;
	p = (unsigned char *)s1;
	q = (unsigned char *)s2;
	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len < len2)
		len = len + 1;
	else
		len = len2 + 1;
	while (i < len)
	{
		if (p[i] != q[i])
			return (p[i] - q[i]);
		i++;
	}
	return (0);
}
