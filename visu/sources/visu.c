/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:35:33 by ssfar             #+#    #+#             */
/*   Updated: 2019/12/11 17:50:03 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

// int				main(void)
// {
// 	t_visu	v;

// 	init(&v);
// 	visu(&v);
// 	quit(&v);
// }

// void			visu(t_visu *v)
// {
// 	SDL_bool	playing;
// 	SDL_bool	close;
// 	SDL_Event	event;

// 	playing = SDL_TRUE;
// 	close = SDL_FALSE;
// 	while (!close && SDL_WaitEvent(&event))
// 	{
// 		if (event.type == SDL_QUIT)
// 			close = SDL_TRUE;
// 		else if (event.type == SDL_KEYDOWN)
// 		{
// 			if (event.key.keysym.sym == SDLK_ESCAPE)
// 				close = SDL_TRUE;
// 			else if (playing && event.key.keysym.sym == SDLK_RETURN)
// 				if (!display_round(v))
// 					playing = SDL_FALSE;
// 		}
// 	}
// }

// uint_fast8_t	display_round(t_visu *v)
// {
// 	if (SDL_SetRenderDrawColor(v->renderer, 0, 0, 0, 255) < 0)
// 		sdl_exit_fail("SetRenderDrawColor()", v, &SDL_GetError);
// 	if (SDL_RenderClear(v->renderer) < 0)
// 		sdl_exit_fail("RenderClear()", v, &SDL_GetError);
// 	if (SDL_SetRenderDrawColor(v->renderer, 0, 0, 255, 255) < 0)
// 		sdl_exit_fail("SetRenderDrawColor()", v, &SDL_GetError);
// 	if (SDL_RenderDrawRect(v->renderer, &v->map.limit) < 0)
// 		sdl_exit_fail("RenderDrawRect()", v, &SDL_GetError);
// 	SDL_RenderPresent(v->renderer);
// 	return (1);
// }

// 	while (gnl_no_buff(0, &line) > 0 && *line != '=')
// 	{
// 		if (line)
// 		{
// 			if (ft_strncmp(line, "Plateau", 4) == 0)
// 				get_unit(map, ft_strchr(line, ' '), 4);
// 			else if (ft_strncmp(line, "Piece", 2) == 0)
// 			{
// 				piece->tab = free_strtab(piece->tab);
// 				get_unit(piece, ft_strchr(line, ' '), 0);
// 				ft_strdel(&line);
// 				return (1);
// 			}
// 			ft_strdel(&line);
// 		}
// 	}
// 	ft_strdel(&line);
// 	return (0);
// }

// 	if (SDL_SetRenderDrawColor(v->renderer, 0, 0, 255, 255) < 0)
// 		sdl_exit_fail("SetRenderDrawColor()", v, &SDL_GetError);
// 	if (SDL_RenderDrawRect(v->renderer, &v->map.limit) < 0)
// 		sdl_exit_fail("RenderDrawRect()", v, &SDL_GetError);

// void	init_struct(t_visu *v)
// {
// 	v->window = NULL;
// 	v->renderer = NULL;
// 	v->font = NULL;
// }

// void	init(t_visu *v)
// {
// 	init_struct(v);
// 	if (SDL_Init(SDL_INIT_VIDEO) < 0)
// 		sdl_exit_fail("Init()", v, &SDL_GetError);
// 	if (!(v->window = SDL_CreateWindow("Filler Visualiseur",
// 		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINW, WINH, 0)))
// 		sdl_exit_fail("CreateWindow()", v, &SDL_GetError);
// 	if (!(v->renderer = SDL_CreateRenderer(v->window, -1,
// 		SDL_RENDERER_SOFTWARE)))
// 		sdl_exit_fail("CreateRenderer()", v, &SDL_GetError);
// 	if (TTF_Init() < 0)
// 		sdl_exit_fail("Init()", v, &TTF_GetError);
// 	if (!(v->font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 30)))
// 		sdl_exit_fail("OpenFont()", v, &TTF_GetError);
	
// 	SDL_RenderPresent(v->renderer);
// }

// void	quit(t_visu *v)
// {
// 	if (SDL_WasInit(SDL_INIT_VIDEO))
// 	{
// 		if (TTF_WasInit())
// 		{
// 			TTF_CloseFont(v->font);
// 			SDL_DestroyTexture(v->p1.name_texture);
// 			SDL_DestroyTexture(v->p2.name_texture);
// 			TTF_Quit();
// 			free(v->p1.name);
// 			free(v->p2.name);
// 			v->prev_map = free_strtab_offset(v->prev_map, -4);
// 			v->map.tab = free_strtab_offset(v->map.tab, -4);
// 			v->piece.tab = free_strtab(v->piece.tab);
// 		}
// 		SDL_DestroyWindow(v->window);
// 		SDL_DestroyRenderer(v->renderer);
// 		SDL_Quit();
// 	}
// }

// void	exit_fail(char *str, t_visu *v)
// {
// 	if (str)
// 		ft_dprintf(2, "[red]ERROR : %s[white]\n", str);
// 	quit(v);
// 	exit(EXIT_FAILURE);
// }

// void	sdl_exit_fail(char *str, t_visu *v, const char *(*get_err)(void))
// {
// 	if (str)
// 		SDL_Log("SDL ERROR : %s > %s", str, get_err());
// 	quit(v);
// 	exit(EXIT_FAILURE);
// }
//////////////////////////////////////

void	sdl_exit_fail(char *str, t_visu *v, const char *(*get_err)(void))
{
	if (str)
		SDL_Log("SDL ERROR : %s > %s", str, get_err());
	//quit(v);
	v = NULL;//
	exit(EXIT_FAILURE);
}

void	exit_fail(char *str, t_visu *v)
{
	if (str)
		ft_printf("[red]%s[a_reset]\n", str);
	//quit(v);
	v = NULL;//
	exit(EXIT_FAILURE);
}

void	read_ant_nb(t_visu *v)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (*line == '#')
			free(line);
		else if (str_is_numeric_no_symbol(line) && *line != '0')
		{
			v->ant_nb = atou(line);
			return (free(line));
		}
		else
		{
			free(line);
			exit_fail("No/invalid ant nbr", v);
		}
	}
}

void	parsing(t_visu *v)
{
	read_ant_nb(v);
	read_room(v);
	read_link(v);
}

void	init_struct(t_visu *v)
{
	v->window = NULL;
	v->renderer = NULL;
	v->font = NULL;
	v->ant_nb = 0;
	v->start = 0;
	v->end = 0;
}

void	init(t_visu *v)
{
	init_struct(v);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		sdl_exit_fail("Init()", v, &SDL_GetError);
	if (!(v->window = SDL_CreateWindow("Lem_in Visualiseur",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINW, WINH, 0)))
		sdl_exit_fail("CreateWindow()", v, &SDL_GetError);
	if (!(v->renderer = SDL_CreateRenderer(v->window, -1,
		SDL_RENDERER_SOFTWARE)))
		sdl_exit_fail("CreateRenderer()", v, &SDL_GetError);
	if (TTF_Init() < 0)
		sdl_exit_fail("Init()", v, &TTF_GetError);
	if (!(v->font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 20)))
		sdl_exit_fail("OpenFont()", v, &TTF_GetError);
}

int	main(void)
{
	t_visu	v;

	init(&v);
	parsing(&v);
//	SDL_RenderPresent(v->renderer);
}