/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:24:16 by teppei            #+#    #+#             */
/*   Updated: 2021/11/02 01:43:44 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_ptr(char **ptrs)
{
	int	i;

	if (!ptrs)
		return ;
	i = -1;
	while (ptrs[++i])
	{
		free(ptrs[i]);
		ptrs[i] = NULL;
	}
	free(ptrs);
}
