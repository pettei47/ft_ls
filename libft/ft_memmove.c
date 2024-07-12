/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitagaw <tkitagaw@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:12:51 by tkitagaw          #+#    #+#             */
/*   Updated: 2020/07/13 18:42:03 by tkitagaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p;
	unsigned char	*q;

	p = (unsigned char *)dst;
	q = (unsigned char *)src;
	if (p > q)
	{
		while (len--)
			p[len] = q[len];
	}
	else
		ft_memcpy(p, q, len);
	return (dst);
}
