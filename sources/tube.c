/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:06:54 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/09 17:24:53 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_tube(t_tube *to_delete)
{
	free(to_delete->link);
	free(to_delete);
}

void	tube_clear(t_tube *to_clear)
{
	t_tube *tmp;

	while (to_clear != NULL)
	{
		tmp = to_clear->next;
		free_tube(to_clear);
		to_clear = tmp;
	}
}

void	print_tube(t_tube *tube, char *message)
{
	ft_printf("%s\n", message);
	while (tube != NULL)
	{
		ft_printf("%s\n", tube->link);
		tube = tube->next;
	}
}

void	init_tube(t_tube *new, char *t_link)
{
	new->link = t_link;
	new->next = NULL;
}

t_tube	*create_tube(char *t_link)
{
	t_tube *new;

	if (!(new = (t_tube*)malloc(sizeof(t_tube))))
		return (NULL);
	init_tube(new, t_link);
	return (new);
}

void	tube_push_back(t_tube *src, t_tube *to_add)
{
	if (src == NULL)
		src = to_add;
	else
	{
		while (src->next != NULL)
			src = src->next;
		src->next = to_add;
	}
}