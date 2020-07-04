/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:34:02 by vrobin            #+#    #+#             */
/*   Updated: 2020/03/10 20:55:39 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

void	write_room(t_lem_in *s)
{
	size_t	i;

	if (!(s->room_tab = malloc(sizeof(t_room) * s->nb_room)))
		exit_failure(s, NULL, 0, 0);
	i = 0;
	while (i < MAP_SIZE)
	{
		write_room2(s, s->hmap[i], i);
		i++;
	}
}

void	write_room_alloc(t_lem_in *s, ssize_t j, size_t i, t_hashmap *tmp)
{
	if (!(s->room_tab[j].link = malloc(sizeof(ssize_t)
		* s->room_tab[j].nb_link)))
		clear_the_mess(s, i, tmp);
	if (!(s->room_tab[j].prio = malloc(sizeof(signed char)
		* s->room_tab[j].nb_link)))
	{
		free(s->room_tab[j].link);
		clear_the_mess(s, i, tmp);
	}
}

void	write_room2(t_lem_in *s, t_hashmap *tmp, size_t i)
{
	ssize_t	j;
	size_t	k;

	while (tmp)
	{
		j = tmp->room->index;
		s->room_tab[j] = *(tmp->room);
		free(tmp->room);
		if (s->room_tab[j].nb_link > 0)
		{
			write_room_alloc(s, j, i, tmp);
			k = 0;
			while (k < s->room_tab[j].nb_link)
			{
				s->room_tab[j].prio[k] = DEL;
				s->room_tab[j].link[k] = -1;
				k++;
			}
		}
		tmp->room = &s->room_tab[j];
		tmp = tmp->collision_next;
	}
}

void	write_link(t_lem_in *s)
{
	ssize_t	index1;
	size_t	i;
	t_room	*r;

	s->i_curr = s->i_pipe;
	while (s->i_curr != NULL)
	{
		i = 0;
		while (s->i_curr->str[0] == '#')
		{
			if (s->i_curr->i_next == NULL)
				return ;
			s->i_curr = s->i_curr->i_next;
		}
		while (s->i_curr->str[i] != '\0')
			i++;
		r = find_room(s, s->i_curr->str, hash_to_int(s->i_curr->str));
		index1 = r->index;
		i += 1;
		r = find_room(s, s->i_curr->str + i, hash_to_int(s->i_curr->str + i));
		if (index1 != r->index)
			add_link(s, index1, r->index);
		s->i_curr = s->i_curr->i_next;
	}
}

void	add_link(t_lem_in *s, ssize_t index1, ssize_t index2)
{
	size_t	i;

	i = 0;
	while (s->room_tab[index1].link[i] != -1
		&& i < s->room_tab[index1].nb_link)
	{
		if (s->room_tab[index1].link[i] == index2)
		{
			s->room_tab[index1].nb_link--;
			s->room_tab[index2].nb_link--;
			return ;
		}
		i++;
	}
	s->room_tab[index1].link_rm = s->room_tab[index1].nb_link;
	s->room_tab[index2].link_rm = s->room_tab[index2].nb_link;
	s->room_tab[index1].link[i] = index2;
	s->room_tab[index1].prio[i] = ALL;
	i = 0;
	while (s->room_tab[index2].link[i] != -1
		&& i < s->room_tab[index2].nb_link)
		i++;
	s->room_tab[index2].link[i] = index1;
	s->room_tab[index2].prio[i] = ALL;
}
