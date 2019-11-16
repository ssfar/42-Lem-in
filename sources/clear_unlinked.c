/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_unlinked.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 13:37:30 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/16 13:37:30 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

void	clear_the_mess(t_lem_in *s, size_t i, t_table *unlinked)
{
	clean_before_unlinked(s, i, unlinked);
	free(s->room_tab);
	clean_after_unlinked(s, i, unlinked->t_next);
	free(unlinked);
	exit_failure(s, 0, "Malloc error room_tab", 0);
}

void	clean_after_unlinked(t_lem_in *s, size_t i, t_table *tmp)
{
	size_t	j;
	t_table	*tmp2;

	while (tmp)
	{
		tmp2 = tmp->t_next;
		free(tmp->room);
		free(tmp);
		tmp = tmp2;
	}
	j = i + 1;
	while (j < MAP_SIZE)
	{
		tmp = s->map[j];
		while (tmp)
		{
			tmp2 = tmp->t_next;
			free(tmp->room);
			free(tmp);
			tmp = tmp2;
		}
		j++;
	}
}

void	clean_before_unlinked(t_lem_in *s, size_t i, t_table *unliked)
{
	t_table	*tmp;
	t_table	*tmp2;
	size_t	j;

	j = 0;
	while (j < i)
	{
		tmp = s->map[j];
		while (tmp)
		{
			free(s->room_tab[tmp->room->index].link);
			tmp2 = tmp->t_next;
			free(tmp);
			tmp = tmp2;
		}
		j++;
	}
	tmp = s->map[i];
	while (tmp && tmp != unliked)
	{
		free(s->room_tab[tmp->room->index].link);
		tmp2 = tmp->t_next;
		free(tmp);
		tmp = tmp2;
	}
}