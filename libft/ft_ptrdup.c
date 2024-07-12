/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 02:17:26 by teppei            #+#    #+#             */
/*   Updated: 2021/06/14 14:50:15 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_ptrdup(char **strs)
{
	char	**ret;
	int		i;

	i = 0;
	while (strs[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (strs[i])
	{
		ret[i] = ft_strdup(strs[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
