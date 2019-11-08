/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:33:38 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/08 18:05:27 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_room(t_room *to_delete)
{
	free(to_delete->name);
	free(to_delete);
}

void	room_clear(t_room *to_clear)
{
	t_room	*tmp;

	while (to_clear != NULL)
	{
		tmp = to_clear->next;
		free_room(to_clear);
		to_clear = tmp;
	}
}

void	print_room(t_room *room, char *message)
{
	ft_printf("%s", message);
	while (room != NULL)
	{
		ft_printf("%s", room->name);
		room = room->next;
	}
}

t_room	create_room(char *r_name)
{
	t_room	result;

	result.name = r_name;
	result.next = NULL;
	result.connexion = NULL;
	return (result);
}

t_room	*initialize_room(char *r_name)
{
	t_room	*result;

	if (!(result = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	*result = create_room(r_name);
	return (result);
}

void	room_push_back(t_lem_in *l, t_room *to_add)
{
	if (l->first == NULL)
	{
		l->first = to_add;
		l->current = to_add;
	}
	else
	{
		while (l->current->next != NULL)
			l->current = l->current->next;
		l->current->next = to_add;
		l->current = l->current->next;
	}
}