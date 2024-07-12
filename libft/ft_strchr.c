/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitagaw <tkitagaw@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 00:33:09 by tkitagaw          #+#    #+#             */
/*   Updated: 2020/07/06 15:58:45 by tkitagaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*out;

	out = (char *)s;
	while (*out && *out != (char)c)
		out++;
	if (*out == (char)c)
		return (out);
	else
		return (NULL);
}
