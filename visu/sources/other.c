/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:15:05 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/10 14:55:02 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

char	find_link(t_visu *v, char *str, size_t *index)
{
	*index = 0;
	while (*index < v->nb_room && ft_strcmp(str, v->room[*index].name))
		(*index)++;
	return (*index == v->nb_room ? 0 : 1);
}

void	verify_ant_path_connexion(t_visu *v, t_room **path, size_t actual_room)
{
	size_t	j;

	if (path[actual_room] == path[actual_room + 1])
		invalid_map(v, NULL);
	j = 0;
	while (j < v->nb_valid_link)
	{
		if ((v->link[j].a == path[actual_room]
		|| v->link[j].a == path[actual_room + 1])
		&& (v->link[j].b == path[actual_room]
		|| v->link[j].b == path[actual_room + 1]))
			break ;
		j++;
	}
	if (j == v->nb_valid_link)
		invalid_map(v, NULL);
}

void	verify_ant_path(t_visu *v)
{
	size_t	i;
	size_t	actual_room;

	i = 0;
	while (i < v->ant_nb)
	{
		v->ant[i].goal = 0;
		actual_room = 0;
		while (actual_room < v->ant[i].nb_move - 1)
		{
			verify_ant_path_connexion(v, v->ant[i].path, actual_room);
			actual_room++;
		}
		if (v->ant[i].path[actual_room] != &v->room[v->end_index])
			invalid_map(v, NULL);
		i++;
	}
}

void	set_tip(t_visu *v, char start)
{
	if (start)
	{
		v->start_found = 1;
		v->start_index = v->nb_room;
	}
	else
	{
		v->end_found = 1;
		v->end_index = v->nb_room;
	}
}

void	display_room(t_visu *v)
{
	size_t	i;
	ssize_t	w;
	ssize_t	h;

	w = v->rect.w * 2;
	h = v->rect.h * 2;
	i = 0;
	SDL_SetRenderDrawColor(v->renderer, 45, 226, 230, 255);
	while (i < v->nb_room)
	{
		v->rect.x = v->room[i].x * w + v->cam_x;
		v->rect.y = v->room[i].y * h + v->cam_y;
		SDL_RenderDrawRect(v->renderer, &v->rect);
		display_name(v, v->room[i].name);
		i++;
	}
	SDL_SetRenderDrawColor(v->renderer, 251, 126, 20, 255);
	v->rect.x = v->room[v->start_index].x * w + v->cam_x;
	v->rect.y = v->room[v->start_index].y * h + v->cam_y;
	SDL_RenderDrawRect(v->renderer, &v->rect);
	SDL_SetRenderDrawColor(v->renderer, 57, 255, 20, 255);
	v->rect.x = v->room[v->end_index].x * w + v->cam_x;
	v->rect.y = v->room[v->end_index].y * h + v->cam_y;
	SDL_RenderDrawRect(v->renderer, &v->rect);
}
