/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:58:45 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/10 21:08:30 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

void	retrace_path(t_lem_in *s, size_t node, size_t *path_size)
{
	size_t i;

	i = 0;
	(*path_size)++;
	while (i < s->room_tab[node].nb_link)
	{
		if (s->room_tab[node].prio[i] == LOCK)
			return (retrace_path(s, s->room_tab[node].link[i], path_size));
		i++;
	}
}

size_t	get_size_path(t_lem_in *s, size_t act_path)
{
	ssize_t	i;
	size_t	j;
	size_t	ret;

	i = s->room_tab[act_path].index;
	ret = 1;
	while (i != s->end)
	{
		j = 0;
		while (s->room_tab[i].prio[j] != LOCK)
			j++;
		ret++;
		i = s->room_tab[i].link[j];
	}
	return (ret);
}

size_t	get_size_path_prev(t_lem_in *s, size_t act_path)
{
	ssize_t	i;
	size_t	j;
	size_t	ret;

	i = s->room_tab[act_path].index;
	ret = 1;
	while (i != s->end)
	{
		j = 0;
		while (s->room_tab[i].prio[j] != LOCK)
			j++;
		s->room_tab[s->room_tab[i].link[j]].prev = s->room_tab[i].index;
		ret++;
		i = s->room_tab[i].link[j];
	}
	return (ret);
}

size_t	count_path(t_lem_in *s, size_t i, size_t j, size_t size)
{
	size_t	*path;
	size_t	ret;

	size = count_nb_path(s);
	if (size == 0 || !(path = malloc(sizeof(size_t) * size)))
		exit_failure(s, NULL, 1, 0);
	i = 0;
	while (i < size)
	{
		while (s->room_tab[s->start].prio[j] != LOCK)
			j++;
		path[i] = get_size_path(s, s->room_tab[s->start].link[j]);
		j++;
		i++;
	}
	bubble_sort(path, size);
	ret = count_turn(s, s->nb_ant, path, size);
	free(path);
	return (ret);
}

size_t	count_nb_path(t_lem_in *s)
{
	size_t	i;
	size_t	nb_path;

	i = 0;
	nb_path = 0;
	while (i < s->room_tab[s->start].nb_link)
	{
		if (s->room_tab[s->start].prio[i] == LOCK)
			nb_path++;
		i++;
	}
	return (nb_path);
}
