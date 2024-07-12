/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrs_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 22:59:25 by teppei            #+#    #+#             */
/*   Updated: 2021/10/09 13:24:14 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrs_fd(char **strs, char *sep, int fd)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		ft_putstr_fd(strs[i++], fd);
		if (strs[i])
			ft_putstr_fd(sep, fd);
	}
}
