/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:14:48 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/09 21:07:29 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	display_link(t_visu *v)
{
	size_t	i;
	ssize_t	x;
	ssize_t	y;
	ssize_t	w;
	ssize_t	h;

	x = v->cam_x + v->rect.w / 2;
	y = v->cam_y + v->rect.h / 2;
	w = v->rect.w * 2;
	h = v->rect.h * 2;
	i = 0;
	SDL_SetRenderDrawColor(v->renderer, 246, 1, 157, 255);
	while (i < v->nb_valid_link)
	{
		SDL_RenderDrawLine(v->renderer, v->link[i].a->x * w + x,
			v->link[i].a->y * h + y, v->link[i].b->x * w + x,
				v->link[i].b->y * h + y);
		i++;
	}
}

void	display_counter(t_visu *v)
{
	size_t		i;
	char		*str;

	i = count_arrived_ant(v);
	if (i == v->ant_nb)
		v->all_ant_arrived = 1;
	v->text_rect.w = (uintlen(i) + uintlen(v->ant_nb) + 3) * v->zoom;
	v->text_rect.x = v->room[v->end_index].x * v->rect.w * 2
		+ (v->rect.w - v->text_rect.w) / 2 + v->cam_x;
	v->text_rect.y = v->room[v->end_index].y * v->rect.h * 2 + v->rect.h
		+ v->cam_y;
	str = strjoin_free(strjoin_free(utoa(i), " / ", 1), utoa(v->ant_nb), 3);
	if (!(v->surface = TTF_RenderText_Solid(v->font, str, v->text_color)))
	{
		free(str);
		sdl_exit_fail(v, "RenderText()", &TTF_GetError);
	}
	free(str);
	surface_to_texture(v, &v->text_rect);
}

void	display_name(t_visu *v, char *str)
{
	v->text_rect.h = 4 * v->zoom;
	v->text_rect.w = ft_strlen(str) * (v->zoom + 4);
	v->text_rect.y = v->rect.y - v->text_rect.h - 5;
	v->text_rect.x = v->rect.x + (v->rect.w - v->text_rect.w) / 2;
	if (!(v->surface = TTF_RenderText_Shaded(v->font, str, v->text_color,
		v->background_color)))
		sdl_exit_fail(v, "RenderText()", &TTF_GetError);
	surface_to_texture(v, &v->text_rect);
}

void	display_ant(t_visu *v)
{
	size_t	i;
	t_ant	*a;
	ssize_t	x;
	ssize_t	y;

	i = 0;
	x = v->cam_x + (v->rect.w - v->ant_rect.w) / 2;
	y = v->cam_y + (v->rect.h - v->ant_rect.h) / 2;
	while (i < v->ant_nb)
	{
		a = &v->ant[i];
		if (a->starting_turn <= v->turn)
		{
			if (a->goal < a->nb_move && a->goal < v->turn - a->starting_turn)
				v->ant[i].goal++;
			find_ant_pos(v, a, x, y);
		}
		else
		{
			v->ant_rect.x = v->room[v->start_index].x * v->rect.w * 2 + x;
			v->ant_rect.y = v->room[v->start_index].y * v->rect.h * 2 + y;
		}
		SDL_RenderFillRect(v->renderer, &v->ant_rect);
		i++;
	}
}

void	display_turn(t_visu *v)
{
	char		*str;
	SDL_Rect	name_rect;

	name_rect.h = 50;
	name_rect.w = (5 + uintlen(v->turn) * 90);
	name_rect.x = 30;
	name_rect.y = 1200;
	str = strjoin_free("Turn ", utoa(v->turn), 2);
	if (!(v->surface = TTF_RenderText_Solid(v->font, str, v->text_color)))
	{
		free(str);
		sdl_exit_fail(v, "RenderText()", &TTF_GetError);
	}
	free(str);
	surface_to_texture(v, &name_rect);
}
