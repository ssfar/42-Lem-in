/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:13:26 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/10 18:21:20 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

void	print_ant(t_lem_in *s)
{
	size_t	i;
	size_t	j;
	size_t	size;
	size_t	*path;
	ssize_t	*node;

	reset_map(s);
	size = count_nb_path(s);
	if (!(path = malloc(sizeof(size_t) * size)))
		exit_failure(s, NULL, 1, 0);
	if (!(node = malloc(sizeof(size_t) * size)))
		exit_failure(s, path, 1, 0);
	i = 0;
	j = 0;
	while (i < size)
	{
		while (s->room_tab[s->start].prio[j] != LOCK)
			j++;
		node[i] = s->room_tab[s->start].link[j];
		path[i] = get_size_path_prev(s, s->room_tab[s->start].link[j]);
		j++;
		i++;
	}
	bubble_sort_node(path, node, size);
	move_ant(s, get_ant(s, s->nb_ant, path, size), node, size);
}

void	move_ant(t_lem_in *s, size_t *path, ssize_t *node, size_t size)
{
	s->run = 1;
	s->ant = 1;
	while (s->run)
	{
		update_ant_pos(s);
		get_ant_out(s, path, node, size);
		if (s->run)
			ft_printf("\n");
	}
	free(path);
	free(node);
	exit_success(s);
}

void	get_ant_out(t_lem_in *s, size_t *path, ssize_t *node, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (path[i] > 0)
		{
			if (s->run)
				ft_printf(" ");
			path[i]--;
			s->room_tab[node[i]].ant = s->ant;
			ft_printf("L%zu-%s", s->ant, s->room_tab[node[i]].name);
			s->ant++;
			s->run = 1;
		}
		else
			s->room_tab[node[i]].ant = 0;
		i++;
	}
}

void	update_ant_pos(t_lem_in *s)
{
	size_t	i;

	s->run = 0;
	i = 0;
	while (i < s->room_tab[s->end].nb_link)
	{
		if (s->room_tab[s->end].prio[i] == PRIO)
		{
			if (s->room_tab[s->room_tab[s->end].link[i]].ant != 0)
			{
				if (s->run)
					ft_printf(" ");
				s->run = 1;
				ft_printf("L%zu-%s",
					s->room_tab[s->room_tab[s->end].link[i]].ant,
						s->room_tab[s->end].name);
			}
			get_prev_ant(s, s->room_tab[s->end].link[i]);
		}
		i++;
	}
}

void	print_start_to_end(t_lem_in *s)
{
	size_t	i;

	i = 0;
	while (i < s->room_tab[s->start].nb_link)
	{
		if (s->room_tab[s->start].link[i] == s->end)
		{
			print_info(s);
			i = 1;
			ft_printf("L%zu-%s", i, s->room_tab[s->end].name);
			i++;
			while (i <= s->nb_ant)
			{
				ft_printf(" L%zu-%s", i, s->room_tab[s->end].name);
				i++;
			}
			ft_printf("\n");
			exit_success(s);
		}
		i++;
	}
}
