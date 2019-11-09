/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:52:42 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/09 11:29:30 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct	s_lem_in
{
	ssize_t	ant;
	t_room	*start;
	t_room	*end;
	t_room	*first;
	t_room	*last;
	t_tube	*tube;
}				t_lem_in;

typedef struct	s_room
{
	char		*name;
	s_room		*next;
	s_connexion	*connexion;
}				t_room;

typedef struct s_connexion
{
	s_room		*neighbour;
	s_connexion	*next;
}				t_connexion;

typedef struct	s_tube
{
	char	*link;
	s_tube	*next;
}				t_tube;

ssize_t	read_ant_nb(void);
void	init_struct(t_lem_in *l);
void	free_room(t_room *to_delete);
void	room_clear(t_room *to_clear);
t_room	*create_room(char *r_name);
void	init_room(t_room *new, char *r_name);
void	room_push_back(t_lem_in *l, t_room *to_add);
void	print_room(t_room *room, char *message);
void	free_tube(t_tube *to_delete);
void	tube_clear(t_tube *to_clear);
t_tube	create_tube(char *t_link);
t_tube	*initialize_tube(char *t_link);
void	tube_push_back(t_tube *src, t_tube *to_add);
void	print_tube(t_tube *tube, char *message);
uint_fast8_t	is_room(char *line);
uint_fast8_t	is_room2(char *line, size_t	i);
