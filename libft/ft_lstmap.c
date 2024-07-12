/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:49:22 by tkitagaw          #+#    #+#             */
/*   Updated: 2021/06/14 14:51:08 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*i;

	if (!l || !f)
		return (NULL);
	i = ft_lstnew(NULL);
	if (!i)
		return (NULL);
	new = i;
	while (i)
	{
		i->content = f(l->content);
		if (!(l->next))
			break ;
		i->next = ft_lstnew(NULL);
		if (!i)
		{
			ft_lstclear(&i, del);
			return (NULL);
		}
		i = i->next;
		l = l->next;
	}
	return (new);
}
