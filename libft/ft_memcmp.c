/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitagaw <tkitagaw@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:50:10 by tkitagaw          #+#    #+#             */
/*   Updated: 2020/07/15 23:07:21 by tkitagaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*q;
	size_t			i;

	i = 0;
	p = (unsigned char *)s1;
	q = (unsigned char *)s2;
	while (i < n && *p == *q)
	{
		i++;
		p++;
		q++;
	}
	if (i == n)
		return (0);
	return (*p - *q);
}
