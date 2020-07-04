/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:59:19 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/10 14:53:36 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	read_tip(t_visu *v, char start, char *line)
{
	free(line);
	if ((start && v->start_found) || (!start && v->end_found))
		return (invalid_map(v, NULL));
	while (get_next_line(0, &line) > 0)
	{
		if (*line == '#')
		{
			if (!ft_strcmp("##start", line) || !ft_strcmp("##end", line))
				return (invalid_map(v, line));
			free(line);
		}
		else if (is_room(line))
		{
			add_info(v, line);
			set_tip(v, start);
			v->nb_room++;
			return ;
		}
		else
			invalid_map(v, line);
	}
	invalid_map(v, NULL);
}

char	*read_room(t_visu *v)
{
	char	*line;

	v->nb_room = 0;
	v->start_found = 0;
	v->end_found = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (is_room(line))
		{
			add_info(v, line);
			v->nb_room++;
		}
		else if (*line == '#')
		{
			if (!ft_strcmp("##start", line))
				read_tip(v, 1, line);
			else if (!ft_strcmp("##end", line))
				read_tip(v, 0, line);
			else
				free(line);
		}
		else
			return (line);
	}
	return (NULL);
}

char	*read_link(t_visu *v, char *line)
{
	v->nb_total_link = 0;
	if (v->nb_room < 2 || !v->start_found || !v->end_found || !line
		|| !is_link(v, line))
		invalid_map(v, line);
	store_room(v);
	while (get_next_line(0, &line) > 0)
	{
		if (!is_link(v, line) && *line != '#')
			return (line);
		else if (!ft_strcmp("##start", line) || !ft_strcmp("##end", line))
			invalid_map(v, line);
		else if (*line == '#')
			free(line);
	}
	return (NULL);
}

void	read_ant_nb(t_visu *v)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (*line != '0' && str_is_numeric_no_symbol(line))
		{
			v->ant_nb = atou(line);
			return (free(line));
		}
		else if (*line == '#' && ft_strcmp("##start", line)
			&& ft_strcmp("##end", line))
			free(line);
		else
			return (invalid_map(v, line));
	}
	return (invalid_map(v, NULL));
}

void	read_ant_movement(t_visu *v, char *line)
{
	v->turn = 1;
	if (v->nb_total_link == 0)
		invalid_map(v, line);
	store_link(v, line);
	if (v->nb_valid_link == 0)
		invalid_map(v, line);
	free_info(v);
	if (line && *line == 0)
	{
		free(line);
		init_ant_struct(v, line);
		while (get_next_line(0, &line) > 0)
			set_ant_movement(v, line);
		store_ant_movement(v);
		verify_ant_path(v);
		v->turn = 0;
	}
	else
		free(line);
}
