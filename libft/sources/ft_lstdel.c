/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <samisfar.dev@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 19:07:36 by ssfar             #+#    #+#             */
/*   Updated: 2020/07/24 11:10:47 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Take the pointer of a link from a list (alst), free him and all the
** following links and set the pointer to NULL.
*/

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*tmp;

	while (*alst)
	{
		tmp = (*alst)->next;
		ft_lstdelone((alst), del);
		*alst = tmp;
	}
	free(*alst);
	*alst = NULL;
}
