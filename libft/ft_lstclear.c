/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitagaw <tkitagaw@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 09:00:58 by tkitagaw          #+#    #+#             */
/*   Updated: 2020/07/17 09:07:05 by tkitagaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **l, void (*del)(void *))
{
	t_list	*tmp;

	if (!l || !del)
		return ;
	while (*l)
	{
		if ((*l)->next == NULL)
		{
			ft_lstdelone(*l, del);
			*l = NULL;
			return ;
		}
		tmp = ((*l)->next);
		ft_lstdelone(*l, del);
		*l = NULL;
		*l = tmp;
	}
}
