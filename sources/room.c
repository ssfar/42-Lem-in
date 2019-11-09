/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:33:38 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/09 11:29:44 by ssfar            ###   ########.fr       */
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

void	init_room(t_room *new, char *r_name)
{
	new.name = r_name;
	new.next = NULL;
	new.connexion = NULL;
}

t_room	*create_room(char *r_name)
{
	t_room	*new;

	if (!(new = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	init_room(new, r_name);
	return (new);
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
		l->current->next = to_add;
		l->current = l->current->next;
	}
}

t_room	*get_room(char *line, t_lem_in *l)
{
	t_room	*tmp;

	tmp = l->start;
	while (tmp)
	{
		if (ft_strccmp(line, tmp->name, ' ') == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
