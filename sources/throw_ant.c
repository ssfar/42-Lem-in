/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 18:45:47 by vrobin            #+#    #+#             */
/*   Updated: 2020/01/15 20:05:21 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

//
// void	print_ant_tab(t_lem_in *s, final, size_t *ant_tab, char *message)
// {
// 	size_t	i;
// 	ssize_t	j;

// 	ft_printf("%s\n", message);
// 	i = 0;
// 	while (i < s->max_path)
// 	{
// 		j = 0;
// 		ft_printf("Path [%d]\n", i);
// 		while (ant_tab[i][j] != -1)
// 		{
// 			ft_printf("%d\n", ant_tab[i][j]);
// 			j++;
// 		}
// 		ft_printf("\n");
// 		i++;
// 	}
// }
// //

// size_t		calcul_ant(t_lem_in *s, ssize_t *final, size_t c_ant, size_t i)
// {
// 	if (s->max_path == 1)
// 		return (s->way[final[0]].last_node + (c_ant - 1) - 1);
// 	else
// 		return ((c_ant + s->way[final[0]].last_node - 1 - s->way[final[i]].last_node) / s->max_path);
// }

size_t	print_turn(t_lem_in *s, ssize_t *ant_tab, ssize_t *final, size_t ant_arrived)
{
	size_t	i;
	size_t	act_path;

	i = 0;
	act_path = -1;
	while (i < s->ant)
	{
		if (ant_tab[i] == 0)
			break;
		if (act_path < s->max_path - 1)
				act_path++;
		else
			act_path = 0;
		if (ant_tab[i] < s->way[final[act_path]].last_node + 1)
			ft_printf("L%d-%s ", i, s->room_tab[s->way[final[act_path]].path[ant_tab[i]]].name);
		i++;
	}
	i = 0;
	ant_arrived = 0;
	while (i < s->ant)
	{
		if (act_path < s->max_path - 1)
			act_path++;
		else
			act_path = 0;
		if (ant_tab[i] == s->way[final[act_path]].last_node)
		{
			ant_tab[i] +=1;
			// ft_printf("ant %d has arrived !\n", i);
			ant_arrived++;
		}
		i++;
	}
	ft_printf("\n");
	return(ant_arrived);
}

ssize_t	*init_ant_tab(t_lem_in *s)
{
	ssize_t	*ant_tab;
	size_t	i;

	i = 0;
	if (!(ant_tab = malloc(sizeof(size_t) * s->ant)))
		exit_failure(s, 123, "malloc ant_tab", 0);
	while (i < s->ant)
	{
		ant_tab[i] = 0;
		i++;
	}
	return (ant_tab);
}

void		throw_ant(t_lem_in *s, ssize_t *final)
{
	size_t	i;
	ssize_t	*ant_tab;
	size_t	act_path;
	size_t	ant_send;
	size_t	ant_arrived;

	ant_tab = init_ant_tab(s);
	ant_send = 0;
	act_path = 0;
	ant_arrived = 0;
	i = 0;
	while (ant_tab[s->ant - 1] < s->way[final[act_path]].last_node + 1)
	{
		act_path = ant_arrived % 2;
		ant_send++;
		i = 0;
		while (i < ant_send * s->max_path)
		{
			if (act_path < s->max_path -1 && i != 0)
				act_path++;
			else
				act_path = 0;
			if (ant_tab[i] != s->way[final[act_path]].last_node)
				ant_tab[i]++;
			i++;
		}
		ant_arrived = print_turn(s, ant_tab, final, ant_arrived);
	}
}