/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 18:45:47 by vrobin            #+#    #+#             */
/*   Updated: 2019/12/28 19:20:47 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

size_t	**init_ant_tab(t_lem_in *s, ssize_t *final)
{
	size_t **ant_tab;
	size_t i;
	ssize_t j;

	i = 0;
	j = 0;
	if (!(ant_tab = malloc(sizeof(size_t*) * s->max_path + 1)))
		exit_failure(s, 123, "malloc ant_tab", 0);
	while (i < s->max_path)
	{
		j = 0;
		if (!(ant_tab[i] = malloc(sizeof(size_t) * s->way[final[i]].last_node + 1)))
			exit_failure(s, 123, "malloc ant_tab", 0);
		while (j <= s->way[final[i]].last_node)
		{
			ant_tab[i][j] = 0;
			j++;
		}
		i++;
	}
	return (ant_tab);
}

void	print_ant_tab(t_lem_in *s, size_t **ant_tab, ssize_t *final)
{
	size_t	i;
	ssize_t	j;

	i = 0;
	while (i < s->max_path)
	{
		j = 0;
		ft_printf("Path [%d]\n", i);
		while (j <= s->way[final[i]].last_node)
		{
			ft_printf("%d\n", ant_tab[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

size_t		**throw_ant(t_lem_in *s, ssize_t *final)
{
	size_t **ant_tab;
	
	ant_tab = init_ant_tab(s, final);
	while (ant_tab[s->max_path][s->way[final[s->max_path]].last_node] != s->ant)
	{
		// calculate nb ant to throw
		// add 1 if more than 1 path, 2 if more than 2, 3 etc..
		// print_turn
	}
	return (ant_tab);
}