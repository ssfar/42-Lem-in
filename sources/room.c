/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:38:07 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/14 21:22:06 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

t_room	*init_room(t_lem_in *s, t_table *tmp, char *name)
{
	if (!(tmp->room = malloc(sizeof(t_room))))
		exit_failure(s, 1, "Can't malloc tmp->room", 0);
	tmp->room->name = name;
	tmp->room->index = s->nb_room;
	tmp->room->nb_link = 0;
	tmp->room->link = NULL;
	return	(tmp->room);
}

t_room	*place_room(t_lem_in *s, char *key, size_t index)
{
	t_table	*tmp;

	if (!(s->map[index]))
	{
		if (!(s->map[index] = malloc(sizeof(t_table))))
			exit_failure(s, 1, "Can't malloc s->map[i]", 0);
		s->map[index]->t_next = NULL;
		return (init_room(s, s->map[index], key));
	}
	tmp = s->map[index];
	while (tmp->t_next)
	{
		if (ft_strcmp(key, tmp->room->name) == 0)
			exit_failure(s, 1, "Room already exist", 1);
		tmp = tmp->t_next;
	}
	if (ft_strcmp(key, tmp->room->name) == 0)
		exit_failure(s, 1, "Room already exist", 1);
	if (!(tmp->t_next = malloc(sizeof(t_table))))
		exit_failure(s, 1, "Can't malloc tmp->t_next", 0);
	tmp = tmp->t_next;
	tmp->t_next = NULL;
	return (init_room(s, tmp, key));
}

uint_fast8_t	is_room(char *line)
{
	size_t	i;

	if (!line[0] || line[0] == ' ' || line[0] == '-' || line[0] == 'L' || line[0] == '#')
		return (0);
	i = 1;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '-')
			return (0);
		i++;
	}
	if (i == 0 || line[i] != ' ')
		return (0);
	if (is_room2(&line[i + 1]))
	{
		line[i] = '\0';
		return (1);
	}
	return (0);
}

uint_fast8_t	is_room2(char *line)
{
	if (!*line)
		return (0);
	if (*line == '-')
		line++;
	if (ft_isdigit(*line))
	{
		line++;
		while (ft_isdigit(*line))
			line++;
		if (*line == ' ')
		{
			line++;
			if (*line == '-')
				line++;
			if (ft_isdigit(*line))
			{
				line++;
				while (ft_isdigit(*line))
					line++;
				if (!*line)
					return (1);
			}
		}
	}
	return (0);
}

char			*read_room(t_lem_in *s)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if ('#' == *line)
		{
			info_push_back(s, create_info(s, line));
			if (ft_strcmp("##start", line) == 0)
				read_tip(s, &s->start);
			else if (ft_strcmp("##end", line) == 0)
				read_tip(s, &s->end);
		}
		else if (is_room(line))
		{
			info_push_back(s, create_info(s, line));
			place_room(s, line, hash_to_int(line));
			s->nb_room++;
		}
		else
			return (line);
	}
	return (NULL);
}