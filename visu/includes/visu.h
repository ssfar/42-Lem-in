/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:36:31 by ssfar             #+#    #+#             */
/*   Updated: 2019/12/11 17:21:12 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H
# define WINW 2080
# define WINH 1280
# include <SDL.h>
# include <SDL_ttf.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

typedef	struct	s_visu
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
	size_t			ant_nb;
	size_t			start;
	size_t			end;
}				t_visu;

#endif