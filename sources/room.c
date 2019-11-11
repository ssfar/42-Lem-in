/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:33:38 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/11 00:18:36 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

uint_fast16_t	room_compare(const char *s1, const char *s2)
{
	size_t	i;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i] && s2[i] && s1[i] == s2[i] && s1[i] != ' ' && s1[i] != '-')
			i++;
		if ((s1[i] == '-' && s2[i] == ' ') || (s1[i] == ' ' && s2[i] == ' ')
			|| (s1[i] == '\0' && s2[i] == ' '))
			return (0);
		return (1);
	}
	return (1);
}

char	*read_room(t_lem_in *s)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (is_room(line))
		{
			if (get_room(line, s))
			{
				free(line);
				exit_failure(s, 1, "Room already exist");
			}
			room_push_back(s, create_room(line));
		}
		else if ('#' == *line)
		{
			room_push_back(s, create_room(line));
			if (ft_strcmp("##start", line) == 0)
				read_tip(&s->start, s);
			else if (ft_strcmp("##end", line) == 0)
				read_tip(&s->end, s);
		}
		else
			return (line);
	}
	return (NULL);
}

uint_fast8_t	is_room(char *line)
{
	size_t	i;

	if (*line == 'L' || *line == '#')
		return (0);
	i = 0;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '-')
			return (0);
		i++;
	}
	if (i == 0 || line[i] != ' ' || !line[++i])
		return (0);
	return (is_room2(&line[i]));
}

uint_fast8_t	is_room2(char *line)
{
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
				return (*line ? 0 : 1);
			}
		}
	}
	return (0);
}

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
		tmp = to_clear->r_next;
		free_room(to_clear);
		to_clear = tmp;
	}
}

void	print_room(t_room *room, char *message)
{
	ft_printf("[blue]%s[a_bold]\n", message);
	while (room != NULL)
	{
		ft_printf("%s\n", room->name);
		room = room->r_next;
	}
	ft_printf("[a_reset]");
}

void	init_room(t_room *new, char *r_name)
{
	new->name = r_name;
	new->r_next = NULL;
	new->link = NULL;
}

t_room	*create_room(char *r_name)
{
	t_room	*new;

	if (!(new = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	init_room(new, r_name);
	return (new);
}

void	room_push_back(t_lem_in *s, t_room *to_add)
{
	if (s->first == NULL)
	{
		s->first = to_add;
		s->current = to_add;
	}
	else
	{
		s->current->r_next = to_add;
		s->current = s->current->r_next;
	}
}

t_room	*get_room(char *line, t_lem_in *s)
{
	t_room	*tmp;

	tmp = s->first;
	while (tmp)
	{
		if (room_compare(line, tmp->name) == 0)
			return (tmp);
		tmp = tmp->r_next;
	}
	return (NULL);
}
