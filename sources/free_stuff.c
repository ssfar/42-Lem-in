/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:32:49 by vrobin            #+#    #+#             */
/*   Updated: 2020/03/10 18:42:49 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

void	free_info(t_lem_in *s)
{
	while (s->info)
	{
		s->i_curr = s->info;
		s->info = s->info->i_next;
		free(s->i_curr->str);
		free(s->i_curr);
	}
}

void	free_room(t_room *room, char mode)
{
	if (mode)
	{
		free(room->link);
		free(room->prio);
	}
	else
		free(room);
}

void	free_hash_map(t_lem_in *s, char mode)
{
	size_t		i;
	t_hashmap	*tmp;
	t_hashmap	*tmp2;

	i = 0;
	while (i < MAP_SIZE)
	{
		tmp = s->hmap[i];
		while (tmp)
		{
			free_room(tmp->room, mode);
			tmp2 = tmp;
			tmp = tmp->collision_next;
			free(tmp2);
		}
		i++;
	}
}

void	free_struct(t_lem_in *s, char mode)
{
	free_info(s);
	free_hash_map(s, mode);
	free(s->room_tab);
	free(s->on_q);
	free(s->queu);
}
