/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitagaw <tkitagaw@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 00:37:55 by tkitagaw          #+#    #+#             */
/*   Updated: 2020/07/16 20:24:39 by tkitagaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*out;

	if (*s == '\0' && c != 0)
		return (NULL);
	if (ft_strlen(s) == 0 && c == 0)
		return ((char *)s);
	i = ft_strlen(s) - 1;
	out = (char *)s;
	if ((char)c == '\0')
		i++;
	while (0 < i && (char)s[i] != (char)c)
		i--;
	if ((char)s[i] == (char)c)
		return (&out[i]);
	else
		return (NULL);
}
