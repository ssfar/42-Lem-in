/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 10:33:11 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/27 16:48:41 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

void	suppr_node_link(t_lem_in *s, t_room *room_tab, ssize_t *link, ssize_t i)
{
	ssize_t	j;
	ssize_t	k;

	room_tab[i].link_rm = 0;
	j = 0;
	while (link[j] == -2)
		j++;
	j = link[j];
	room_tab[j].link_rm--;	
	if (room_tab[j].link_rm > 0)
	{
		k = 0;
		while (room_tab[j].link[k] != i)
			k++;
		room_tab[j].link[k] = -2;
		if (room_tab[j].link_rm == 1 && j != s->start && j != s->end)
			return (suppr_node_link(s, room_tab, room_tab[j].link, j));
	}
}

void	update_link(t_lem_in *s, ssize_t start, ssize_t end, t_room *room_tab)
{
	ssize_t	i;
	ssize_t	nb_room;

	i = 0;
	nb_room = s->nb_room;
	while (i < nb_room)
	{
		if (room_tab[i].link_rm == 1 && i != start && i != end)
			suppr_node_link(s, room_tab, room_tab[i].link, i);
		i++;
	}
}