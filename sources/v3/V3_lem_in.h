/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V3_lem_in.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:52:28 by ssfar             #+#    #+#             */
/*   Updated: 2019/11/12 18:59:36 by ssfar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# define MAP_SIZE	1024

typedef struct	s_lem_in
{
	ssize_t			ant;
	struct	s_info	*info;
	struct	s_info	*current;
	struct	s_info	*pipe;
	struct	s_room	*start;
	struct	s_room	*end;
	struct	s_room	*room_tab;
	size_t			nb_room;
	struct	s_table	map[MAP_SIZE];
}				t_lem_in;

typedef	struct	s_info
{
	char			*str;
	struct	s_info	*i_next;
}				t_info;

typedef	struct	s_table
{
	struct s_room	*room;
	struct s_table	*t_next;
}				t_table;

typedef	struct	s_room
{
	size_t	index;
	char	*name;
	size_t	nb_link;
	size_t	*link;
}				t_room;

void			hash_data(void *dest, const size_t size, const char *key);
unsigned int	hash_to_int(const char *key);
t_table			*find_table(t_table *table, char *key, size_t index);
void			hash_data(void *dest, const size_t size, const char *key);
void			init_struct(t_lem_in *s);
void			init_map(t_lem_in *s);
void			read_ant_nb(t_lem_in *s);
t_info			*create_info(char *str);
void			info_push_back(t_lem_in *s, t_info *to_add);
void			init_info(t_info *new, char *str);
char			*read_room(t_lem_in *s);
void			read_tip(t_lem_in *s, t_room **tip);