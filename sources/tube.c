/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:06:54 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/11 15:07:12 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_tube(t_tube *to_delete)
{
	free(to_delete->str);
	free(to_delete);
}

void	tube_clear(t_tube *to_clear)
{
	t_tube *tmp;

	while (to_clear != NULL)
	{
		tmp = to_clear->t_next;
		free_tube(to_clear);
		to_clear = tmp;
	}
}

void	print_tube(t_tube *tube, char *message)
{
	size_t	nb_tube;

	nb_tube = 0;
	ft_printf("[green]%s[a_bold]\n", message);
	while (tube != NULL)
	{
		ft_printf("%s\n", tube->str);
		tube = tube->t_next;
		nb_tube++;
	}
	ft_printf("Number of tubes = %zd\n[a_reset]", nb_tube);
}

void	init_tube(t_tube *new, char *t_str)
{
	new->str = t_str;
	new->t_next = NULL;
}

t_tube	*create_tube(char *t_str)
{
	t_tube *new;

	if (!(new = (t_tube*)malloc(sizeof(t_tube))))
		return (NULL);
	init_tube(new, t_str);
	return (new);
}

void	tube_push_back(t_tube *src, t_tube *to_add)
{
	if (src == NULL)
		src = to_add;
	else
	{
		while (src->t_next != NULL)
			src = src->t_next;
		src->t_next = to_add;
	}
}

uint_fast8_t	is_tube(char *line, t_lem_in *s)
{
	size_t i;
	size_t mid;
	t_room *tmp1;
	t_room *tmp2;

	if (line[0] == '#')
		return (!ft_strcmp(line, "##start")
			|| !ft_strcmp(line, "##end") ? 0 : 1);
	if (!line[0] || line[0] == 'L' || line[0] == ' ' || line[0] == '-')
		return (0);
	i = 1;
	while (line[i] && line[i] != ' ' && line[i] != '-')
		i++;
	if (line[i] != '-' || !(tmp1 = get_room(line, s)))
		return (0);
	i++;
	mid = i;
	while (line[i] && line[i] != ' ' && line[i] != '-')
		i++;
	if (mid == i || line[i] != '\0' || !(tmp2 = get_room(line + mid, s)))
		return (0);
	link_push_back(tmp1, create_link(tmp2));
	link_push_back(tmp2, create_link(tmp1));
	return (1);
}

void	read_tube(t_lem_in *s, char *line)
{
	if (!s->start || !s->end || !line || !is_tube(line, s))
	{
		ft_printf("error line : |%s|\n", line);
		free(line);
		exit_failure(s, 1, "Not enouth info before 1rst tube OR invalid/no 1rst tube");
	}
	s->tube = create_tube(line);
	while (get_next_line(0, &line) > 0)
	{
		if (is_tube(line, s) == 0)
			return (free(line));
		tube_push_back(s->tube, create_tube(line));
	}
}