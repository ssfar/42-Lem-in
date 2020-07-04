/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:54:57 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/10 18:41:27 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

void	bfs(t_lem_in *s, unsigned char on)
{
	t_room	*tab;
	size_t	cur;

	cur = 0;
	s->queu[0] = s->start;
	s->q_last = 0;
	tab = s->room_tab;
	while (cur <= s->q_last)
	{
		if (tab[s->queu[cur]].ascend)
			ascend_case(s, &tab[s->queu[cur]], tab, on);
		else
			normal_case(s, &tab[s->queu[cur]], tab, on);
		cur++;
	}
}

void	normal_case(t_lem_in *s, t_room *room, t_room *tab, unsigned char on)
{
	size_t	i;

	i = 0;
	while (i < room->nb_link)
	{
		if (room->prio[i] == PRIO)
		{
			if (room->cost + 1 < tab[room->link[i]].cost || (on > 1 && on < 4))
			{
				if (room->link[i] != s->end)
				{
					s->q_last++;
					s->queu[s->q_last] = room->link[i];
				}
				tab[room->link[i]].cost = room->cost + 1;
				tab[room->link[i]].prev = room->index;
				tab[room->link[i]].ascend = 1;
			}
			return ;
		}
		i++;
	}
	search_for_all(s, room, tab, on);
}

void	ascend_case(t_lem_in *s, t_room *room, t_room *tab, unsigned char on)
{
	size_t	i;

	i = 0;
	(void)on;
	room->ascend = 0;
	if (!search_for_all(s, room, tab, on))
		while (i < room->nb_link)
		{
			if (room->prio[i] == PRIO)
			{
				if (room->cost + 1 < tab[room->link[i]].cost || on > 2)
				{
					if (room->link[i] != s->end)
					{
						s->q_last++;
						s->queu[s->q_last] = room->link[i];
					}
					tab[room->link[i]].cost = room->cost + 1;
					tab[room->link[i]].prev = room->index;
					tab[room->link[i]].ascend = 1;
				}
				return ;
			}
			i++;
		}
}

char	search_for_all(t_lem_in *s, t_room *room, t_room *tab, unsigned char on)
{
	size_t	i;
	char	all_found;

	i = 0;
	(void)on;
	all_found = 0;
	while (i < room->nb_link)
	{
		if (room->prio[i] == ALL)
		{
			if (room->cost + 1 < tab[room->link[i]].cost)
			{
				all_found = 1;
				if (room->link[i] != s->end)
				{
					s->q_last++;
					s->queu[s->q_last] = room->link[i];
				}
				tab[room->link[i]].cost = room->cost + 1;
				tab[room->link[i]].prev = room->index;
			}
		}
		i++;
	}
	return (all_found);
}
