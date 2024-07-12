/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teppei <teppei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 23:54:16 by tkitagaw          #+#    #+#             */
/*   Updated: 2021/06/14 15:00:36 by teppei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	chk_alpha(int c)
{
	if (64 < c && c < 91)
		return (1);
	else if (96 < c && c < 123)
		return (1);
	else
		return (0);
}

static int	chk_digit(int c)
{
	if (47 < c && c < 58)
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if (chk_alpha(c) || chk_digit(c))
		return (1);
	else
		return (0);
}
