/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_room_link.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:58:16 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/14 17:44:22 by vrobin           ###   ########.fr       */
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
			return ;
		i++;
	}
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
		s->pipe->str[i] = '-';
		i += 1;
		tmp = find_room(s, s->pipe->str + i, hash_to_int(s->pipe->str + i));
		index2 = tmp->index;
		add_link(s, index1, index2);
		s->pipe = s->pipe->i_next;
	}
}

void	init_room_tab(t_lem_in *s)
{
	size_t i;

	i = 0;
	if (!(s->room_tab = malloc(sizeof(t_room) * s->nb_room)))
		exit_failure(s, 123, "Malloc error room_tab");
	while (i < s->nb_room)
		s->room_tab[i++].link = NULL;
}

void	clear_unfinished_data_tab(t_lem_in *s, size_t i, t_table *unliked)
{
	size_t j;
	t_table *tmp;
	t_table *tmp2;

	j = i;
	tmp = unliked->t_next;
	while (tmp)
	{
		tmp2 = tmp->t_next;
		free(tmp->room);
		free(tmp);
		tmp = tmp2;
	}
	j++;
	while (j < MAP_SIZE)
	{
		tmp = s->map[j];
		while (tmp)
		{
			tmp2 = tmp->t_next;
			free(tmp->room);
			free(tmp);
			tmp = tmp2;
		}
		j++;
	}
	j = 0;
	while (j < i)
	{
		tmp = s->map[j];
		while (tmp)
		{
			tmp2 = tmp->t_next;
			free(tmp);
			tmp = tmp2;
		}
		j++;
	}
	tmp = s->map[i];
	while (tmp && tmp != unliked)
	{
			tmp2 = tmp->t_next;
			free(tmp);
			tmp = tmp2;
	}
	free(unliked);
	exit_failure(s, 3, "Malloc error room_tab");
}

void	write_room(t_lem_in *s)
{
	size_t	i;
	size_t	j;
	size_t k;
	t_table	*tmp;

	init_room_tab(s);
	i = 0;
	while (i < MAP_SIZE)
	{
		tmp = s->map[i];
		while (tmp)
		{
			j = tmp->room->index;
			s->room_tab[j] = *(tmp->room);
			free(tmp->room);
			if (s->room_tab[j].nb_link > 0)
			{
				if (!(s->room_tab[j].link = malloc(sizeof(ssize_t) * s->room_tab[j].nb_link)))
					clear_unfinished_data_tab(s, i, tmp);
				k = 0;
				while(k < s->room_tab[j].nb_link)
					s->room_tab[j].link[k++] = -1;
			}
			tmp->room = &s->room_tab[j];
			tmp = tmp->t_next;
		}
		i++;
	}
}