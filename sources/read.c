/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:43:29 by vrobin            #+#    #+#             */
/*   Updated: 2020/03/10 18:45:41 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

void	read_link(t_lem_in *s, char *line)
{
	if (!line || s->start == -1 || s->end == -1 || is_link(s, line) == 0)
		exit_failure(s, line, 0, 1);
	s->i_pipe = s->i_curr;
	while (get_next_line(0, &line) > 0)
	{
		if (is_link(s, line) == 0)
		{
			free(line);
			return ;
		}
	}
}

void	read_ant_nb(t_lem_in *s)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (*line == '#')
		{
			info_push_back(s, create_info(s, line));
			if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
				exit_failure(s, NULL, 0, 1);
		}
		else if (str_is_numeric_no_symbol(line) && *line != '0')
		{
			s->nb_ant = atou(line);
			free(line);
			if (s->nb_ant == 0)
				exit_failure(s, NULL, 0, 0);
			return ;
		}
		else
			exit_failure(s, line, 0, 1);
	}
	exit_failure(s, NULL, 0, 1);
}

void	read_tip(t_lem_in *s, ssize_t *tip)
{
	char	*line;

	if (*tip != -1)
		exit_failure(s, NULL, 0, 1);
	while (get_next_line(0, &line) > 0)
	{
		if (*line == '#')
		{
			info_push_back(s, create_info(s, line));
			if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
				exit_failure(s, NULL, 0, 1);
		}
		else if (is_room(line))
		{
			*tip = s->nb_room;
			add_room(s, line);
			break ;
		}
		else
			exit_failure(s, line, 0, 1);
	}
}

char	*read_room(t_lem_in *s)
{
	char	*line;

	s->nb_room = 0;
	s->start = -1;
	s->end = -1;
	while (get_next_line(0, &line) > 0)
	{
		if (*line == '#')
		{
			info_push_back(s, create_info(s, line));
			if (ft_strcmp("##start", line) == 0)
				read_tip(s, &s->start);
			else if (ft_strcmp("##end", line) == 0)
				read_tip(s, &s->end);
		}
		else if (is_room(line))
			add_room(s, line);
		else
			return (line);
	}
	return (NULL);
}
