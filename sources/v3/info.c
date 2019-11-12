/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:17:02 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/12 18:05:58 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

void	free_info(t_info *to_free)
{
	free(to_free->str);
	free(to_free);
}

void	clear_info(t_info *to_clear)
{
	t_info *tmp;

	while (to_clear != NULL)
	{
		tmp = to_clear->next;
		free_info(to_clear);
		to_clear = tmp;
	}
}

void	info_push_back(t_lem_in *s, t_info *to_add)
{
	if (s->info == NULL)
	{
		s->info = to_add;
		s->i_current = to_add;
	}
	else
	{
		s->i_current->i_next = to_add;
		s->i_current = s->i_current->i_next;
	}
}

void	init_info(t_info *new, char *str)
{
	new->str = str;
	new->i_next = NULL;
}

t_info	*create_info(char *str)
{
	t_info	*new;

	if (!(new = (t_info*)malloc(sizeof(t_info))))
		return (NULL);
	init_info(new, str);
	return (new);
}