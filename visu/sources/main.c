/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:55:59 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/10 18:26:03 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int		main(void)
{
	visu_lem_in();
}

void	visu_lem_in(void)
{
	t_visu	v;

	init(&v);
	read_ant_nb(&v);
	read_ant_movement(&v, read_link(&v, read_room(&v)));
	init_loop(&v);
	sdl_loop(&v);
	quit(&v);
}

void	sdl_loop(t_visu *v)
{
	char			stop;
	const uint8_t	*keystate;

	stop = 0;
	center_start(v);
	while (!stop)
	{
		v->cur_time = SDL_GetTicks();
		keystate = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&v->event))
			if (v->event.type == SDL_QUIT || keystate[SDL_SCANCODE_ESCAPE])
				stop = 1;
		handle_keystate(v, keystate);
		if (v->ant && keystate[SDL_SCANCODE_SPACE] && !v->all_ant_arrived
			&& (v->percent == 1 || v->turn == 0))
		{
			v->turn++;
			v->percent = 0;
		}
		display_map(v);
	}
}

void	display_map(t_visu *v)
{
	SDL_SetRenderDrawColor(v->renderer, 0, 0, 0, 255);
	SDL_RenderClear(v->renderer);
	v->rect.w = 10 * v->zoom;
	v->rect.h = 10 * v->zoom;
	v->ant_rect.w = 3 * v->zoom;
	v->ant_rect.h = 3 * v->zoom;
	display_link(v);
	display_room(v);
	SDL_SetRenderDrawColor(v->renderer, 250, 237, 39, 255);
	if (v->ant)
	{
		if (v->percent < 1.0 && v->turn > 0
			&& v->cur_time > v->prev_time_a + 15)
		{
			if (v->percent < 0.99)
				v->percent += 0.01;
			else
				v->percent = 1;
			v->prev_time_a = v->cur_time;
		}
		display_ant(v);
		display_counter(v);
		display_turn(v);
	}
	SDL_RenderPresent(v->renderer);
}

void	handle_keystate(t_visu *v, const uint8_t *keystate)
{
	if (keystate[SDL_SCANCODE_R])
		reset(v);
	if (v->prev_time_b + 50 < v->cur_time
		&& keystate[SDL_SCANCODE_KP_PLUS] && v->zoom < 30)
	{
		v->zoom += 1;
		v->prev_time_b = v->cur_time;
	}
	else if (v->prev_time_b + 50 < v->cur_time
		&& keystate[SDL_SCANCODE_KP_MINUS] && v->zoom > 1)
	{
		v->zoom -= 1;
		v->prev_time_b = v->cur_time;
	}
	if (keystate[SDL_SCANCODE_A])
		v->cam_x -= 10;
	else if (keystate[SDL_SCANCODE_D])
		v->cam_x += 10;
	if (keystate[SDL_SCANCODE_W])
		v->cam_y -= 10;
	else if (keystate[SDL_SCANCODE_S])
		v->cam_y += 10;
}
