/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:40:16 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/20 17:47:27 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

void			init_map(t_lem_in *s)
{
	size_t	i;

	i = 0;
	while (i < MAP_SIZE)
	{
		s->map[i] = NULL;
		i++;
	}
}

void	clear_map_room(t_lem_in *s)
{
	t_table	*tmp;
	t_table	*tmp1;
	size_t	i;

	i = 0;
	while (i < MAP_SIZE)
	{
		tmp = s->map[i];
		while (tmp)
		{
			tmp1 = tmp->t_next;
			free(tmp->room);
			free(tmp);
			tmp = tmp1;
		}
		i++;
	}
}

void	clear_map(t_lem_in *s)
{
	size_t	i;
	t_table	*tmp;
	t_table	*tmp1;

	i = 0;
	while (i < MAP_SIZE)
	{
		tmp = s->map[i];
		while (tmp)
		{
			tmp1 = tmp->t_next;
			free(tmp);
			tmp = tmp1;
		}
		i++;
	}
}