/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 18:45:47 by vrobin            #+#    #+#             */
/*   Updated: 2020/01/21 17:58:53 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

ssize_t	*init_ant_tab(t_lem_in *s)
{
	ssize_t	*ant_tab;
	size_t	i;

	i = 0;
	if (!(ant_tab = malloc(sizeof(ssize_t) * s->ant)))
		exit_failure(s, 123, "malloc ant_tab", 0);
	while (i < s->ant)
	{
		ant_tab[i] = 0;
		i++;
	}
	return (ant_tab);
}

ssize_t	*init_ant_path(t_lem_in *s, ssize_t * final)
{
	size_t i;
	size_t	ant;
	size_t	path;
	ssize_t	*ant_path;

	i = 0;
	ant = s->ant;
	path = s->max_path;
	if (!(ant_path = malloc(sizeof(ssize_t) * s->max_path)))
		exit_failure(s, 123, "malloc ant_path", 0);
	while (i < s->max_path && ant > 0)
	{
		if (i < s->max_path - 1)
			ant_path[i] = calculate_case(s->way[final[0]].last_node, s->way[final[i]].last_node, ant, path);
		else
			ant_path[i] = ant;
		ant -= ant_path[i];
		path--;
		i++;
	}
	return (ant_path);
}

size_t	print_turn(t_lem_in *s, ssize_t *ant_tab, ssize_t *final, size_t ant_arrived)
{
	// static size_t nb_turn = 0;
	size_t	i;
	size_t	act_path;

	i = 0;
	act_path = s->max_path - 1;
	while (i < s->ant)
	{
		if (ant_tab[i] == 0)
			break;
		act_path = act_path < s->max_path - 1 ? act_path + 1 : 0;
		if (ant_tab[i] < s->way[final[act_path]].last_node + 1)
			ft_printf("L%d-%s ", i, s->room_tab[s->way[final[act_path]].path[ant_tab[i]]].name);
		i++;
	}
	i = 0;
	act_path = s->max_path - 1;
	while (i < s->ant)
	{
		act_path = act_path < s->max_path - 1 ? act_path + 1 : 0;
		if (ant_tab[i] == s->way[final[act_path]].last_node)
		{
			ant_tab[i]++;
			ant_arrived++;
			// ft_printf("ant %d on path %d has arrived !", i, act_path);
		}
		i++;
	}
	ft_printf("\n");
	return(ant_arrived);
}

void		throw_ant(t_lem_in *s, ssize_t *final)
{
	size_t	i;
	ssize_t	*ant_tab;
	ssize_t	*ant_path;
	size_t	act_path;
	size_t	to_throw;
	size_t	ant_arrived;

	ant_arrived = 0;
	ant_tab = init_ant_tab(s);
	ant_path = init_ant_path(s, final);
	to_throw = 0;
	act_path = 0;
	i = 0;
	while (ant_tab[s->ant - 1] < s->way[final[act_path]].last_node + 1)
	{
		to_throw++;
		act_path = ant_arrived % s->max_path - 0;
		if (act_path < s->max_path - 1 && i != 0)
			act_path++;
		else
			act_path = 0;
		while (i < to_throw * s->max_path && i < s->ant)
		{
			act_path = act_path < s->max_path - 1 ? act_path + 1 : 0;
			if (ant_tab[i] < s->way[final[act_path]].last_node)
			{
				if (ant_tab[i] == 0)
					ant_path[act_path]--;
				ant_tab[i]++;
			}
			i++;
		}
		i = 0;
		ant_arrived = print_turn(s, ant_tab, final, ant_arrived);
		if (ant_path[0] == 0)
			s->max_path--;
		// print_stab(ant_path, s->max_path, "ant_path");
	}
}