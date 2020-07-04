/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:07:30 by vrobin            #+#    #+#             */
/*   Updated: 2020/03/10 18:19:32 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

void		delete_link(t_lem_in *s, t_room *room_tab, ssize_t *link, ssize_t i)
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
		room_tab[j].prio[k] = DEL;
		if (room_tab[j].link_rm == 1 && j != s->start && j != s->end)
			return (delete_link(s, room_tab, room_tab[j].link, j));
	}
}

void		set_link_to_all(t_lem_in *s, ssize_t i, size_t j)
{
	s->room_tab[i].prio[j] = ALL;
	j = 0;
	while (s->room_tab[s->room_tab[i].prev].link[j] != i)
		j++;
	s->room_tab[s->room_tab[i].prev].prio[j] = ALL;
}

void		edit_link(t_lem_in *s)
{
	ssize_t	i;
	size_t	j;

	i = s->end;
	while (i != s->start)
	{
		j = 0;
		while (s->room_tab[i].prev != s->room_tab[i].link[j])
			j++;
		if (s->room_tab[i].prio[j] == ALL)
		{
			s->room_tab[i].prio[j] = PRIO;
			j = 0;
			while (s->room_tab[s->room_tab[i].prev].link[j] != i)
				j++;
			s->room_tab[s->room_tab[i].prev].prio[j] = LOCK;
		}
		else
			set_link_to_all(s, i, j);
		i = s->room_tab[i].prev;
	}
}

size_t		check_ledit(t_lem_in *s)
{
	ssize_t	i;
	size_t	j;

	i = s->end;
	while (i != s->start)
	{
		j = 0;
		if (s->room_tab[i].prev == -1)
			return (0);
		while (s->room_tab[i].prev != s->room_tab[i].link[j])
			j++;
		if (add_on(s->on_q, s->room_tab[i].link[j]) == 0)
			return (0);
		i = s->room_tab[i].prev;
	}
	return (1);
}
