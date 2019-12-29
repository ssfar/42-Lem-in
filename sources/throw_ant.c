/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 18:45:47 by vrobin            #+#    #+#             */
/*   Updated: 2019/12/29 16:26:37 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

//
void	print_ant_tab(t_lem_in *s, final, size_t *ant_tab, char *message)
{
	size_t	i;
	ssize_t	j;

	ft_printf("%s\n", message);
	i = 0;
	while (i < s->max_path)
	{
		j = 0;
		ft_printf("Path [%d]\n", i);
		while (ant_tab[i][j] != -1)
		{
			ft_printf("%d\n", ant_tab[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
//

size_t		calcul_ant(t_lem_in *s, ssize_t *final, size_t c_ant, size_t i)
{
	if (s->max_path == 1)
		return (s->way[final[0]].last_node + (c_ant - 1) - 1);
	else
		return ((c_ant + s->way[final[0]].last_node - 1 - s->way[final[i]].last_node) / s->max_path);
}

void	print_turn(t_lem_in *s, ssize_t **ant_tab, ssize_t *final)
{
	size_t i;
	ssize_t j;

	i = 0;
	while (i < s->max_path)
	{
		j = 0;
		while (j < s->way[final[i]].last_node && ant_tab[i][j] >= 0)
		{
			if (ant_tab[i][j] != -1)
				ft_printf("L%d-%s ", ant_tab[i][j], s->room_tab[s->way[final[i]].path[j + 1]].name);
			j++;
		}
		i++;
	}
	ft_printf("\n");
}

ssize_t	***init_ant_tab(t_lem_in *s, ssize_t *final)
{
	ssize_t	***ant_tab;
	size_t	act_ant;
	size_t	i;
	size_t	j;

	i = 0;
	act_ant = s->ant;
	if (!(ant_tab = malloc(sizeof(size_t**) * calculate_best_case(s->way[final[max_path]].last_node, s->ant, s->max_path)))
		exit_failure(s, 123, "malloc ant_tab", 0);
	while (i < s->max_path - 1)
	{
		j = 0;
		if (!(ant_tab[i] = malloc(sizeof(size_t) * s->way[final[i]].last_node)))
			exit_failure(s, 123, "malloc ant_tab", 0);
		while (j < act_ant)
		{
			ant_tab[i][j] = 0;
			j++;
		}
		i++;
	}
	return (ant_tab);
}

void		fill_tab(t_lem_in *s, ssize_t *ant_tab, ssize_t size_path, size_t i)
{
	size_t j;

	j = 0;
	while ((ssize_t)j <= size_path + 1)
	{
		if (ant_tab[j] == -1)
		{
			if (i == 0)
				ant_tab[j] += s->max_path - 1;
			else
				ant_tab[j] += s->max_path % i;
			return ;
		}
		if (i == 0)
			ant_tab[j] += s->max_path - 1;
		else
			ant_tab[j] += s->max_path % i;
		j++;
	}
}


void		throw_ant(t_lem_in *s, ssize_t *final)
{
	ssize_t	***ant_tab;
	size_t	i;

	ant_tab = init_ant_tab(s, final);
	i = 0;
	while (i < s->max_path - 1)
	{
		act_ant = calcul_ant(s, final, s->ant, i);
		s->ant -= act_ant;
		fill_tab(ant_tab, final[i], act_ant, i, nb_path);
		i++;
	}
	return (ant_tab);
}