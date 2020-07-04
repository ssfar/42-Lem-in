/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_return.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:11:22 by vrobin            #+#    #+#             */
/*   Updated: 2020/03/10 18:20:37 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

void	reset_map(t_lem_in *s)
{
	ssize_t	i;

	i = 0;
	while (i < s->nb_room)
	{
		s->room_tab[i].ascend = 0;
		s->room_tab[i].cost = SIZE_T_MAX;
		s->room_tab[i].prev = -1;
		i++;
	}
	s->room_tab[s->start].cost = 0;
}

void	full_reset(t_lem_in *s)
{
	ssize_t	i;
	size_t	j;

	i = 0;
	while (i < s->nb_room)
	{
		j = 0;
		while (j < s->room_tab[i].nb_link)
		{
			if (s->room_tab[i].prio[j] != -2)
				s->room_tab[i].prio[j] = 0;
			j++;
		}
		i++;
	}
	reset_map(s);
}

size_t	count_turn(t_lem_in *s, size_t nb_ant, size_t *path, size_t size)
{
	size_t	i;
	size_t	ret;
	size_t	*ant_tab;

	i = 0;
	ret = 0;
	if ((ant_tab = get_ant(s, nb_ant, path, size)) == NULL)
		return (SIZE_T_MAX);
	while (i < size)
	{
		path[i] += ant_tab[i] - 1;
		i++;
	}
	free(ant_tab);
	i = 0;
	ret = 0;
	while (i < size)
	{
		if (path[i] > ret)
			ret = path[i];
		i++;
	}
	return (ret);
}

void	return_to_the_future(t_lem_in *s)
{
	ssize_t	i;
	size_t	j;

	i = s->end;
	while (i != s->start)
	{
		j = 0;
		while (s->room_tab[i].prev != s->room_tab[i].link[j])
			j++;
		if (s->room_tab[i].prio[j] == PRIO)
			set_link_to_all(s, i, j);
		else
		{
			s->room_tab[i].prio[j] = LOCK;
			j = 0;
			while (s->room_tab[s->room_tab[i].prev].link[j] != i)
				j++;
			s->room_tab[s->room_tab[i].prev].prio[j] = PRIO;
		}
		i = s->room_tab[i].prev;
	}
}
