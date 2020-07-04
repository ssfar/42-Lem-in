/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:05:52 by vrobin            #+#    #+#             */
/*   Updated: 2020/03/10 19:07:18 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

t_room		*place_room(t_lem_in *s, char *key, size_t index)
{
	t_hashmap	*tmp;

	if (!(s->hmap[index]))
	{
		if (!(s->hmap[index] = malloc(sizeof(t_hashmap))))
			exit_failure(s, NULL, 0, 0);
		s->hmap[index]->collision_next = NULL;
		return (init_room(s, s->hmap[index], key));
	}
	tmp = s->hmap[index];
	while (tmp->collision_next)
	{
		if (ft_strcmp(key, tmp->room->name) == 0)
			exit_failure(s, NULL, 0, 1);
		tmp = tmp->collision_next;
	}
	if (ft_strcmp(key, tmp->room->name) == 0)
		exit_failure(s, NULL, 0, 1);
	if (!(tmp->collision_next = malloc(sizeof(t_hashmap))))
		exit_failure(s, NULL, 0, 0);
	tmp = tmp->collision_next;
	tmp->collision_next = NULL;
	return (init_room(s, tmp, key));
}

void		add_room(t_lem_in *s, char *line)
{
	info_push_back(s, create_info(s, line));
	place_room(s, line, hash_to_int(line));
	s->nb_room++;
	if (s->nb_room > SSIZE_T_MAX)
		exit_failure(s, NULL, 0, 0);
}

t_room		*find_room(t_lem_in *s, char *key, size_t index)
{
	t_hashmap	*tmp;

	if (!s->hmap[index])
		return (NULL);
	tmp = s->hmap[index];
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->room->name, key) == 0)
			return (tmp->room);
		tmp = tmp->collision_next;
	}
	return (NULL);
}
