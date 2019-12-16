/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:20:38 by vrobin            #+#    #+#             */
/*   Updated: 2019/12/16 17:13:44 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

uint_fast8_t	is_collision(t_path way1, t_path way2)
{
	ssize_t i;
	ssize_t j;

	i = 1;
	while (i < way1.last_node)
	{
		j = 1;
		while (j < way2.last_node)
		{
			if (way1.path[i] == way2.path[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void		sort_way(t_lem_in *s)
{
	size_t i;
	t_path tmp;

	i = 0;
	while (i < s->p_last)
	{
		if (s->way[i].last_node > s->way[i + 1].last_node)
		{
			tmp = s->way[i];
			s->way[i] = s->way[i + 1];
			s->way[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

ssize_t		*get_way(t_lem_in *s)
{
	size_t	i; // current path
	size_t	j; // other path to add
	size_t	max_path; // room link to start && end
	ssize_t	*ret; // return tab (with indexs of all path who will be used)
	size_t	best_case; // best case found
	size_t	best_path; // best path int the current case
	size_t	act_ant; // ant left to use
	size_t	act_path; // index of current number of path
	size_t	new_case; // new current case 

	i = 0;
	new_case = 0;
	max_path = s->room_tab[s->start].link_rm;
	if (max_path > s->room_tab[s->end].link_rm)
		max_path = s->room_tab[s->start].link_rm;
	if (!(ret = malloc(sizeof(ssize_t) * max_path + 1)))
		exit_failure(s, 123, "can't malloc ret", 0);
	while (i <= max_path)
		ret[i++] = -1;
	i = 0;
	best_case = s->way[0].last_node + s->ant - 1;
	while (i <= s->p_last && s->way[i].last_node * max_path < best_case)
	{
		j = i + 1;
		act_path = 0;
		act_ant = s->ant;
		best_path = s->way[i].last_node;
		while (act_path <= max_path && j <= s->p_last)
		{
			if (is_collision(s->way[i], s->way[j]) == 0)
			{
				act_path++;
			}
			j++;
		}
		i++;
	}
	ft_printf("%d\n", best_case);
	return (ret);
}