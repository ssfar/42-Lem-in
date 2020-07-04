/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_room_link.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:45:56 by vrobin            #+#    #+#             */
/*   Updated: 2020/03/10 20:09:50 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "les_mines.h"

char	is_room_name_format(char *line, size_t *i)
{
	size_t	j;

	j = *i;
	if (line[j] == '#' || line[j] == 'L' || line[j] == ' ' || line[j] == '-')
		return (0);
	while (line[j] != ' ' && line[j] != '-' && line[j] > 32 && line[j] < 127)
		j++;
	if (j == *i)
		return (0);
	*i = j;
	return (1);
}

char	is_link2(t_lem_in *s, char *line, t_room *room1)
{
	t_room	*room2;
	size_t	i;

	i = 0;
	if (!is_room_name_format(line, &i) || line[i] != '\0')
		return (0);
	if (!(room2 = find_room(s, line, hash_to_int(line))))
		return (0);
	if (room1->index == room2->index)
		return (1);
	room1->nb_link++;
	room2->nb_link++;
	if (room1->nb_link == SIZE_T_MAX || room2->nb_link == SIZE_T_MAX)
		exit_failure(s, line, 0, 0);
	return (1);
}

char	is_link(t_lem_in *s, char *line)
{
	size_t	i;
	t_room	*room1;

	if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		return (0);
	i = 0;
	if (line[0] != '#')
	{
		if (!is_room_name_format(line, &i) || line[i] != '-')
			return (0);
		line[i] = '\0';
		if (!(room1 = find_room(s, line, hash_to_int(line))))
			return (0);
		if (!is_link2(s, &line[i + 1], room1))
			return (0);
	}
	info_push_back(s, create_info(s, line));
	return (1);
}

char	is_room(char *line)
{
	size_t	i;

	i = 0;
	if (is_room_name_format(line, &i) && line[i] == ' '
		&& is_room2(&line[i + 1]))
	{
		line[i] = '\0';
		return (1);
	}
	return (0);
}

char	is_room2(char *line)
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
