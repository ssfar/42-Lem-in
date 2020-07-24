/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <samisfar.dev@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:56:03 by ssfar             #+#    #+#             */
/*   Updated: 2020/07/24 11:13:41 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	init_ant_struct(t_visu *v, char *line)
{
	size_t	i;

	if (!(v->ant = malloc(sizeof(t_ant) * v->ant_nb)))
		exit_fail(v, "Malloc error", line);
	i = 0;
	while (i < v->ant_nb)
	{
		v->ant[i].goal = 0;
		v->ant[i].nb_move = 0;
		v->ant[i].moved = 0;
		v->ant[i].path = NULL;
		i++;
	}
}

void	init(t_visu *v)
{
	init_struct(v);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		sdl_exit_fail(v, "Init()", &SDL_GetError);
	if (!(v->window = SDL_CreateWindow("Lem_in Visualiseur",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINW, WINH, 0)))
		sdl_exit_fail(v, "CreateWindow()", &SDL_GetError);
	if (!(v->renderer = SDL_CreateRenderer(v->window, -1,
		SDL_RENDERER_SOFTWARE)))
		sdl_exit_fail(v, "CreateRenderer()", &SDL_GetError);
	if (TTF_Init() < 0)
		sdl_exit_fail(v, "Init()", &TTF_GetError);
	if (!(v->font = TTF_OpenFont("visualiser/fonts/Herculanum.ttf", 150))
		&& !(v->font = TTF_OpenFont("fonts/Herculanum.ttf", 150)))
		sdl_exit_fail(v, "OpenFont()", &TTF_GetError);
}

void	init_loop(t_visu *v)
{
	v->cam_x = 0;
	v->cam_y = 0;
	v->zoom = 2;
	v->prev_time_a = 0;
	v->prev_time_b = 0;
	v->text_color.r = 255;
	v->text_color.g = 255;
	v->text_color.b = 255;
	v->text_color.a = 255;
	v->background_color.r = 0;
	v->background_color.g = 0;
	v->background_color.b = 0;
	v->background_color.a = 255;
	v->rect.w = 10 * v->zoom;
	v->rect.h = 10 * v->zoom;
	v->ant_rect.w = 3 * v->zoom;
	v->ant_rect.h = 3 * v->zoom;
	v->all_ant_arrived = 0;
	v->prev_time_a = 0;
	v->prev_time_b = 0;
}

void	init_struct(t_visu *v)
{
	v->window = NULL;
	v->renderer = NULL;
	v->font = NULL;
	v->texture = NULL;
	v->surface = NULL;
	v->info = NULL;
	v->room = NULL;
	v->link = NULL;
	v->ant = NULL;
	v->cam_x = 0;
	v->cam_y = 0;
	v->zoom = 2;
	v->text_color.r = 255;
	v->text_color.g = 255;
	v->text_color.b = 255;
	v->text_color.a = 255;
	v->rect.w = 10 * v->zoom;
	v->rect.h = 10 * v->zoom;
	v->ant_rect.w = 3 * v->zoom;
	v->ant_rect.h = 3 * v->zoom;
	v->all_ant_arrived = 0;
}
