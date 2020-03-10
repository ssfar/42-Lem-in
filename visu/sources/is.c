/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:05:20 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/09 17:08:30 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

char	is_room(char *line)
{
	size_t	i;

	i = 0;
	if (!is_room_name_format(line, &i) || line[i] != ' '
		|| !is_room2(&line[i + 1]))
		return (0);
	line[i] = '\0';
	return (1);
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

char	is_link(t_visu *v, char *line)
{
	size_t	i;

	i = 0;
	if (!is_room_name_format(line, &i) || line[i] != '-')
		return (0);
	line[i] = '\0';
	i++;
	if (!is_room_name_format(line, &i) || line[i])
		return (0);
	add_info(v, line);
	v->nb_total_link++;
	return (1);
}
