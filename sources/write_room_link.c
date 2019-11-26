/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_room_link.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:58:16 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/26 18:01:47 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

void			add_link(t_lem_in *s, ssize_t index1, ssize_t index2)
{
	size_t	i;

	if (index1 == index2)
		return ;
	i = 0;
	while (s->room_tab[index1].link[i] != -1)
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
	i = 0;
	while (s->room_tab[index2].link[i] != -1)
		i++;
	s->room_tab[index2].link[i] = index1;
}

void			write_link(t_lem_in *s)
{
	ssize_t	index1;
	ssize_t	index2;
	size_t	i;
	t_room	*tmp;

	while (s->pipe != NULL)
	{
		i = 0;
		while (s->pipe->str[0] == '#')
		{
			if (s->pipe->i_next == NULL)
				return;
			s->pipe = s->pipe->i_next;
		}
		while (s->pipe->str[i] != '\0')
			i++;
		tmp = find_room(s, s->pipe->str, hash_to_int(s->pipe->str));
		index1 = tmp->index;
		i += 1;
		tmp = find_room(s, s->pipe->str + i, hash_to_int(s->pipe->str + i));
		index2 = tmp->index;
		add_link(s, index1, index2);
		s->pipe = s->pipe->i_next;
	}
}

// void	init_room_tab(t_lem_in *s)
// {
// 	size_t i;

// 	i = 0;
// 	if (!(s->room_tab = malloc(sizeof(t_room) * s->nb_room)))
// 		exit_failure(s, 1, "Malloc error room_tab", 0);
// 	while (i < s->nb_room)
// 		s->room_tab[i++].link = NULL;
// }

void	write_room2(t_lem_in *s, t_table *tmp, size_t i)
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
			if (!(s->room_tab[j].link
				= malloc(sizeof(ssize_t) * s->room_tab[j].nb_link)))
				clear_the_mess(s, i, tmp);
			k = 0;
			while (k < s->room_tab[j].nb_link)
				s->room_tab[j].link[k++] = -1;
		}
		tmp->room = &s->room_tab[j];
		tmp = tmp->t_next;
	}
}

void	write_room(t_lem_in *s)
{
	size_t	i;

	if (!(s->room_tab = malloc(sizeof(t_room) * s->nb_room)))
		exit_failure(s, 1, "Malloc error room_tab", 0);
	i = 0;
	while (i < MAP_SIZE)
	{
		write_room2(s, s->map[i], i);
		i++;
	}
}

// void	write_room(t_lem_in *s)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	k;
// 	t_table	*tmp;

// 	if (!(s->room_tab = malloc(sizeof(t_room) * s->nb_room)))
// 		exit_failure(s, 1, "Malloc error room_tab", 0);
// 	i = 0;
// 	while (i < MAP_SIZE)
// 	{
// 		tmp = s->map[i];
// 		while (tmp)
// 		{
// 			j = tmp->room->index;
// 			s->room_tab[j] = *(tmp->room);
// 			free(tmp->room);
// 			if (s->room_tab[j].nb_link > 0)
// 			{
// 				if (!(s->room_tab[j].link = malloc(sizeof(ssize_t) * s->room_tab[j].nb_link)))
// 					clear_the_mess(s, i, tmp);
// 				k = 0;
// 				while (k < s->room_tab[j].nb_link)
// 					s->room_tab[j].link[k++] = -1;
// 			}
// 			tmp->room = &s->room_tab[j];
// 			tmp = tmp->t_next;
// 		}
// 		i++;
// 	}
// }