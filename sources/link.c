/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:06:54 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/09 17:21:37 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_link(t_link *to_delete)
{
	free(to_delete->neighbour);
	free(to_delete);
}

void	print_link(t_room *room, char *message)
{
	ft_printf("%s\n", message);
	while (room != NULL)
	{
		while (room->link != NULL)
		{
			ft_printf("%s to %s\n", room->name, room->link->neighbour->name);
			room->link = room->link->next;
		}
		room = room->next;
	}
}

void	link_clear(t_link *to_clear)
{
	t_link *tmp;

	while (to_clear != NULL)
	{
		tmp = to_clear->next;
		free_link(to_clear);
		to_clear = tmp;
	}
}

void	init_link(t_link *link, t_room *room)
{
	link->neighbour = room;
	link->next = NULL;
}

t_link	*create_link(t_room *room)
{
	t_link *new;

	if (!(new = (t_link*)malloc(sizeof(t_link))))
		return (NULL);
	init_link(new, room);
	return (new);
}

void	link_push_back(t_room *src, t_link *to_add)
{
	t_link *tmp;

	if (src->link == NULL)
		src->link = to_add;
	else
	{
		tmp = src->link;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = to_add;
	}
}