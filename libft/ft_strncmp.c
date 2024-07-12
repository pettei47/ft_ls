/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitagaw <tkitagaw@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 19:02:51 by tkitagaw          #+#    #+#             */
/*   Updated: 2020/07/17 00:06:59 by tkitagaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*q;
	size_t			i;

	i = 0;
	p = (unsigned char *)s1;
	q = (unsigned char *)s2;
	while (p[i] == q[i] && p[i] && q[i] && n > 0)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return (p[i] - q[i]);
}
