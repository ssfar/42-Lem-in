/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:52:42 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/11 00:42:05 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"

typedef struct	s_room
{
	char			*name;
	struct s_room	*r_next;
	struct s_link	*link;
}				t_room;

typedef struct s_link
{
	struct s_room	*jump;
	struct s_link	*l_next;
}				t_link;

typedef struct	s_tube
{
	char			*str;
	struct s_tube	*t_next;
}				t_tube;

typedef struct	s_lem_in
{
	ssize_t			ant;
	struct s_room	*start;
	struct s_room	*end;
	struct s_room	*first;
	struct s_room	*current;
	struct s_tube	*tube;
}				t_lem_in;

void	read_ant_nb(t_lem_in *s);
void	init_struct(t_lem_in *s);
void	free_room(t_room *to_delete);
void	room_clear(t_room *to_clear);
t_room	*create_room(char *r_name);
void	init_room(t_room *new, char *r_name);
void	room_push_back(t_lem_in *s, t_room *to_add);
void	print_room(t_room *room, char *message);
void	free_tube(t_tube *to_delete);
void	tube_clear(t_tube *to_clear);
t_tube	*create_tube(char *t_link);
void	init_tube(t_tube *new, char *t_link);
void	tube_push_back(t_tube *src, t_tube *to_add);
void	print_tube(t_tube *tube, char *message);
void	read_tube(t_lem_in *s, char *line);
void	free_link(t_link *to_delete);
void	link_clear(t_link *to_clear);
void	init_link(t_link *link, t_room *room);
t_link	*create_link(t_room *room);
void	link_push_back(t_room *src, t_link *to_add);
uint_fast8_t	is_room(char *line);
uint_fast8_t	is_room2(char *line);
void	read_tip(t_room **tip, t_lem_in *s);
char	*read_room(t_lem_in *s);
t_room	*get_room(char *line, t_lem_in *s);
void	print_link(t_room *room, char *message);
void	exit_failure(t_lem_in *s, size_t id, char *message);
uint_fast16_t	room_compare(const char *s1, const char *s2);
