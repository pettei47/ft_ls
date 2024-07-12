/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitagaw <tkitagaw@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 19:05:09 by tkitagaw          #+#    #+#             */
/*   Updated: 2020/07/18 20:18:59 by tkitagaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char const *s, size_t size)
{
	size_t	slen;
	size_t	i;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (size == 0)
		return (slen);
	i = 0;
	while (i < size - 1 && s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}
