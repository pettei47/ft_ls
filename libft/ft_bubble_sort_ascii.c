/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubble_sort_ascii.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 02:24:09 by teppei            #+#    #+#             */
/*   Updated: 2021/06/14 14:58:24 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bubble_sort_ascii(char **strs)
{
	int		i;
	int		j;

	i = 0;
	while (strs[i])
	{
		j = i + 1;
		while (strs[j])
		{
			if (ft_strcmp(strs[i], strs[j]) > 0)
				swap_str(strs, i, j);
			j++;
		}
		i++;
	}
}
