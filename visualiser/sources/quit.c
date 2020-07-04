/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:09:57 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/09 17:13:08 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	invalid_map(t_visu *v, char *to_free)
{
	size_t	stop;

	free(to_free);
	v->rect.w = 500;
	v->rect.h = 125;
	v->rect.x = (WINW - v->rect.w) / 2;
	v->rect.y = (WINH - v->rect.h) / 2;
	if (!(v->surface = TTF_RenderText_Blended(v->font, "Invalid Map",
		v->text_color)))
		sdl_exit_fail(v, "RenderText()", &TTF_GetError);
	surface_to_texture(v, &v->rect);
	SDL_RenderPresent(v->renderer);
	stop = 0;
	while (!stop)
		while (SDL_PollEvent(&v->event))
			if (v->event.type == SDL_QUIT
				|| v->event.key.keysym.sym == SDLK_ESCAPE)
				stop = 1;
	quit(v);
	exit(0);
}

void	quit(t_visu *v)
{
	if (SDL_WasInit(SDL_INIT_VIDEO))
	{
		if (TTF_WasInit())
		{
			SDL_FreeSurface(v->surface);
			SDL_DestroyTexture(v->texture);
			free_all_struct(v);
			TTF_CloseFont(v->font);
			TTF_Quit();
		}
		SDL_DestroyWindow(v->window);
		SDL_DestroyRenderer(v->renderer);
		SDL_Quit();
	}
}

void	sdl_exit_fail(t_visu *v, char *str, const char *(*get_err)(void))
{
	if (str)
		SDL_Log("SDL ERROR : %s > %s", str, get_err());
	quit(v);
	exit(EXIT_FAILURE);
}

void	exit_fail(t_visu *v, char *str, char *to_free)
{
	free(to_free);
	if (str)
		ft_printf("[red]%s[a_reset]\n", str);
	quit(v);
	exit(EXIT_FAILURE);
}
