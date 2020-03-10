/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:09:32 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/09 17:06:54 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	find_ant_pos(t_visu *v, t_ant *a, ssize_t x, ssize_t y)
{
	if (a->goal == 0)
	{
		v->ant_rect.x = linear_interpolation(v->percent,
			v->room[v->start_index].x * v->rect.w * 2 + x,
				a->path[a->goal]->x * v->rect.w * 2 + x);
		v->ant_rect.y = linear_interpolation(v->percent,
			v->room[v->start_index].y * v->rect.h * 2 + y,
				a->path[a->goal]->y * v->rect.h * 2 + y);
	}
	else if (a->goal == a->nb_move)
	{
		v->ant_rect.x = a->path[a->goal - 1]->x * v->rect.w * 2 + x;
		v->ant_rect.y = a->path[a->goal - 1]->y * v->rect.h * 2 + y;
	}
	else
	{
		v->ant_rect.x = linear_interpolation(v->percent,
			a->path[a->goal - 1]->x * v->rect.w * 2 + x,
				a->path[a->goal]->x * v->rect.w * 2 + x);
		v->ant_rect.y = linear_interpolation(v->percent,
			a->path[a->goal - 1]->y * v->rect.h * 2 + y,
				a->path[a->goal]->y * v->rect.h * 2 + y);
	}
}

void	set_ant(t_visu *v, size_t ant_id, char *line)
{
	if (ant_id >= v->ant_nb || v->ant[ant_id].moved)
		invalid_map(v, line);
	if (v->ant[ant_id].nb_move == 0)
		v->ant[ant_id].starting_turn = v->turn;
	v->ant[ant_id].nb_move++;
	v->ant[ant_id].moved = 1;
}

void	set_ant_movement(t_visu *v, char *line)
{
	size_t	i;

	check_ant_format(v, line);
	i = 0;
	while (i < v->ant_nb)
	{
		v->ant[i].moved = 0;
		i++;
	}
	add_info(v, line);
	v->turn++;
}

size_t	count_arrived_ant(t_visu *v)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (i < v->ant_nb)
	{
		if (v->ant[i].goal == v->ant[i].nb_move
			|| (v->percent == 1 && v->ant[i].goal + 1 == v->ant[i].nb_move))
			counter++;
		i++;
	}
	return (counter);
}

void	check_ant_format(t_visu *v, char *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (line[i])
	{
		if (i != 0 && line[i] == ' ')
			i++;
		if (line[i] != 'L')
			invalid_map(v, line);
		i++;
		j = i;
		if (line[i] == '0')
			invalid_map(v, line);
		while (line[i] >= '0' && line[i] <= '9')
			i++;
		if (i == j || line[i] != '-')
			invalid_map(v, line);
		i++;
		set_ant(v, atou(&line[j]) - 1, line);
		if (!is_room_name_format(line, &i)
			|| (line[i] != '\0' && line[i] != ' '))
			invalid_map(v, line);
	}
}
