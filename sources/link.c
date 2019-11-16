/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:40:03 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/16 14:38:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

uint_fast8_t	is_link2(t_lem_in *s, char *line)
{
	t_room	*tmp;
	size_t	i;

	if (!line[0])
		return (0);
	i = 1;
	while (line[i] && line[i] != ' ' && line[i] != '-')
		i++;
	if (line[i] != '\0')
		return (0);
	if (!(tmp = find_room(s, line, hash_to_int(line))))
		return (0);
	tmp->nb_link++;
	return (1);
}

uint_fast8_t	is_link(t_lem_in *s, char *line)
{
	size_t	i;
	t_room	*tmp;

	if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		return (0);
	if (line[0] != '#')
	{
		if (!line[0] || line[0] == 'L' || line[0] == ' ' || line[0] == '-')
			return (0);
		i = 1;
		while (line[i] && line[i] != ' ' && line[i] != '-')
			i++;
		if (line[i] != '-')
			return (0);
		line[i] = '\0';
		if (!(tmp = find_room(s, line, hash_to_int(line))))
			return (0);
		tmp->nb_link++;
		if (!is_link2(s, &line[i + 1]))
			return (0);
	}
	info_push_back(s, create_info(s, line));
	return (1);
}

void			read_link(t_lem_in *s, char *line)
{
	if (!line || s->start == -1 || s->end == -1 || is_link(s, line) == 0)
	{
		free(line);
		exit_failure(s, 1, "Not enought viable info", 1);
	}
	s->pipe = s->i_current;
	while (get_next_line(0, &line))
	{
		if (is_link(s, line) == 0)
		{
			free(line);
			return ;
		}
	}
}