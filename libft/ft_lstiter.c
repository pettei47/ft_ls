/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkitagaw <tkitagaw@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:47:10 by tkitagaw          #+#    #+#             */
/*   Updated: 2020/07/17 14:48:57 by tkitagaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *l, void (*f)(void *))
{
	if (!l)
		return ;
	while (l)
	{
		f(l->content);
		l = l->next;
	}
	return ;
}
