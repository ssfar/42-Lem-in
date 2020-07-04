/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:15:36 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/10 18:26:42 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	surface_to_texture(t_visu *v, SDL_Rect *rect)
{
	v->texture = SDL_CreateTextureFromSurface(v->renderer, v->surface);
	SDL_FreeSurface(v->surface);
	v->surface = NULL;
	if (!v->texture)
		sdl_exit_fail(v, "CreateTextureFromSurface()", &SDL_GetError);
	if (SDL_RenderCopy(v->renderer, v->texture, NULL, rect) < 0)
	{
		SDL_DestroyTexture(v->texture);
		sdl_exit_fail(v, "RenderCopy()", &SDL_GetError);
	}
	SDL_DestroyTexture(v->texture);
}

char	add_info(t_visu *v, char *line)
{
	if (!v->info)
	{
		if (!(v->info = malloc(sizeof(t_info))))
			exit_fail(v, "Malloc error", line);
		v->cur_info = v->info;
	}
	else
	{
		if (!(v->cur_info->next = malloc(sizeof(t_info))))
			exit_fail(v, "Malloc error", line);
		v->cur_info = v->cur_info->next;
	}
	v->cur_info->next = NULL;
	v->cur_info->str = line;
	return (1);
}

void	center_start(t_visu *v)
{
	int	x;
	int	y;

	v->rect.w = 10 * v->zoom;
	v->rect.h = 10 * v->zoom;
	v->rect.x = v->room[v->start_index].x * v->rect.w;
	v->rect.y = v->room[v->start_index].y * v->rect.h;
	x = (WINW - v->rect.w) / 2;
	y = (WINH - v->rect.h) / 2;
	v->cam_x = v->rect.x - x;
	v->cam_y = v->rect.y - y;
	if (v->rect.x < x)
		v->cam_x = x - v->rect.x;
	if (v->rect.y < y)
		v->cam_y = y - v->rect.y;
}

ssize_t	linear_interpolation(float percentage, ssize_t p1, ssize_t p2)
{
	return (percentage * (p2 - p1) + p1);
}

void	reset(t_visu *v)
{
	size_t	i;

	i = 0;
	while (i < v->ant_nb)
	{
		v->ant[i].goal = 0;
		i++;
	}
	v->turn = 0;
	v->percent = 0;
	v->all_ant_arrived = 0;
}
