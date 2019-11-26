/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 10:33:11 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/26 18:01:48 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

void	suppr_other_side(t_room *room, ssize_t to_suppr)
{
	size_t	i;

	i = 0;
	while (room->link[i] != to_suppr)
		i++;
	room->link[i] = -2;
}

void	update_link(t_lem_in *s, ssize_t i)
{
	size_t	j;
	ssize_t	to_suppr;

	i = 0;
	j = 0;
	while (i < s->nb_room)
	{
		if (s->room_tab[i].link_rm == 1 && i != s->start && i != s->end)
		{
			j = 0;
			while (s->room_tab[i].link[j] == -2)
				j++;
			to_suppr = s->room_tab[i].link[j];
			suppr_other_side(&s->room_tab[to_suppr], i);
			s->room_tab[i].link[j] = -2;
			s->room_tab[i].link_rm--;
			s->room_tab[to_suppr].link_rm--;
			if (s->room_tab[to_suppr].link_rm == 1)
				update_link(s, to_suppr);
		}
		i++;
	}
}