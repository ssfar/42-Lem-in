/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:52:42 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/12 14:14:44 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"

# define MAP_SIZE	1024

typedef struct	s_lem_in
{
	ssize_t			ant;
	struct s_info	*info;
	struct s_info	*i_current;
	struct s_table	*map[MAP_SIZE];
	struct s_table	*start;
	struct s_table	*end;
	size_t			nb_room;
	uint_fast8_t	st;
	uint_fast8_t	en;
}				t_lem_in;

typedef struct	s_info
{
	char			*str;
	struct	s_info	*i_next;
}				t_info;

typedef struct	s_table
{
	char			*key;
	struct s_link	*link;
	struct s_table	*t_next;
}				t_table;

typedef struct s_link
{
	struct s_table	*jump;
	struct s_link	*l_next;
}				t_link;


void	link_push_back(t_table *src, t_link *to_add);

// typedef struct	s_room
// {
// 	char			*name;
// 	struct s_room	*r_next;
// 	struct s_link	*link;
// }				t_room;

// typedef struct s_link
// {
// 	struct s_room	*jump;
// 	struct s_link	*l_next;
// }				t_link;

// typedef struct	s_tube
// {
// 	char			*str;
// 	struct s_tube	*t_next;
// }				t_tube;

// typedef struct	s_lem_in
// {
// 	ssize_t			ant;
// 	struct s_room	*start;
// 	struct s_room	*end;
// 	struct s_room	*first;
// 	struct s_room	*current;
// 	struct s_tube	*tube;
// }				t_lem_in;

