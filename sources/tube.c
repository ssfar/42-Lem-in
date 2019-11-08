/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:06:54 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/08 16:50:11 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_tube(t_tube *to_delete)
{
	free(to_delete->link);
	to_delete->next = NULL;
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
	ft_printf("%s", message);
	while (tube != NULL)
	{
		ft_printf("%s", tube->link);
		tube = tube->next;
	}
}

t_tube	create_tube(char *t_link)
{
	t_tube result;

	result.link = t_link;
	result.next = NULL;
	return (result);
}

t_tube *initialize_tube(char *t_link)
{
	t_tube *result;

	if (!(result = (t_tube*)malloc(sizeof(t_tube))))
		return (NULL);
	*result = create_tube(t_link);
	return (result);
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