/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:44:15 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/11 14:14:33 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

t_room	*init_room(t_lem_in *s, t_hashmap *new, char *name)
{
	new->room = NULL;
	if (!(new->room = malloc(sizeof(t_room))))
		exit_failure(s, NULL, 0, 0);
	new->room->name = name;
	new->room->index = s->nb_room;
	new->room->nb_link = 0;
	new->room->link = NULL;
	new->room->cost = SIZE_T_MAX;
	new->room->prio = NULL;
	new->room->ascend = 0;
	new->room->prev = -1;
	new->room->ant = 0;
	return (new->room);
}

void	init_struct(t_lem_in *s)
{
	s->info = NULL;
	s->room_tab = NULL;
	s->on_q = NULL;
	s->queu = NULL;
	init_hmap(s);
}

void	init_algo(t_lem_in *s)
{
	s->on_size = (s->nb_room / 8) + 1;
	if (s->nb_room > ROOM_OVERFLOW)
		exit_failure(s, NULL, 1, 0);
	if (!(s->queu = malloc(sizeof(size_t) * s->nb_room * s->nb_room)))
		exit_failure(s, NULL, 1, 0);
	s->room_tab[s->start].cost = 0;
	if (!(s->on_q = malloc(sizeof(unsigned char) * s->on_size)))
		exit_failure(s, NULL, 1, 0);
	ft_bzero(s->on_q, s->on_size);
	hunt_deadend(s, s->start, s->end, s->room_tab);
	if (s->room_tab[s->start].link_rm < 1 || s->room_tab[s->end].link_rm < 1)
		exit_failure(s, NULL, 1, 1);
}

void	init_hmap(t_lem_in *s)
{
	size_t	i;

	i = 0;
	while (i < MAP_SIZE)
	{
		s->hmap[i] = NULL;
		i++;
	}
}
