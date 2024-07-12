/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitagaw <tkitagaw@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:56:02 by tkitagaw          #+#    #+#             */
/*   Updated: 2020/07/06 22:08:34 by tkitagaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*q;

	i = 0;
	q = (unsigned char *)s;
	while (i < n)
	{
		q[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
