/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:36:31 by ssfar             #+#    #+#             */
/*   Updated: 2020/03/10 18:25:18 by ssfar            ###   ########.fr       */
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

typedef	struct		s_visu
{
	SDL_Event		event;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_Surface		*surface;
	SDL_Rect		rect;
	SDL_Rect		ant_rect;
	SDL_Rect		text_rect;
	SDL_Color		text_color;
	SDL_Color		background_color;
	TTF_Font		*font;
	struct s_info	*info;
	struct s_info	*cur_info;
	size_t			nb_room;
	size_t			nb_total_link;
	size_t			nb_valid_link;
	struct s_room	*room;
	struct s_link	*link;
	char			start_found;
	char			end_found;
	struct s_ant	*ant;
	char			*ant_moved;
	size_t			start_index;
	size_t			end_index;
	size_t			ant_nb;
	ssize_t			cam_x;
	ssize_t			cam_y;
	ssize_t			zoom;
	size_t			cur_time;
	size_t			prev_time_a;
	size_t			prev_time_b;
	size_t			turn;
	float			percent;
	char			all_ant_arrived;
}					t_visu;

typedef	struct		s_room
{
	char			*name;
	ssize_t			x;
	ssize_t			y;
}					t_room;

typedef	struct		s_link
{
	t_room			*a;
	t_room			*b;
}					t_link;

typedef	struct		s_info
{
	char			*str;
	struct s_info	*next;
}					t_info;

typedef struct		s_point
{
	ssize_t			x;
	ssize_t			y;
}					t_point;

typedef	struct		s_ant
{
	size_t			starting_turn;
	size_t			goal;
	size_t			nb_move;
	t_room			**path;
	size_t			moved;
}					t_ant;

void				find_ant_pos(t_visu *v, t_ant *a, ssize_t x, ssize_t y);
void				set_ant(t_visu *v, size_t ant_id, char *line);
void				set_ant_movement(t_visu *v, char *line);
size_t				count_arrived_ant(t_visu *v);
void				check_ant_format(t_visu *v, char *line);
void				display_link(t_visu *v);
void				display_counter(t_visu *v);
void				display_name(t_visu *v, char *str);
void				display_ant(t_visu *v);
void				display_turn(t_visu *v);
void				free_all_struct(t_visu *v);
void				free_info(t_visu *v);
void				init_ant_struct(t_visu *v, char *line);
void				init(t_visu *v);
void				init_loop(t_visu *v);
void				init_struct(t_visu *v);
char				is_room(char *line);
char				is_room2(char *line);
char				is_room_name_format(char *line, size_t *i);
char				is_link(t_visu *v, char *line);
int					main(void);
void				visu_lem_in(void);
void				sdl_loop(t_visu *v);
void				display_map(t_visu *v);
void				handle_keystate(t_visu *v, const uint8_t *keystate);
char				find_link(t_visu *v, char *str, size_t *index);
void				verify_ant_path_connexion(t_visu *v, t_room **path,
						size_t actual_room);
void				verify_ant_path(t_visu *v);
void				set_tip(t_visu *v, char start);
void				display_room(t_visu *v);
void				surface_to_texture(t_visu *v, SDL_Rect *rect);
char				add_info(t_visu *v, char *line);
ssize_t				linear_interpolation(float percentage, ssize_t p1,
						ssize_t p2);
void				invalid_map(t_visu *v, char *to_free);
void				quit(t_visu *v);
void				sdl_exit_fail(t_visu *v, char *str,
						const char *(*get_err)(void));
void				exit_fail(t_visu *v, char *str, char *to_free);
void				read_tip(t_visu *v, char start, char *line);
char				*read_room(t_visu *v);
char				*read_link(t_visu *v, char *line);
void				read_ant_nb(t_visu *v);
void				read_ant_movement(t_visu *v, char *line);
void				store_ant_movement(t_visu *v);
size_t				store_ant_path(t_visu *v, char *line, size_t i);
void				store_link(t_visu *v, char *to_free);
void				store_room(t_visu *v);
void				center_start(t_visu *v);
void				reset(t_visu *v);

#endif
