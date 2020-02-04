/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 18:45:47 by vrobin            #+#    #+#             */
/*   Updated: 2020/02/04 18:07:12 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

void	init_ant_tab(t_lem_in *s)
{
	size_t	i;

	i = 0;
	if (!(s->res->ant_tab = malloc(sizeof(ssize_t) * s->ant)))
		exit_failure(s, 123, "malloc ant_tab", 0);
	while (i < s->ant)
	{
		s->res->ant_tab[i] = 0;
		i++;
	}
}

void	init_ant_path(t_lem_in *s, ssize_t * final)
{
	size_t i;
	size_t	ant;
	size_t	path;

	i = 0;
	ant = s->ant;
	path = s->max_path;
	if (!(s->res->ant_path = malloc(sizeof(ssize_t) * s->max_path)))
		exit_failure(s, 123, "malloc s->res->ant_path", 0);
	if (!(s->res->ant_start = malloc(sizeof(ssize_t) * s->max_path)))
		exit_failure(s, 123, "malloc res", 0);
	while (i < s->max_path && ant > 0)
	{
		s->res->ant_start[i] = 0;
		if (i < s->max_path - 1)
			s->res->ant_path[i] = calculate_case(s->way[final[0]].last_node, s->way[final[i]].last_node, ant, path);
		else
			s->res->ant_path[i] = ant;
		ant -= s->res->ant_path[i];
		path--;
		i++;
	}
}

size_t	count_arrived(t_lem_in *s, ssize_t *final, size_t lock_path)
{
	size_t	act_path;
	size_t	i;
	ssize_t	ant_arrived;

	i = lock_path;
	act_path = lock_path;
	ant_arrived = 0;
	while (i < s->ant - 1 && s->res->ant_tab[i] != 0)
	{
		if (lock_path == act_path && s->res->ant_tab[i] == s->way[final[lock_path]].last_node + 1)
		{
			// ft_printf("%d has arrived ", i);
			ant_arrived++;
		}
		act_path = act_path < s->max_path - 1 ? act_path + 1 : 0;
		i++;
	}
	return (ant_arrived);
}

size_t		last_ant_arrived(t_lem_in *s, ssize_t *final)
{
	size_t	i;
	size_t	act_path;

	i = 0;
	act_path = 0;
	while (i < s->ant)
	{
		if (i != 0)
			act_path = act_path < s->max_path - 1 ? act_path + 1 : 0;
		if (s->res->ant_tab[i] < s->way[final[act_path]].last_node + 1)
			break;
		i++;
	}
	return (i);
}

size_t	print_turn(t_lem_in *s, ssize_t *final)
{
	size_t	i;
	size_t	act_path;
	size_t	new_max_path;

	i = 0;
	act_path = 0;
	new_max_path = s->max_path;
	while (i < s->ant)
	{
		if (s->res->ant_tab[i] == 0)
			break;
		if (i != 0)
			act_path = act_path < new_max_path - 1 ? act_path + 1 : 0;
		if (s->res->ant_tab[i] < s->way[final[act_path]].last_node + 1)
			ft_printf("L%d-%s ", i, s->room_tab[s->way[final[act_path]].path[s->res->ant_tab[i]]].name);
		if (new_max_path > 1 && (ssize_t)((i + 1) / new_max_path) == s->res->ant_path[new_max_path - 1])
			new_max_path -= 1;
		i++;
	}
	i = 0;
	act_path = 0;
	new_max_path = s->max_path;
	while (i < s->ant)
	{
		if (new_max_path > 1 && (ssize_t)((i + 1) / new_max_path) == s->res->ant_path[new_max_path - 1])
			new_max_path -= 1;
		if (i != 0)
			act_path = act_path < new_max_path - 1 ? act_path + 1 : 0;
		if (s->res->ant_tab[i] == s->way[final[act_path]].last_node)
			s->res->ant_tab[i]++;
		i++;
	}
	ft_printf("\n");
	return(1);
}

void		throw_ant(t_lem_in *s, ssize_t *final)
{
	size_t	i;
	size_t	to_throw;
	size_t	act_path;
	ssize_t	turn;
	size_t	new_max_path;
	size_t	max;
	size_t	up;

	if (!(s->res = (t_throw*)malloc(sizeof(t_throw))))
		exit_failure(s, 123, "malloc res", 0);
	init_ant_tab(s);
	init_ant_path(s, final);
	print_stab(s->res->ant_tab, s->ant, "ant_tab");
	print_stab(s->res->ant_path, s->max_path, "ant_path");
	print_stab(s->res->ant_start, s->max_path, "ant_start");
	to_throw = 0;
	act_path = 0;
	turn = 0;
	new_max_path = s->max_path;
	while (s->res->ant_tab[s->ant - 1] < s->way[final[new_max_path - 1]].last_node + 1)
	{
		up = 0;
		act_path = 0;
		to_throw++;
		if (s->res->ant_start[new_max_path - 1] == 1)
			max = max + new_max_path;
		else
			max = to_throw * new_max_path;
		new_max_path = s->max_path;
		i = 0;
		while (up < max && i < s->ant)
		{
			if (i != 0)
				act_path = act_path < new_max_path - 1 ? act_path + 1 : 0;
			if (s->res->ant_tab[i] != s->way[final[act_path]].last_node + 1)
			{
				s->res->ant_tab[i]++;
			}
			if (new_max_path > 1 && (ssize_t)((i + 1) / new_max_path) == s->res->ant_path[new_max_path - 1])
			{
				new_max_path--;
				s->res->ant_start[new_max_path - 1] = 1;
			}
			up++;
			i++;
		}
		turn += print_turn(s, final);
	}
	ft_printf("turn vaut : %d\n", turn);
}