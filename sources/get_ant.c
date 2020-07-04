/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ant.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:14:01 by vrobin            #+#    #+#             */
/*   Updated: 2020/03/10 18:43:20 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

void	get_prev_ant(t_lem_in *s, ssize_t cur)
{
	if (s->room_tab[cur].prev != -1)
	{
		s->room_tab[cur].ant = s->room_tab[s->room_tab[cur].prev].ant;
		if (s->room_tab[cur].ant != 0)
		{
			if (s->run)
				ft_printf(" ");
			ft_printf("L%zu-%s", s->room_tab[cur].ant, s->room_tab[cur].name);
			s->run = 1;
		}
		return (get_prev_ant(s, s->room_tab[cur].prev));
	}
}

size_t	*get_ant2(size_t nb_ant, size_t *ant_tab, size_t size)
{
	size_t	i;

	while (nb_ant > 0)
	{
		i = 0;
		while (i < size && nb_ant > 0)
		{
			ant_tab[i]++;
			nb_ant--;
			i++;
		}
	}
	if (!ant_tab[size - 1])
	{
		free(ant_tab);
		return (NULL);
	}
	return (ant_tab);
}

void	init_ant_tab(size_t *ant_tab, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		ant_tab[i] = 0;
		i++;
	}
}

size_t	*get_ant(t_lem_in *s, size_t nb_ant, size_t *path, size_t size)
{
	size_t	ret;
	size_t	j;
	size_t	i;
	size_t	*ant_tab;

	i = 0;
	ret = 0;
	if (!(ant_tab = malloc(sizeof(size_t) * size)))
		exit_failure(s, path, 1, 0);
	init_ant_tab(ant_tab, size);
	while (i < size - 1 && nb_ant > ret && nb_ant > 0)
	{
		j = 0;
		ret = path[i + 1] - path[i];
		if (ret > nb_ant)
			ret = nb_ant;
		while (j < i + 1 && nb_ant > 0 && nb_ant > ret)
		{
			ant_tab[j] += ret;
			nb_ant -= ret;
			j++;
		}
		i++;
	}
	return (get_ant2(nb_ant, ant_tab, size));
}
