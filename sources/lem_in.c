/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:57:42 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/08 17:58:30 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	exit_failure(t_lem_in *l, size_t id)
{
	room_clear(l->first);
	tube_clear(l->tube);
	ft_printf("ERROR");
	exit(EXIT_FAILURE);
}

// connexion possible ici si les deux room sont trouve

void	link_room(t_lem_in *l)
{
	
}

uint_fast8_t	find_room(char *line, size_t h, size_t i, t_room *first)
{
	while (first->next != NULL)
	{
		if (ft_strncmp(first->name, line + h, i) == 0)
			return (1);
		first = first->next;
	}
	return (0);
}

uint_fast8_t	is_tube(char *line, t_lem_in *l)
{
	size_t i;

	i = 0;
	if (line[0] == '#')
		return (1);
	if (line[0] == 'L' || line[i] == ' ')
		return (0);
	while (line[i] && line[i] != '-')
		i++;
	if (line[i] != '-')
		return (0);
	if (!find_room(line, 0, i, l->first))
		return (0);
	i++;
	if (line[i] == '#' || line[i] == 'L' || line[i] == ' ')
		return (0);
	while (line[i] && line[i] != '-' && line[i] != ' ')
		i++;
	if (!find_room(line, i, 0, l->first))
		return (0);
	if (line[i] == '\0')
	{
		link_room(l);
		return (1);
	}
	return (0);
}

uint_fast16_t	read_tube(t_lem_in *l)
{
	char *line;
	
	while (get_next_line(0, &line) > 0)
	{
		if (is_tube(line, l) == 0)
			return (0);
		else if (line[0] != '#')
		{
			free(line);
			return (0);
		}
		l->tube->link = line;
	}
	return (1);
	
}

uint_fast8_t	is_room2(char *line, size_t	i)
{
	if (i != 0 && line[i++] == ' ')
	{
		if (line[i] == '-')
			i++;
		if (ft_isdigit(line[i++]))
		{
			while (ft_isdigit(line[i]))
				i++;
			if (line[i++] == ' ')
			{
				if (line[i] == '-')
					i++;
				if (ft_isdigit(line[i++]))
				{
					while (ft_isdigit(line[i]))
						i++;
					return (line[i] ? 0 : 1);
				}
			}
		}
	}
	return (0);
}

uint_fast8_t	is_room(char *line)
{
	size_t	i;

	if (!line || *line == 'L' || *line == '#')
		return (0);
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	return (is_room2(line, i));
}

void	init_struct(t_lem_in *l)
{
	l->start = NULL;
	l->end = NULL;
	l->first = NULL;
	l->current = NULL;
}

void	get_tip(s_room **tip)
{
	char	*line;

	if (*tip || get_next_line(0, &line) < 1 || *line == '#')
	{
		free(line);
		exit_failure(l, 1);
	}
	room_push_back(&l, initialize_room(line));
	*tip = l->current;
}

int	main(void)
{
	char		*line;
	t_lem_in	l; 

	l.ant = get_ant_nb();
	while (get_next_line(0, &line) > 0)
	{
		if (is_room(line))
			room_push_back(&l, initialize_room(line));
		else if (ft_strcmp("#", line))
		{
			room_push_back(&l, initialize_room(line));
			if (ft_strcmp("##start", line))
				get_tip(l->start);	
			else if (ft_strcmp("##end", line))
				get_tip(l->end);
		}
	}
	if (read_tube(&l) == 0)
		exit_failure(&l, 2);
	
	// check infos
	// room_push_back(current, initialize_room(line));
}

ssize_t	get_ant_nb(void)
{
	char	*line;
	ssize_t	ant;
	
	line = NULL;
	if (get_next_line(0, &line) <= 0 || !line)
		exit(EXIT_FAILURE);
	if (str_is_numeric(line) != 1 || (ant = ft_atoi(line)) < 0)
	{
		free(line);	
		exit(EXIT_FAILURE);
	}
	free(line);	
	return (ant);
}