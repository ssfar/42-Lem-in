/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:53:42 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/09 17:08:19 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	free_all_struct(t_visu *v)
{
	size_t	i;

	free_info(v);
	if (v->room)
	{
		i = 0;
		while (i < v->nb_room)
		{
			free(v->room[i].name);
			i++;
		}
		free(v->room);
		free(v->link);
		i = 0;
		if (v->ant)
			while (i < v->ant_nb)
			{
				free(v->ant[i].path);
				i++;
			}
		free(v->ant);
	}
}

void	free_info(t_visu *v)
{
	t_info	*tmp;

	while (v->info != NULL)
	{
		tmp = v->info;
		v->info = v->info->next;
		free(tmp->str);
		free(tmp);
	}
}
