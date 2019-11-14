/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_room_link.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:58:16 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/14 22:57:12 by ssfar            ###   ########.fr       */
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

void	clean_before_unlinked(t_lem_in *s, size_t i, t_table *unliked)
{
	t_table	*tmp;
	t_table	*tmp2;
	size_t	j;

	j = 0;
	while (j < i)
	{
		tmp = s->map[j];
		while (tmp)
		{
			free(s->room_tab[tmp->room->index].link);
			tmp2 = tmp->t_next;
			free(tmp);
			tmp = tmp2;
		}
		j++;
	}
	tmp = s->map[i];
	while (tmp && tmp != unliked)
	{
		free(s->room_tab[tmp->room->index].link);
		tmp2 = tmp->t_next;
		free(tmp);
		tmp = tmp2;
	}
}

void	clean_after_unlinked(t_lem_in *s, size_t i, t_table *tmp)
{
	size_t	j;
	t_table	*tmp2;

	while (tmp)
	{
		tmp2 = tmp->t_next;
		free(tmp->room);
		free(tmp);
		tmp = tmp2;
	}
	j = i + 1;
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
}

void	clear_the_mess(t_lem_in *s, size_t i, t_table *unlinked)
{
	clean_before_unlinked(s, i, unlinked);
	free(s->room_tab);
	clean_after_unlinked(s, i, unlinked->t_next);
	free(unlinked);
	exit_failure(s, 0, "Malloc error room_tab", 0);
}

void	write_room(t_lem_in *s)
{
	size_t	i;
	size_t	j;
	size_t	k;
	t_table	*tmp;

	if (!(s->room_tab = malloc(sizeof(t_room) * s->nb_room)))
		exit_failure(s, 1, "Malloc error room_tab", 0);
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
					clear_the_mess(s, i, tmp);
				k = 0;
				while (k < s->room_tab[j].nb_link)
					s->room_tab[j].link[k++] = -1;
			}
			tmp->room = &s->room_tab[j];
			tmp = tmp->t_next;
		}
		i++;
	}
}