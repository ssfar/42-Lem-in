/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:40:16 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/19 18:15:32 by ssfar            ###   ########.fr       */
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
	size_t	i;

	i = 0;
	while (i < s->nb_room)
	{
		while (s->map[i] != NULL)
		{
			tmp = s->map[i];
			free(tmp->room);
			free(tmp);
			s->map[i] = s->map[i]->t_next;
		}
		i++;
	}
}

void	clear_map(t_lem_in *s)
{
	size_t	i;
	t_table	*tmp;

	i = 0;
	while (i < s->nb_room)
	{
		tmp = s->map[i];
		while (tmp != NULL)
		{
			tmp = s->map[i]->t_next;
			free(s->map[i]);
		}
		i++;
	} 
}