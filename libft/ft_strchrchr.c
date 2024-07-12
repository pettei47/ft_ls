/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 02:36:26 by teppei            #+#    #+#             */
/*   Updated: 2021/06/14 14:56:00 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrchr(const char *s, char c1, char c2)
{
	char	*ret;

	ret = (char *)s;
	while (*ret)
	{
		if (*ret == c1 && *(ret + 1) == c2)
			return (ret);
		ret++;
	}
	return (NULL);
}
