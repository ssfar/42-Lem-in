/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:40:03 by vrobin            #+#    #+#             */
/*   Updated: 2019/11/26 13:44:18 by vrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "V3_lem_in.h"

uint_fast8_t	is_link2(t_lem_in *s, char *line, t_room *tmp1)
{
	t_room	*tmp2;
	size_t	i;

	if (!line[0])
		return (0);
	i = 1;
	while (line[i] && line[i] != ' ' && line[i] != '-')
		i++;
	if (line[i] != '\0')
		return (0);
	if (!(tmp2 = find_room(s, line, hash_to_int(line))))
		return (0);
	if (tmp1->index == tmp2->index)
		return (1);
	tmp1->nb_link++;
	tmp2->nb_link++;
	return (1);
}

uint_fast8_t	is_link(t_lem_in *s, char *line)
{
	size_t	i;
	t_room	*tmp1;

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
		if (!(tmp1 = find_room(s, line, hash_to_int(line))))
			return (0);
		if (!is_link2(s, &line[i + 1], tmp1))
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