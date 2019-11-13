/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:40:16 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/13 17:22:30 by vrobin           ###   ########.fr       */
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
		//s->map[i].t_next = NULL;
		i++;
	}
}

void			print_map(t_lem_in *s)
{
	int i;

	i = 0;
	while (i < MAP_SIZE)
	{
		if (s->map[i])
			ft_printf("map[%d]->index = %d, ->name = |%s|\n", i, s->map[i]->room->index, s->map[i]->room->name);
		i++;
	}
}