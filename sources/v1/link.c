/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:06:54 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/11 20:47:45 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_link(t_link *to_delete)
{
	free(to_delete->jump);
	free(to_delete);
}

void	print_link(t_room *room, char *message)
{
	size_t	i;
	size_t	nb_total_links;

	ft_printf("[yellow]%s[a_bold]\n", message);
	nb_total_links = 0;
	while (room != NULL)
	{
		while (room->link != NULL)
		{
			nb_total_links++;
			i = 0;
			while (room->name[i] && room->name[i] != ' ')	
				write(1, &room->name[i++], 1);
			i = 0;
			write(1, "_", 1);
			while (room->link->jump->name[i] && room->link->jump->name[i] != ' ')
				write(1, &room->link->jump->name[i++], 1);
			room->link = room->link->l_next;
			write(1, "\n", 1);
		}
		room = room->r_next;
	}
	ft_printf("Number of links = %zd[a_reset]\n", nb_total_links);
}

void	link_clear(t_link *to_clear)
{
	t_link *tmp;

	while (to_clear != NULL)
	{
		tmp = to_clear->l_next;
		free_link(to_clear);
		to_clear = tmp;
	}
}

void	init_link(t_link *link, t_room *room)
{
	link->jump = room;
	link->l_next = NULL;
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
		while (tmp->l_next != NULL)
			tmp = tmp->l_next;
		tmp->l_next = to_add;
	}
}